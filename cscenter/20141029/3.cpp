#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main(int argc, char *argv[])
{
    Mat img = imread("table.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty()) 
       return -1;
    cv::Size lenaSize = img.size();

 
    //unsigned morph_kernel[5][5] = {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};
    //Mat A = Mat(5, 5, CV_8UC1, &morph_kernel);
    Mat A = getStructuringElement(CV_SHAPE_RECT,Size(5,1),Point(3,0));

 
    Mat res;
    //for(int i=0;i<128;++i) {
        img.copyTo(res);    

        morphologyEx(res,res,CV_MOP_CLOSE,A,Point(-1,-1),64);
        
        imshow("res",res);
        waitKey(50);
    //}

    Mat res2;
    /*unsigned morph_kernel2[5][5] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
    Mat B = Mat(5, 5, CV_8UC1, &morph_kernel);*/
    Mat B = getStructuringElement(CV_SHAPE_RECT,Size(1,5),Point(0,3));

    //for(int i=0;i<128;++i) {
        img.copyTo(res2);

        morphologyEx(res2,res2,CV_MOP_CLOSE,B,Point(-1,-1),64);
        
        imshow("res2",res2);
        waitKey(50);
    //}

    Mat result;
        bitwise_and(res,res2,result);

        imwrite("teble_without_text.jpg",result);
        waitKey(0);
        


    

    return 0;
}
