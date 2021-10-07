#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;
using namespace cv;

#define threshold 130
#define gap_min 10
#define min_r 30
#define max_r 100
#define r_diff_max 90

void find_circle(Mat source_image, Mat img_th);
void correct_darts(Mat source_image);

std::vector<Rect> darts;
//dart 0 -- dart
//int n = 1;
//int truex[] = { 445 };
//int truey[] = { 20 };
//int width[] = { 152 };
//int height[] = { 170 };


//dart 1
int n = 1;
int truex[] = { 198 };
int truey[] = { 133 };
int width[] = { 190 };
int height[] = { 190 };

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
//int n = 2;
//int truex[] = { 122, 985 };
//int truey[] = { 105, 94 };
//int width[] = { 122, 124 };
//int height[] = { 125, 123 };


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


int ***malloc3dArray(int dim1, int dim2, int dim3){
    int i, j, k;
    int ***array = (int ***) malloc(dim1 * sizeof(int **));

    for (i = 0; i < dim1; i++) {
    	array[i] = (int **) malloc(dim2 * sizeof(int *));
 			for (j = 0; j < dim2; j++) {
      	array[i][j] = (int *) malloc(dim3 * sizeof(int));
 			}
    }
    return array;
}

int main(int argc, const char** argv) {
    Mat image, blur_image, grey_image, img_th;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    cvtColor(image, grey_image, CV_BGR2GRAY );
    GaussianBlur( grey_image, blur_image, Size( 5, 5 ), 0, 0 );
    Canny(blur_image, img_th, 50, 200);

    find_circle(image,img_th);
    correct_darts(image);

    imwrite("HoughCircle.jpg", image);
}

void find_circle(Mat source_image, Mat img_th) {

    int height = img_th.rows;
    int width = img_th.cols;

    // += 1
    int ***accu;
    accu= malloc3dArray(height, width, max_r);
    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            for(int k=0; k<max_r; k++) {
                accu[i][j][k] = 0;
            }
        }
    }
    int x0, y0;
    double radian;
    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {
            if(img_th.at<uchar>(y,x) > 250) {
                //all possible angles
                for(int theta=0; theta<360; theta++) {
                    for(int r=min_r; r<max_r; r++) {
                        radian = (theta * 3.141592653) / 180;
                        x0 = round(x - r * cos(radian));
                        y0 = round(y - r * sin(radian));
                        if(x0>0 && x0<width && y0>0 && y0<height) {
                            accu[y0][x0][r] += 1;
                        }
                    }
                }
            }
        }
    }

///////circle
    int number = 0;
    for(int i=0; i<height; i++){
        for(int j=0; j<width;j++){
            for(int k=0; k<max_r; k++){
                if(accu[i][j][k] > threshold){
                    int vote = accu[i][j][k];
                    bool circle_max = true;

                    for(int yy=-gap_min; yy<gap_min; yy++){
                        for(int xx=-gap_min; xx<gap_min; xx++){
                            for(int rr=-gap_min; rr<gap_min; rr++){
                                if(((yy+i)>=0 && (yy+i)<=height)
																   && ((xx+j)>=0 && (xx+j)<=width)
																	 && ((rr+k)>=0 && (rr+k)<=max_r)){
                                   if(accu[yy+i][xx+j][rr+k] > vote){
                                    circle_max = false;
                                   }
                                }
                            }
                        }
                    }

////// other circles
                    int max = 0;
                    if(circle_max == true) {
                        int center_x = j;
                        int center_y = i;
                        int r = k;
                        for(int yy=-5; yy<5; yy++) {
                            for(int xx=-5; xx<5; xx++) {
                                for(int rr=5; rr<r_diff_max; rr++) {
                                    if(((yy+center_y)>=0 && (yy+center_y)<=height)
                                       && ((xx+center_x)>=0 && (xx+center_x)<=width)
                                       && ((rr+r)>=0 && (rr+r)<=max_r)){
                                       if(rr!=0 && accu[yy+center_y][xx+center_x][rr+r] > threshold){
                                          if( rr+r > max) {
                                            max = rr+r;
                                          }
                                       }
                                    }
                                }
                            }
                        }
                       if(max > k){
                          number++;
                          rectangle(source_image, Point(center_x-max, center_y-max),Point(center_x+max, center_y+max), Scalar( 0, 255, 0 ), 2);
                       }
                    }
                }
            }
        }
    }
    printf("number of circles that detetced :%d\n", number);

}

void correct_darts(Mat source_image) {
	for (int i = 0; i < n; i++) {
		rectangle(source_image, Point(truex[i], truey[i]), Point(truex[i] + width[i],
			        truey[i] + height[i]), Scalar(0, 0, 255), 2);
	}
}
