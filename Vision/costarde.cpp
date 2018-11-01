#include "pch.h"
#include "costarde.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>

costarde::costarde()
{
}

costarde::costarde(Mat* pOriginal)
{
	_original = pOriginal;

	createHistogram(_original, _histogram);
}


costarde::~costarde()
{
}

bool sortCount(const Vec4f &lhs, const Vec4f &rhs) { return lhs[3] > rhs[3]; }

void costarde::createHistogram(Mat * pImg, Vec4f* pHistogram)
{
	loadHistogram(pHistogram);

	for (int y = 0; y < pImg->rows; y++) {
		for (int x = 0; x < pImg->cols; x++) {
			Vec3b pix = pImg->at<Vec3b>(y, x);
			int b = pix[0] / 64;
			int g = pix[1] / 64;
			int r = pix[2] / 64;

			int i = r * 16 + g * 4 + b;
			pHistogram[i][3]++;
		}
	}
}

void costarde::loadHistogram(Vec4f * pHistogram)
{
	int blue = 0;
	int green = 0;
	int red = 0;

	for (int i = 0; i < 64; i++) {

		if (blue > 3) {
			blue = 0;
			green++;
		}

		if (green > 3) {
			green = 0;
		}

		pHistogram[i][0] = blue;
		pHistogram[i][1] = green;
		pHistogram[i][2] = red;

		if (blue == 3 && green == 3) red++;
		blue++;
	}
}

void costarde::drawHistogram(Mat * pImg)
{
	Mat imgRGB = pImg->clone();
	Mat img = pImg->clone();
	cvtColor(img, img, CV_BGR2HSV);

	Vec4f histogram[64];
	createHistogram(&img, histogram);

	std::sort(histogram, histogram + 64, sortCount);

	for (int y = 0; y < img.rows; y++) {
		for (int x = 0; x < img.cols; x++) {
			Vec3b pix = img.at<Vec3b>(y, x);
			int b = pix[0] / 64;
			int g = pix[1] / 64;
			int r = pix[2] / 64;

			if (histogram[0][0] == b && histogram[0][1] == g && histogram[0][2] == r) {
				imgRGB.at<Vec3b>(y, x)[0] = 255;
				imgRGB.at<Vec3b>(y, x)[1] = 255;
				imgRGB.at<Vec3b>(y, x)[2] = 255;
			}
			else if (histogram[1][0] == b && histogram[1][1] == g && histogram[1][2] == r) {
				imgRGB.at<Vec3b>(y, x)[0] = 0;
				imgRGB.at<Vec3b>(y, x)[1] = 255;
				imgRGB.at<Vec3b>(y, x)[2] = 0;
			}
			else if (histogram[2][0] == b && histogram[2][1] == g && histogram[2][2] == r) {
				imgRGB.at<Vec3b>(y, x)[0] = 0;
				imgRGB.at<Vec3b>(y, x)[1] = 0;
				imgRGB.at<Vec3b>(y, x)[2] = 255;
			}
			else if (histogram[3][0] == b && histogram[3][1] == g && histogram[3][2] == r) {
				imgRGB.at<Vec3b>(y, x)[0] = 255;
				imgRGB.at<Vec3b>(y, x)[1] = 0;
				imgRGB.at<Vec3b>(y, x)[2] = 0;
			}
		}
	}

	imshow("draw histogram", imgRGB);
}

void costarde::drawContour(Mat * pImg)
{
	Mat img = pImg->clone();
	Mat imgHsv = pImg->clone();

	cvtColor(imgHsv, imgHsv, COLOR_BGR2HSV);

	inRange(imgHsv, Scalar(38, 70, 50), Scalar(95, 255, 255), img);

	std::vector<Vec4i> hierarchy;
	std::vector<std::vector<Point> > contours;
	findContours(img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	if (contours.size > 0)
	{

	}
	
	imshow("draw contour", img);
}

bool costarde::findCostarde(Mat* pImg)
{
	Mat img = pImg->clone();
	cvtColor(img, img, CV_BGR2HSV);

	Vec4f histogram[64];
	createHistogram(&img, histogram);

	Vec4f lgst;
	Vec4f scdLgst;
	for (int i = 0; i < 64; i++) {
		Vec4f cur = histogram[i];

		if (cur[3] > lgst[3]) {
			scdLgst = lgst;
			lgst = cur;
		}
		else if (cur[3] > scdLgst[3]) {
			scdLgst = cur;
		}
	}

	if (_costardeRange[0] == lgst[0] && _costardeRange[1] == lgst[1] && _costardeRange[2] == lgst[2] || _costardeRange[0] == scdLgst[0] && _costardeRange[1] == scdLgst[1] && _costardeRange[2] == scdLgst[2])
		return true;
	else
		return false;
}

bool costarde::findFeuille(Mat * pImg)
{
	Mat img = pImg->clone();
	cvtColor(img, img, CV_BGR2HSV);

	Vec4f histogram[64];
	createHistogram(&img, histogram);

	std::sort(histogram, histogram + 64, sortCount);

	if (_feuilleRange[0] == histogram[1][0] && _feuilleRange[1] == histogram[1][1] && _feuilleRange[2] == histogram[1][2] || _feuilleRange[0] == histogram[2][0] && _feuilleRange[1] == histogram[2][1] && _feuilleRange[2] == histogram[2][2])
		return true;
	else
		return false;

	return false;
}

bool costarde::findCream(Mat * pImg)
{
	Mat img = pImg->clone();
	cvtColor(img, img, CV_BGR2HSV);

	Vec4f histogram[64];
	createHistogram(&img, histogram);

	std::sort(histogram, histogram + 64, sortCount);

	for (int i = 0; i < 64; i++) {
		if (_costardeRange[0] == histogram[i][0] && _costardeRange[1] == histogram[i][1] && _costardeRange[2] == histogram[i][2]) {
			if (histogram[i][3] > 25000) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	return false;
}
