#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main(int argc, char *argv[])
{
    Mat img = imread("coins_2.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty()) 
       return -1;
    cv::Size lenaSize = img.size();

    Mat A = getStructuringElement(MORPH_ELLIPSE,Size(3,3),Point(1,1));

 
    Mat res;
        img.copyTo(res);    

        //morphologyEx(res,res,CV_MOP_CLOSE,A,Point(-1,-1),1);
        dilate(res,res,A,Point(-1,-1),3);
        for(int i = 0;i<128;++i)
        {
            erode(res,res,A,Point(-1,-1),1);
            max(res,img,res);
        }

            imshow("res",res);
            waitKey(50);

    /*Mat res2;
    Mat B = getStructuringElement(CV_SHAPE_RECT,Size(1,5),Point(0,3));

        img.copyTo(res2);

        morphologyEx(res2,res2,CV_MOP_CLOSE,B,Point(-1,-1),2);
        
        imshow("res2",res2);
        waitKey(50);*/

    Mat result;
        bitwise_not(res,res);
        imshow("res",res);
        waitKey(0);
        bitwise_and(res,img,result);
        imshow("result",result);
        waitKey(0);
        bitwise_not(res,res);
        imshow("res",res);
        waitKey(0);
        add(res,result,result);
        imshow("result",result);
        waitKey(0);

        //imwrite("teble_without_text.jpg",result);
        


    

    return 0;
}
