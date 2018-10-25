#include "pch.h"
#include "costarde.h"


costarde::costarde(Mat* pOriginal)
{
	_original = pOriginal;

	createHistogram(_original, _histogram);
}


costarde::~costarde()
{
}

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
	
	imshow("2MostFrequentColors", *pImg);
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
		/*histogram[i][0] = red;
		histogram[i][1] = green;
		histogram[i][2] = blue;*/

		if (blue == 3 && green == 3) red++;
		blue++;
	}

	/*for (int i = 0; i < 64; i++) {
		std::cout << histogram[i] << std::endl;
	}*/
}

void costarde::findDefault(Mat * pImg)
{
	Vec4f histogram[64];
	createHistogram(pImg, histogram);

	findCostarde(histogram);
}

void costarde::findCostarde(Vec4f* pHistogram)
{
	Vec4f lgst;
	Vec4f scdLgst;
	for (int i = 0; i < 64; i++) {
		Vec4f cur = pHistogram[i];

		if (cur[3] > lgst[3]) {
			scdLgst = lgst;
			lgst = cur;
		}
		else if (cur[3] > scdLgst[3]) {
			scdLgst = cur;
		}
	}

	if (_costardeRange[0] == lgst[0] && _costardeRange[1] == lgst[1] && _costardeRange[2] == lgst[2])
		std::cout << "THERE IS SOME COSTARDE" << std::endl;
	else 
		std::cout << "THERE IS NO COSTARDE" << std::endl;
}


//for (int y = 0; y < _original->rows; y++) {
//	for (int x = 0; x < _original->cols; x++) {
//		Vec3b pix = _original->at<Vec3b>(y, x);
//		int b = pix[0] / 64;
//		int g = pix[1] / 64;
//		int r = pix[2] / 64;
//
//		int i = r * 16 + g * 4 + b;
//		if (pHistogram[i] == lgst) {
//			_original->at<Vec3b>(y, x)[0] = 255;
//			_original->at<Vec3b>(y, x)[1] = 255;
//			_original->at<Vec3b>(y, x)[2] = 255;
//		}
//		else if (pHistogram[i] == scdLgst) {
//			_original->at<Vec3b>(y, x)[0] = 0;
//			_original->at<Vec3b>(y, x)[1] = 0;
//			_original->at<Vec3b>(y, x)[2] = 0;
//		}
//		else {
//
//		}
//	}
//}
