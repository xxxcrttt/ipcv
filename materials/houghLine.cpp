#include <stdio.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;
using namespace cv;

#define min_line 50
#define max_line 300
#define theta 360
#define line_dif 10 //difference between lines->one line
#define Pi 3.141592653

//function headers
void line_detection(Mat source_image, Mat image_th);
int **malloc2dArray(int dim1, int dim2);
void correct_face(Mat source_image);

std::vector<Rect> darts;
//dart 0 -- face


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

int **malloc2dArray(int dim1, int dim2) {
    int i, j;
    int **array = (int **) malloc(dim1 * sizeof(int *));
    for (i = 0; i < dim1; i++) {
        array[i] = (int *) malloc(dim2 * sizeof(int));
    }
    return array;
}


int main( int argc, const char** argv ){
    Mat image, grey_image, blur_image, image_th;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    cvtColor(image, grey_image, CV_BGR2GRAY );
    GaussianBlur( grey_image, grey_image, Size( 7, 7 ), 0, 0 );
    Canny(grey_image, image_th, 50, 200);

    line_detection(image,image_th);
    correct_face(image);
    imwrite("HoughLine.jpg", image);
}


void line_detection(Mat source_image, Mat image_th) {
    int img_H = image_th.rows;//whole image
    int img_W = image_th.cols;
    int diag = 0;
    diag = round(sqrt((img_H*img_H + img_W*img_W)));//小数 -> 分数

    int diag_max = diag * 2;//存储正负

    int **acc;
    acc = malloc2dArray(diag_max, theta);
    for(int i=0; i<diag_max; ++i) {
        for(int j=0; j<theta; ++j) {
            acc[i][j] = 0;
        }
    }
//////////////////////////////////////////////// first line
    for(int y=0; y<img_H; y++) {
        for(int x=0; x<img_W; x++) {
            if(image_th.at<uchar>(y,x) > 0) {
                for(int th=0; th<theta; th++) {
                    double r = y * sin((th * Pi) / 180) + x * cos((th * Pi) / 180);//r=xcos(theta)+ysin(theta)
                    int len = round(r + diag);//-ve
                    acc[len][th] += 1;
                }
            }
        }
    }
    int image[img_H][img_W][2];
    int length[max_line];
    for(int i=0; i<img_H; ++i) {
        for(int j=0; j<img_W; ++j) {
            image[i][j][0] = 0;//accumulator where it intersect
            image[i][j][1] = 0;//length of lines
        }
    }
////////////////////////////////////////////////////////////////////////adjust the first line to more accurarate
    for(int i=0; i<diag_max; i++) {
        for(int j=0; j<theta; j++) {
            if(acc[i][j] > min_line && acc[i][j] < max_line) {
                int count = acc[i][j];
                bool count_Max = true;//max count
                //找到上下左右的像素，将很多位置偏差很小的直线作为一条直线，分别检测长度和角度（x,y)
                for(int y=-line_dif; y<line_dif; y++) {//find pixels around the coordinates,
                    for(int x=-line_dif; x<line_dif; x++) {
                        if( ((y+i)>=0 && (y+i)<=diag_max) && ((x+j)>=0 && (x+j)<=theta) ) {//between the max and min lines and theta
                            if(acc[y+i][x+j] > count && acc[y+i][x+j] < max_line) {//this acc is better
                                count_Max = false;//if this is better, the previous count_max is not the best
                            }
                        }
                    }
                }

                if(count_Max) {//when find max acc(TRUE（defaut）)
                    int x0, y0, x1, y1;
                    if(j != 0) {//not perpendicular (j is dim2)
                        x0 = 0;
                        y0 = ((double)((i - diag) - (x0 * cos((j * Pi) / 180)))) / sin((j * Pi) / 180);
                        x1 = img_W - 0;//limit value, width-0
                        y1 = ((double)((i - diag) - (x1 * cos((j * Pi) / 180)))) / sin((j * Pi) / 180);
                    }//one line
                    else {//perpendicular
                        y0 = 0;
                        x0 = ((double)((i - diag) - (y0 * sin((j * Pi) / 180)))) / cos((j * Pi) / 180);
                        y1 = img_H - 0;
                        x1 = ((double)((i - diag) - (y1 * sin((j * Pi) / 180)))) / cos((j * Pi) / 180);
                    }
                    //slope
                    double slope0 = ((double)(y1-y0)/(double)(x1-x0));
                    int c0 = (y0 -slope0*x0);//y=kx+b, b intercept

                ////////////////////////////////////////////////////////////////////////PART2 second line
                    for(int a=0; a<diag_max; a++) {
                        for(int b=0; b<theta; b++) {
                            if(acc[a][b] > min_line && acc[a][b] < max_line) {
                                int count2 = acc[a][b];
                                bool count_Max2 = true;
                                for(int la=-line_dif; la<line_dif; la++) {
                                    for(int lb=-line_dif; lb<line_dif; lb++) {
                                        if( ((la+a)>=0 && (la+a)<=diag_max) && ((lb+b)>=0 && (lb+b)<=theta) ) {
                                            if(acc[la+a][lb+b] > count2 && acc[la+a][lb+b] < max_line) {
                                                count_Max2 = false;
                                            }
                                        }
                                    }
                                }
                                if(count_Max2) {
                                  if(j != 0) {
                                    x0 = 0;
                                    y0 = ((double)((a - diag) - (x0 * cos((b * Pi) / 180)))) / sin((b * Pi) / 180);
                                    x1 = img_W - 0;
                                    y1 = ((double)((a - diag) - (x1 * cos((b * Pi) / 180)))) / sin((b * Pi) / 180);
                                }
                                else {
                                    y0 = 0;
                                    x0 = ((double)((a - diag) - (y0 * sin((b * Pi) / 180)))) / cos((b * Pi) / 180);
                                    y1 = img_H - 0;
                                    x1 = ((double)((a - diag) - (y1 * sin((b * Pi) / 180)))) / cos((b * Pi) / 180);
                                }

                                double slope1 = ((double)(y1-y0)/(double)(x1-x0));
                                int c1 = (y0 -slope1*x0);
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////intersections
                                int len_dist = abs(count - count2);//difference between two lines

                                if( (double)(slope0 - slope1) != 0 && len_dist <= 40){
                                    int x_co = (c1 - c0) / (slope0 - slope1);//x coordinate
                                    int y_co = slope0 * x_co + c0;//y coordinate
                                    if (y_co>0 && y_co<img_W && x_co>0 && x_co<img_H){
                                        //circle( source_image, Point( x_co, y_co ), 1.0, Scalar( 0, 255, 0 ), 2, 8);
                                        image[x_co][y_co][0]+=1;//totel number of  intersecs
                                        image[x_co][y_co][1]+=count;//number of lines intersect
                                    }
                                  }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
//center of circle
    int max_no_lines=0;
    int square_x=0;
    int square_y=0;
    int average_len=0;
    for(int i=0; i<img_H; i++) {
        for(int j=0; j<img_W; j++) {
            if (image[i][j][0]>max_no_lines){//acc>0,number lines
                max_no_lines=image[i][j][0];
                average_len=image[i][j][1]/max_no_lines;//average line length-> find dart square
                square_x=i;//dart square
                square_y=j;
            }
        }
    }
    rectangle( source_image, Point( square_x-sqrt(2) *average_len/2, square_y-sqrt(2) *average_len/2 ),
                             Point( square_x+sqrt(2) *average_len/2, square_y+sqrt(2) *average_len/2 ),
                             Scalar( 0, 255, 0 ), 2);
}

void correct_face(Mat source_image) {
	for (int i = 0; i < n; i++) {
		rectangle(source_image, Point(truex[i], truey[i]), Point(truex[i] + width[i],
			        truey[i] + height[i]), Scalar(0, 0, 255), 2);
	}
}
