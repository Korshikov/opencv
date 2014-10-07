#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main(int argc, char *argv[])
{
    Mat img = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty()) 
       return -1;
    Mat lenaUp;
    cv::Size lenaSize = img.size();
    img(Rect(0,0,lenaSize.width,lenaSize.height/2)).copyTo(lenaUp);
    namedWindow( "LenaUp", CV_WINDOW_AUTOSIZE );
    imshow("LenaUp", lenaUp);
    imwrite("LenaUp.jpg",lenaUp);
    Mat lenaLeft;
    img(Rect(0,0,lenaSize.width/2,lenaSize.height)).copyTo(lenaLeft);
    namedWindow( "LenaUp", CV_WINDOW_AUTOSIZE );
    imshow("lenaLeft", lenaLeft);
    imwrite("lenaLeft.jpg",lenaLeft);
    waitKey(0);
    return 0;
}



