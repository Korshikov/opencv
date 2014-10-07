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
    split(img,planes);
    Mat res = planes[0]/3+planes[1]/3+planes[2]/3;

    imwrite("LenaGrayMean.jpg",res);
    return 0;
}



