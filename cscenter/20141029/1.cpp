#include <cstdio>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv; 



int main( int argc, char** argv )
{

  	Mat img,res,b1,b2;	

  	
  	img = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);

  	//imshow("e",img);

    float init_kernel_hor[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    Mat kernel_hor(3,3,CV_32F,&init_kernel_hor);
    
    filter2D(img,b1,-1,kernel_hor/9);

    //imshow("r",b1);
    
    float init_kernel_ver[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    Mat kernel_ver(3,3,CV_32F,&init_kernel_hor);
    
    filter2D(img,b2,-1,kernel_ver/9);

    //imshow("e",b2);

    res = b1+b2;
  	imwrite("lena_counter_grad.jpg",res);
    
    /*imshow("res",res);
    waitKey(0);*/

    Laplacian(img,res,-1);
    imwrite("lena_counter_laplacian.jpg",res);
    
    /*imshow("res",res);
    waitKey(0);*/

    morphologyEx(img,res,MORPH_GRADIENT,getStructuringElement(MORPH_RECT,Size(3,3),Point(1,1)),Point(-1,-1),1,BORDER_REPLICATE);
    imwrite("lena_counter_morphology.jpg",res);


    cvtColor(img,img,CV_RGB2GRAY);
    vector<Vec4i> hierarchy;
    findContours(img,res,hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    
    imshow("res",res);
    waitKey(0);




    return 0;

}