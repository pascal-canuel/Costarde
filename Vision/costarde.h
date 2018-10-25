#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class costarde
{
public:
	costarde(Mat* pOriginal);
	~costarde();

	void createHistogram(Mat* pImg, Vec4f* pHistogram);
	void loadHistogram(Vec4f* pHistogram);

	void findDefault(Mat* pImg);

	void findCostarde(Vec4f* pHistogram);

private:
	
	Vec4f _histogram[64];
	Mat* _original;

	Vec3f _costardeRange = Vec3f(0, 1, 2);
};

