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
    imwrite("LenaBlue.jpg",planes[0]);
    imwrite("LenaGreen.jpg",planes[1]);
    imwrite("LenaRed.jpg",planes[2]);
    return 0;
}



