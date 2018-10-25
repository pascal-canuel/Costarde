// Vision.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "costarde.h"

using namespace cv;
using namespace std;

int main()
{
#pragma region "take picture of costarde"
	/*
	VideoCapture cap(0);

	Mat frame;
	if (!cap.isOpened())
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	int i = 0;
	while (true)
	{
		cap.read(frame);
		if (frame.empty())
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		imshow("frame", frame);


		waitKey(30);
		if (waitKey(30) > 0)
		{
			imwrite("Costarde/" + to_string(i) + ".jpg", frame);
			i++;
		}
	}
	cap.release();
	*/
#pragma endregion
	
	Mat original = imread("Costarde/17.jpg");
	Mat destruction = imread("Costarde/18.jpg");
	Mat ahnilation = imread("Costarde/19.jpg");
	Mat ancestrale = imread("Costarde/SideCostardOff.bmp");

	cvtColor(original, original, CV_BGR2HSV);
	costarde costarde(&ancestrale);

	cvtColor(destruction, destruction, CV_BGR2HSV);
	cvtColor(ahnilation, ahnilation, CV_BGR2HSV);
	cvtColor(ancestrale, ancestrale, CV_BGR2HSV);

	costarde.findDefault(&ancestrale);

	waitKey(0);
	
	return 0;
}

