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

	imshow("阈值窗口", g_dstImage);

}

//void adaptiveThreshold(InputArray src, OutputArray dst,
//	double maxValue, int adaptiveMethod,
//	int thresholdType, int blockSize, double C);
int main()
{
	Mat  image_output, image_output2;   //定义输入图像，灰度图像，输出图像
	image = imread("微信图片_20220429112901.jpg");  //读取图像；
	if (image.empty())
	{
		cout << "读取错误" << endl;
		return -1;
	}

	imshow("原图", image);

	cvtColor(image, image_gray, COLOR_BGR2GRAY);
	imshow("灰度图", image_gray);

	//自编函数
	myfilter(image_gray, image_output); //4邻域
	imshow("4邻域", image_output);

	myfilter2(image_gray, image_output2); //8邻域
	imshow("8邻域", image_output2);
	waitKey(0);



	namedWindow("阈值窗口");

	createTrackbar("模式", "阈值窗口", &g_nThresholdType, 4, on_Threshold);
	createTrackbar("参数值", "阈值窗口", &g_nThresholdValue, 255, on_Threshold);

	waitKey(0);
	//自适应阈值的二值化
	Mat srcBinary1;
	adaptiveThreshold(~image_gray, srcBinary1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, -2);
	//namedWindow("srcBinary 1", WINDOW_AUTOSIZE);
	imshow("自适应阈值的二值化 1", srcBinary1);

	//Mat srcBinary2;
	//adaptiveThreshold(~image_gray, srcBinary1, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, -2);
	////namedWindow("srcBinary 2", WINDOW_AUTOSIZE);
	//imshow("自适应阈值的二值化 2", srcBinary2);

	waitKey(0);  //暂停，保持图像显示，等待按键结束
	return 0;
}


