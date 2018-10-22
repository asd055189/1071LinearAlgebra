//1061516 Linear algebra HW2
//紀錄用 勿抄襲
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <math.h>
using namespace std;
using namespace cv;


int main(int argc, char  *argv[]) {
	int flags;
	Mat img = imread(argv[1], flags = 1);
	/*============open source============*/
	Mat Image_2(img.size(), CV_64FC3);
	img.convertTo(Image_2, CV_64FC3);
	Mat r(img.rows, img.cols, CV_64FC1);
	Mat g(img.rows, img.cols, CV_64FC1);
	Mat b(img.rows, img.rows, CV_64FC1);

	Mat out[] = { b,g,r };
	split(Image_2, out);

	// 三个通道的顺序是 b,g,r.
	/*============open source============*/
	ifstream in;
	in.open(argv[2]);
	string str;
	vector <double> harr;
	while (getline(in, str))
	{

		int pos;
		char *num = NULL;
		while ((pos = str.find(',')) != -1) {
			num = new char[pos]();
			str.copy(num, pos, 0);
			str.erase(0, pos + 1);
			double x = atof(num);
			harr.push_back(x);
		}
		pos = str.size();
		num = new char[pos]();
		str.copy(num, pos, 0);
		double x = atof(num);
		harr.push_back(x);
	}
	int HarrSide = pow(harr.size(), 0.5);
	vector <Mat> squaresr;
	vector <Mat> squaresg;
	vector <Mat> squaresb;		
		for (int i = 0; i < pow(img.cols / HarrSide, 2); i++) {
			Mat tmpr(HarrSide, HarrSide, CV_64FC1);
			Mat tmpg(HarrSide, HarrSide, CV_64FC1);
			Mat tmpb(HarrSide, HarrSide, CV_64FC1);
			for (int row = 0; row < HarrSide; row++)
				for (int col = 0; col < HarrSide; col++){
					
					tmpr.at<double>(row, col) = r.at<double>((i / (img.cols / HarrSide)) * HarrSide + row, (HarrSide * i + col) % img.cols);
					tmpg.at<double>(row, col) = g.at<double>((i / (img.cols / HarrSide)) * HarrSide + row, (HarrSide * i + col) % img.cols);
					tmpb.at<double>(row, col) = b.at<double>((i / (img.cols / HarrSide)) * HarrSide + row, (HarrSide * i + col) % img.cols);
					
				}

			squaresr.push_back(tmpr);
			squaresg.push_back(tmpg);
			squaresb.push_back(tmpb);
		}

	Mat H(HarrSide, HarrSide, CV_64FC1);
	for (int i = 0; i < HarrSide; i++)
		for (int j = 0; j < HarrSide; j++)
			H.at<double>(i, j) = harr[(HarrSide*i) + j];
	Mat HT(HarrSide, HarrSide, CV_64FC1);
	transpose(H, HT);

	for (int i = 0; i < squaresr.size(); i++) {
		squaresr[i] = HT * squaresr[i] * H;
		squaresg[i] = HT * squaresg[i] * H;
		squaresb[i] = HT * squaresb[i] * H;
	}

	for (int i = 0; i < squaresr.size(); i++)
	{
			for (int row = 0; row < HarrSide; row++) {
				for (int col = 0; col < HarrSide; col++) {
					r.at<double>((i / (img.cols / HarrSide)) * HarrSide + row, (HarrSide * i + col) % img.cols) = squaresr[i].at<double>(row, col);
					g.at<double>((i / (img.cols / HarrSide)) *HarrSide + row, (HarrSide * i + col) % img.cols) = squaresg[i].at<double>(row, col);
					b.at<double>((i / (img.cols / HarrSide)) * HarrSide + row, (HarrSide * i + col) % img.cols) = squaresb[i].at<double>(row, col);
				}
			}

	}

	Mat newpicture[] = { b ,g ,r };
	Mat output(img.rows, img.cols, CV_64FC3);
	merge(newpicture, 3, output);
	for (int i = 0; i < output.rows; i++) {
		for (int j = 0; j < output.cols; j++) {
			if (output.at<double>(i, j) >= 255.0) {
				output.at<double>(i, j) = 255.0;
			}
			else if (output.at<double>(i, j) <= 0.0) {
				output.at<double>(i, j) = 0.0;
			}
			else {
				output.at<double>(i, j) = round(output.at<double>(i, j));
			}
		}
	}
	Mat save(img.rows, img.cols, CV_8U);
	output.convertTo(save, CV_8U);
	imwrite(argv[3], save);
}