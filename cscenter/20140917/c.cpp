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


    Mat planes[3];
    Mat result;
    split(img,planes);


    cvtColor(img,result,CV_BGR2Lab);
    

    Mat XYZ[3];
    XYZ[0]= planes[0]*0.180423+planes[1]*0.357580+planes[2]*0.412453;
    XYZ[1]= planes[0]*0.072169+planes[1]*0.715160+planes[2]*0.212671;
    XYZ[2]= planes[0]*0.950227+planes[1]*0.119193+planes[2]*0.019334;



    //absdiff(gray,img,result);

    namedWindow( "LenaLeft", CV_WINDOW_AUTOSIZE );
    imshow("LenaLeft", result);
//    imwrite("b.jpg",result);
    waitKey(0);

    return 0;
}
