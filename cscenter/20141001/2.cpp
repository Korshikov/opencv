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

    Mat gray;

    cvtColor(img,gray,CV_RGB2GRAY);

    Mat normal;

    normalize(gray,normal,255,0,NORM_INF);
    Mat equaliz;

    equalizeHist(gray,equaliz);

    Mat diff;

    absdiff(normal,equaliz,diff);

    Mat res;

    hconcat(gray,normal,res);
    hconcat(res,equaliz,res);
    hconcat(res,diff,res);

    imwrite("2.jpg",res);

    return 0;   
}
