#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main(int argc, char *argv[])
{
    Mat img = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty()) 
       return -1;
    Size lenaSize = img.size();
    

    Mat rightDownLena = img(Rect(lenaSize.width/2,lenaSize.height/2,lenaSize.width/2,lenaSize.height/2)).clone();
    Mat rightUpLena = img(Rect(lenaSize.width/2,0,lenaSize.width/2,lenaSize.height/2)).clone();

    rightUpLena.copyTo(img(Rect(lenaSize.width/2,lenaSize.height/2,lenaSize.width/2,lenaSize.height/2)));
    rightDownLena.copyTo(img(Rect(lenaSize.width/2,0,lenaSize.width/2,lenaSize.height/2)));

    namedWindow("original", CV_WINDOW_AUTOSIZE);
    
    imshow("original", img);

    imwrite("LenaMixed.jpg",img);

    
    waitKey(0);
    return 0;
}



