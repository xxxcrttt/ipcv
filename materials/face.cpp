// header inclusion
#include <stdio.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );
void correct_face( Mat frame );
int pfIOU();
double f1score(double precision, double recall);

/** Global variables */
String cascade_name = "frontalface.xml";
CascadeClassifier cascade;

// ground truth boxes
std::vector<Rect> faces;

//dart 0 -- face


//dart 0 -- dart
//int n = 1;
//int truex[] = { 445 };
//int truey[] = { 20 };
//int width[] = { 152 };
//int height[] = { 170 };


//dart 1
//int n = 1;
//int truex[] = { 198 };
//int truey[] = { 133 };
//int width[] = { 190 };
//int height[] = { 190 };

//dart 2
//int n = 1;
//int truex[] = { 89 };
//int truey[] = { 83 };
//int width[] = { 115 };
//int height[] = { 115 };

//dart 3
//int n = 1;
//int truex[] = { 325 };
//int truey[] = { 145 };
//int width[] = { 65 };
//int height[] = { 75 };

//dart4 -- face
//int n = 1;
//int truex[] = { 350 };
//int truey[] = { 95 };
//int width[] = { 125 };
//int height[] = { 168 };

//dart 4 -- dart
//int n = 1;
//int truex[] = { 188 };
//int truey[] = { 110 };
//int width[] = { 162 };
//int height[] = { 165 };


//dart5 -- face
//int n = 11;
//int truex[] = { 67, 250, 372, 510, 646, 60, 195, 297, 430, 565, 685};
//int truey[] = { 134, 163, 193, 175, 186, 246, 204, 234, 233, 232, 236 };
//int width[] = { 54, 53, 64, 59, 57, 52, 54, 48, 54, 51, 49 };
//int height[] = { 74, 70, 50, 60, 54, 70, 80, 76, 72, 82, 77 };


//dart 5 -- dart
//int n = 1;
//int truex[] = { 434  };
//int truey[] = { 142 };
//int width[] = { 110 };
//int height[] = { 104 };

//dart 6
//int n = 1;
//int truex[] = { 200  };
//int truey[] = { 114 };
//int width[] = { 75 };
//int height[] = { 75 };

//dart 7
//int n = 1;
//int truex[] = { 255 };
//int truey[] = { 170 };
//int width[] = { 135 };
//int height[] = { 145 };

//dart 8
//int n = 2;
//int truex[] = { 62, 839 };
//int truey[] = { 250, 215 };
//int width[] = { 62, 115 };
//int height[] = { 92, 122 };

//dart 9
//int n = 1;
//int truex[] = { 202 };
//int truey[] = { 47 };
//int width[] = { 231 };
//int height[] = { 230 };

//dart 10
//int n = 3;
//int truex[] = { 90, 583, 915 };
//int truey[] = { 104, 130, 153 };
//int width[] = { 97, 56, 38 };
//int height[] = { 105, 82, 60 };

//dart 11
//int n = 1;
//int truex[] = { 175 };
//int truey[] = { 107 };
//int width[] = { 55 };
//int height[] = { 45 };

//dart 12
//int n = 1;
//int truex[] = { 160 };
//int truey[] = { 78 };
//int width[] = { 55 };
//int height[] = { 133 };

//dart 13 -- face
//int n = 1;
//int truex[] = { 420 };
//int truey[] = { 120 };
//int width[] = { 105 };
//int height[] = { 136 };

//dart 13 -- dart
//int n = 1;
//int truex[] = { 270 };
//int truey[] = { 120 };
//int width[] = { 132 };
//int height[] = { 132 };

//dart 14 -- face
//int n = 2;
//int truex[] = { 470, 725 };
//int truey[] = { 210, 185 };
//int width[] = { 85, 100 };
//int height[] = { 113, 113 };

//dart 14 -- dart
int n = 2;
int truex[] = { 122, 985 };
int truey[] = { 105, 94 };
int width[] = { 122, 124 };
int height[] = { 125, 123 };


// dart 15 -- face
//int n = 3;
//int truex[] = { 60, 370, 535 };
//int truey[] = { 130, 100, 115 };
//int width[] = { 65, 65, 80 };
//int height[] = { 85, 85, 100 };

//dart 15 -- dart
//int n = 1;
//int truex[] = { 155 };
//int truey[] = { 58 };
//int width[] = { 130 };
//int height[] = { 135 };




/** @function main */
int main( int argc, const char** argv )
{
       // 1. Read Input Image
	Mat frame = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	// 2. Load the Strong Classifier in a structure called `Cascade'
	if( !cascade.load( cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

	// 3. Detect Faces and Display Result
	detectAndDisplay( frame );

	correct_face( frame );

	int correct = pfIOU();
	double precision = (double) correct / faces.size();
	double recall = (double) correct / n;
	f1score(precision, recall);

	// 4. Save Result Image
	//imwrite( "detected1.jpg", frame );
	//imwrite( "cascadetected.jpg", frame );

	return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
	//std::vector<Rect> faces;
	Mat frame_gray;

	// 1. Prepare Image by turning it into Grayscale and normalising lighting
	cvtColor( frame, frame_gray, CV_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray );

	// 2. Perform Viola-Jones Object Detection
	cascade.detectMultiScale( frame_gray, faces, 1.1, 1, 0|CV_HAAR_SCALE_IMAGE, Size(50, 50), Size(500,500) );

       // 3. Print number of Faces found
	std::cout << "Detected faces:" << faces.size() << std::endl;

       // 4. Draw box around faces found
	for( int i = 0; i < faces.size(); i++ )
	{
		rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar( 0, 255, 0 ), 2);
	}

}

// correct Faces
void correct_face(Mat frame) {
	for (int i = 0; i < n; i++) {
		rectangle(frame, Point(truex[i], truey[i]), Point(truex[i] + width[i],
			        truey[i] + height[i]), Scalar(0, 0, 255), 2);
						}
}

double inter_over_union(int X, int Y, int W, int H) {
	double final_IOU = 0;
	for (int i = 0; i < faces.size(); i++) {
		int a = max(faces[i].x, X);
		int b = min(faces[i].y, Y);
		int c = min(faces[i].x + faces[i].width, X + W);
		int d = max(faces[i].y + faces[i].height, Y + H);
		int width = c - a;
		int height = d - b;
		if (width < 0) {
			width = 0;
		}
		if (height < 0){
			height = 0;
		}
		int intersection = width * height;

		int G_area = faces[i].width * faces[i].height;
		int R_area = W * H;

		int Union = G_area + R_area - intersection;

		double IOU = (double) intersection / (double) Union;

//红框和绿框比较，取IOU较大的作为final
		final_IOU = IOU >= final_IOU ? IOU : final_IOU;
	}
	return final_IOU;
}


int pfIOU() {
	int correct = 0;

	//double threshold = 0.5;
	for (int i = 0; i < n; i++) {
		double result = inter_over_union(truex[i], truey[i], width[i], height[i]);
		if (result >= 0.7) {
			correct++;
		}
	}
	std::cout << "Num of correctly detected faces:" << correct << std::endl;
	return correct;
}


// precision: 精准度 正绿 / 所有绿 == TP/TP+FP
// recall： 召回率 正绿 / 所有红   == TP/TP+FN

double f1score(double precision, double recall) {
	double f1score = 2 * ((precision * recall) / ( precision + recall));
	std::cout << "F1score is: " << f1score << std::endl;
	return f1score;
}
