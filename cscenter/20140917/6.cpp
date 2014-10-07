#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main(int argc, char *argv[])
{
    Mat img = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty()) 
       return -1;
    cv::Size lenaSize = img.size();

    Mat hsv;

    cvtColor(img,hsv,CV_BGR2HSV);
    
    Mat planes[3];
    split(hsv,planes);

    planes[1] = 255;
    planes[2] = 255;
    //planes[0] = 255;

    
    merge(planes,3,hsv);

    Mat result;
    cvtColor(hsv,result,CV_HSV2BGR);




    //absdiff(gray,img,result);

    namedWindow( "LenaLeft", CV_WINDOW_AUTOSIZE );
    imshow("LenaLeft", result);
    imwrite("LenaRGBHSV.jpg",result);
    waitKey(0);

    return 0;
}
