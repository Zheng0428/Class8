#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
using namespace cv;
using namespace std;
int main()
{
	cv::Mat srcMat = imread("D:\\a\\die_on_chip.png", 0);
	cv::Mat Result = imread("D:\\a\\die_on_chip.png");

	cv::Mat	BinaryMat;
	cv::Mat	OpenMat;
	cv::Mat GaussFilterMat;

	//��ֵ��
	threshold(srcMat, BinaryMat, 125, 175, THRESH_BINARY);
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(BinaryMat, OpenMat, MORPH_OPEN, element);			//������

	//GaussianBlur(BinaryMat, GaussFilterMat, Size(3, 3), 2,2, BORDER_DEFAULT);//��˹�˲�

	vector<vector<Point>> contours;
	findContours(OpenMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i < contours.size(); i++)
	{
		//�����С����ı���
		RotatedRect rbox = minAreaRect(contours[i]);

		float width = rbox.size.width;
		float height = rbox.size.height;
		float proportion = width / height;
		float pixelsum = width * height;
		if (pixelsum > 1000)
		{
			if (fabs(proportion - 1) < 0.1)
			{
				cv::Point2f vtx[4];
				rbox.points(vtx);
				for (int i = 0; i < 4; ++i)
				{
					cv::line(Result, vtx[i], vtx[i < 3 ? i + 1 : 0], cv::Scalar(0, 0, 255), 2);
				}
				//��������
				drawContours(Result, contours, i, Scalar(0, 255, 255), 1, 8);

			}
		}

	}

	imshow("srcMat", srcMat);
	imshow("binaryMat", BinaryMat);



	imshow("Result", Result);
	waitKey(0);

}
