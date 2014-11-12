#include <cstdio>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv; 



int main( int argc, char** argv )
{

  	Mat img,res;	

  	
  	img = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
  	cvtColor(img, img, CV_BGR2GRAY);

  	img.convertTo(img,CV_32F);
  	img = img + 1;

  	log(img,img);
  	cv::convertScaleAbs(img,res);
    cv::normalize(res,res,0,255,cv::NORM_MINMAX);

  	imwrite("log_lena.jpg",res);

  	pow(img,2,img);

  	cv::convertScaleAbs(img,res);
    cv::normalize(res,res,0,255,cv::NORM_MINMAX);


  	imwrite("sqr_lena.jpg",res);
	
  	
  	pow(img,2,img);

  	cv::convertScaleAbs(img,res);
    cv::normalize(res,res,0,255,cv::NORM_MINMAX);


  	imwrite("sqr_sqr_lena.jpg",res);

    return 0;

}