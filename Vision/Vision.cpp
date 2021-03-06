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
	costarde milleFeuille;

	// vérification du contenu 
	vector<String> pathList;
	pathList.push_back("Costarde/noCream.jpg");
	pathList.push_back("Costarde/noCostarde.jpg");
	pathList.push_back("Costarde/nothing.jpg");
	pathList.push_back("Costarde/original.jpg");

	while (!pathList.empty()) {
		String path = pathList.back();
		pathList.pop_back();
		Mat img = imread(path);

		// dessiner son histogramme 
		milleFeuille.drawHistogram(&img);

		bool costarde = milleFeuille.findCostarde(&img);
		bool feuille = milleFeuille.findFeuille(&img);		
		bool cream = milleFeuille.findCream(&img);

		if (costarde && feuille && cream)
			cout << "it is perfect" << endl;
		else if (!costarde && !feuille && !cream)
			cout << "there is nothing good. Give some costarde xD" << endl;
 		else if (!costarde && feuille && !cream)
			cout << "there is no costard" << endl;
		else if (costarde && feuille && !cream)
			cout << "there is no cream" << endl;
		else if (costarde && !feuille && cream)
			cout << "there is no feuille" << endl;

		imshow("contenu", img);
		waitKey(0);
	}

	// vérification de la dimension
	pathList.push_back("Costarde/noTop.jpg");
	pathList.push_back("Costarde/errorDimGreen.jpg");
	pathList.push_back("Costarde/originalDim.jpg");

	while (!pathList.empty()) {
		String path = pathList.back();
		pathList.pop_back();

		Mat img = imread(path);
		imshow("dimension", img);

		// dessiner son histogramme 
		milleFeuille.drawContour(&img);

		waitKey(0);
	}
	waitKey(0);
	
	return 0;
}

