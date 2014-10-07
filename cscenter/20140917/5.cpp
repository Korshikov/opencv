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

    Mat gray;

    cvtColor(img,gray,CV_BGR2GRAY);
    cvtColor(gray,gray,CV_GRAY2BGR);

    Mat result;

    absdiff(gray,img,result);

    imwrite("LenaDifference.jpg",result);
    return 0;
}



