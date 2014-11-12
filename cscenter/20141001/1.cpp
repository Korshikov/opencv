#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

Mat change(const Mat img)
{
    Mat res;
    img.copyTo(res);
    res = 2*res+100;
    return res;
}

int main(int argc, char *argv[])
{
    Mat img = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty()) 
       return -1;
    cv::Size lenaSize = img.size();

    Mat lenaLeft = change(img);


    Mat convert;
    img.convertTo(convert,CV_8UC1,2,100);
    
    absdiff(convert,lenaLeft,img);

    return 0;
}
