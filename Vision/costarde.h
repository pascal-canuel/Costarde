#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class costarde
{
public:
	costarde();
	costarde(Mat* pOriginal);
	~costarde();

	void createHistogram(Mat* pImg, Vec4f* pHistogram);
	void loadHistogram(Vec4f* pHistogram);

	void drawHistogram(Mat* pImg);
	void drawContour(Mat* pImg);

	bool findCostarde(Mat* pImg);
	bool findFeuille(Mat* pImg);
	bool findCream(Mat* pImg);
private:
	
	Vec4f _histogram[64];
	Mat* _original;

	Vec3f _costardeRange = Vec3f(0, 1, 2);
	Vec3f _feuilleRange = Vec3f(0, 1, 1);
};

