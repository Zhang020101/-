#include<iostream>
#include<opencv2/opencv.hpp>
#include<imgproc/imgproc.hpp>
#include<highgui/highgui.hpp>

using namespace cv;
using namespace std;


int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat image, image_gray,g_dstImage;

void myfilter(Mat& image_input, Mat& image_output) //4
{
	image_output = image_input.clone();
	int la;
	for (int i = 1; i < (image_input.rows - 1); i++)
	{
		for (int j = 1; j < (image_input.cols - 1); j++)
		{
			la = 4 * image_input.at<uchar>(i, j) - image_input.at<uchar>(i + 1, j) - image_input.at<uchar>(i - 1, j) - image_input.at<uchar>(i, j + 1) - image_input.at<uchar>(i, j - 1);

			image_output.at<uchar>(i, j) = saturate_cast<uchar>(image_output.at<uchar>(i, j) + la);

		}
	}
}
void myfilter2(Mat& image_input, Mat& image_output) //8
{
	image_output = image_input.clone();
	int la2;
	for (int i = 1; i < (image_input.rows - 1); i++)
	{
		for (int j = 1; j < (image_input.cols - 1); j++)
		{
			la2 = 8 * image_input.at<uchar>(i, j) - image_input.at<uchar>(i + 1, j) - image_input.at<uchar>(i - 1, j) - image_input.at<uchar>(i, j + 1) - image_input.at<uchar>(i, j - 1)
				- image_input.at<uchar>(i - 1, j - 1) - image_input.at<uchar>(i + 1, j + 1) - image_input.at<uchar>(i - 1, j + 1) - image_input.at<uchar>(i + 1, j - 1);

			image_output.at<uchar>(i, j) = saturate_cast<uchar>(image_output.at<uchar>(i, j) + la2);

		}
	}
}

void on_Threshold(int, void*)
{
	threshold(image_gray, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);

	imshow("��ֵ����", g_dstImage);

}

//void adaptiveThreshold(InputArray src, OutputArray dst,
//	double maxValue, int adaptiveMethod,
//	int thresholdType, int blockSize, double C);
int main()
{
	Mat  image_output, image_output2;   //��������ͼ�񣬻Ҷ�ͼ�����ͼ��
	image = imread("΢��ͼƬ_20220429112901.jpg");  //��ȡͼ��
	if (image.empty())
	{
		cout << "��ȡ����" << endl;
		return -1;
	}

	imshow("ԭͼ", image);

	cvtColor(image, image_gray, COLOR_BGR2GRAY);
	imshow("�Ҷ�ͼ", image_gray);

	//�Աຯ��
	myfilter(image_gray, image_output); //4����
	imshow("4����", image_output);

	myfilter2(image_gray, image_output2); //8����
	imshow("8����", image_output2);
	waitKey(0);



	namedWindow("��ֵ����");

	createTrackbar("ģʽ", "��ֵ����", &g_nThresholdType, 4, on_Threshold);
	createTrackbar("����ֵ", "��ֵ����", &g_nThresholdValue, 255, on_Threshold);

	waitKey(0);
	//����Ӧ��ֵ�Ķ�ֵ��
	Mat srcBinary1;
	adaptiveThreshold(~image_gray, srcBinary1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, -2);
	//namedWindow("srcBinary 1", WINDOW_AUTOSIZE);
	imshow("����Ӧ��ֵ�Ķ�ֵ�� 1", srcBinary1);

	//Mat srcBinary2;
	//adaptiveThreshold(~image_gray, srcBinary1, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, -2);
	////namedWindow("srcBinary 2", WINDOW_AUTOSIZE);
	//imshow("����Ӧ��ֵ�Ķ�ֵ�� 2", srcBinary2);

	waitKey(0);  //��ͣ������ͼ����ʾ���ȴ���������
	return 0;
}


