// ClipCount.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	cv::Mat srcMat = imread("E:\\课程\\数字图像处理\\clip.png", 0);
	cv::Mat BinaryMat;
	cv::Mat statsMat;
	cv::Mat labelMat;
	cv::Mat centrMat;
	cv::Mat ResultMat;
	cv::Mat OpenMat;

	//二值化
	threshold(srcMat, BinaryMat, 90, 255, THRESH_BINARY_INV);


	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(BinaryMat, OpenMat, MORPH_OPEN, element); //腐蚀运算

	BinaryMat.copyTo(ResultMat);
	//连通域标记
	int nComp = connectedComponentsWithStats(BinaryMat,
		labelMat,
		statsMat,
		centrMat,
		8,
		CV_32S);
	int ClipArea = 0;
	int num = 0;
	for (int i = 1; i < nComp; i++)
	{
		ClipArea += statsMat.at<int>(i, 4);
	}
	for (int i = 1; i < nComp; i++)
	{
		if (statsMat.at<int>(i, 4) > (ClipArea / nComp - 1))
			num++;
	}
	


	imshow("bMat", BinaryMat);
	//imshow("resultMat", OpenMat);

	cout << num << endl;
	waitKey(0);
	return 0;
    //std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
