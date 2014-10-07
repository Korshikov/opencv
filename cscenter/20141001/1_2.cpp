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



    Mat convert[5];
    img.convertTo(convert[0],CV_8UC1,0.5,0);
    img.convertTo(convert[1],CV_8UC1,1,-125);
    img.convertTo(convert[2],CV_8UC1,2,0);
    img.convertTo(convert[3],CV_8UC1,2,-255);
    img.convertTo(convert[4],CV_8UC1,1,125);

    Mat res[2];

    hconcat(convert[0],convert[1],res[0]);
    hconcat(convert[2],convert[3],res[1]);
    hconcat(res[1],convert[4],res[1]);

    imwrite("lenaConcat1.jpg",res[0]);
    imwrite("lenaConcat2.jpg",res[1]);


    waitKey(0);

    return 0;
}
