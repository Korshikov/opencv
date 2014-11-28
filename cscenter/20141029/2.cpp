#include <algorithm>
#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;


int main(int argc, char *argv[])
{
    Mat img = imread("image.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty()) 
       return -1;
    
    int res[img.rows][img.cols];
    for(int i=0;i<img.rows;++i)
    {
        for(int t=0;t<img.cols;++i)
        {
            res[i][t] = 0;
        }
    }


    int counter = 0;
    for(int i=0;i<img.rows;++i)
    {
        for(int t=0;t<img.cols;++i)
        {
            if(img.at<double>(i,t)==0)
            {
                continue;
            }
            res[i][t] = ++counter;
            if(i > 0)
            {
                if((img.at<double>(i,t)==img.at<double>(i-1,t))&&(res[i-1][t]!=0))
                {
                    res[i][t] = res[i-1][t];
                    continue;
                }
                
            }
            if(t > 0)
            {
                if((img.at<double>(i,t)==img.at<double>(i,t-1))&&(res[i][t-1]!=0))
                {
                    res[i][t] = res[i][t-1];
                    continue;
                }
                
            }
            if((t > 0)&&(i > 0))
            {
                if((img.at<double>(i,t)==img.at<double>(i-1,t-1))&&(res[i-1][t-1]!=0))
                {
                    res[i][t] = res[i][t-1];
                    continue;
                }
                
            }
        }
    }


    for(int i=0;i<img.rows;++i)
    {
        for(int t=0;t<img.cols;++i)
        {
            res[i][t] = std::min(res[i][t],
                std::min((i>0?res[i-1][t]:counter),
                    std::min((t>0?res[i][t-1]:counter),
                        std::min((t>0&&i>0?res[i-1][t-1]:counter),
                            std::min((i<img.rows-1?res[i+1][t]:counter),
                                std::min((t<img.cols-1?res[i][t+1]:counter),
                                    std::min((t<img.cols-1&&i<img.rows-1?res[i+1][t+1]:counter),
                                        std::min(
                                            (t>0&&i<img.rows-1?res[i+1][t-1]:counter),
                                            (t<img.cols-1&&i>0?res[i-1][t+1]:counter)))))))));
        }
    }

        

    return 0;
}
