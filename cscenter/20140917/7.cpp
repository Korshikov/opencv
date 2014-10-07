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

    
    
    {   
        Mat planes[3];
        split(img,planes);
        
        planes[0] = Mat::zeros(img.rows,img.cols,CV_8UC1);
        
        Mat result;
        merge(planes,3,result);
    
        imwrite("LenaMinusBlue.jpg",result);
    }

    
    {   
        Mat planes[3];
        split(img,planes);
        
        planes[1] = Mat::zeros(img.rows,img.cols,CV_8UC1);
        
        Mat result;
        merge(planes,3,result);
    
        imwrite("LenaMinusGreen.jpg",result);
    }

    
    {   
        Mat planes[3];
        split(img,planes);
        
        planes[2] = Mat::zeros(img.rows,img.cols,CV_8UC1);
        
        Mat result;
        merge(planes,3,result);
    
        imwrite("LenaMinusRed.jpg",result);
    }

    return 0;
}
