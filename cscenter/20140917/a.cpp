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
        split(img,planes);
        
        Mat res[3],result;

        res[0]=planes[0];
        res[2]=planes[1];
        res[1]=planes[2];
        
        
        merge(res,3,result);
    
        imwrite("1.jpg",result);
        
        res[1]=planes[0];
        res[0]=planes[1];
        res[2]=planes[2];
        
        
        merge(res,3,result);
    
        imwrite("2.jpg",result);
    
        res[1]=planes[0];
        res[2]=planes[1];
        res[0]=planes[2];
        
        
        merge(res,3,result);
    
        imwrite("3.jpg",result);
    
        res[2]=planes[0];
        res[0]=planes[1];
        res[1]=planes[2];
        
        
        merge(res,3,result);
    
        imwrite("4.jpg",result);
    
        res[2]=planes[0];
        res[1]=planes[1];
        res[0]=planes[2];
        
        
        merge(res,3,result);
    
        imwrite("5.jpg",result);
    
        res[0]=planes[0];
        res[1]=planes[1];
        res[2]=planes[2];
        
        
        merge(res,3,result);
    
        imwrite("6.jpg",result);
    
    return 0;
}
