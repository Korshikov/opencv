#include <cstdio>
#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;


Mat salt_and_pepper(Mat const & input,double p,double q)
{
    Mat result;
    input.copyTo(result);
    for(int y(result.rows - 1); y >= 0; --y)
    {
        unsigned char *const scanLine( result.ptr<unsigned char>(y) );

        for(int x(result.cols - 1); x >= 0 ; --x)
        {
            if(rand() < RAND_MAX * p)
            {
                scanLine[x] = 0;
            }
            if(rand() < RAND_MAX * q)
            {
                scanLine[x] = 255;
            }
        }
    }
    return result;
}

Mat awgn(Mat const& input, unsigned int mean, unsigned int stddev)
{
    Mat result;
    input.copyTo(result);
    randn(result,mean,stddev);
    return input+result;
}

int main(int argc, char *argv[])
{
    Mat img = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty()) 
       return -1;
    cv::Size lenaSize = img.size();

    Mat chanals[3],ma;

    img.copyTo(ma);
    split(img,chanals);

    imwrite("4.1_chanal_mean_ecval_0_stddev_ecval_30.jpg",awgn(chanals[0],0,30));
    imwrite("4.2_chanal_mean_ecval_0_stddev_ecval_30.jpg",awgn(chanals[1],0,30));
    imwrite("4.3_chanal_mean_ecval_0_stddev_ecval_30.jpg",awgn(chanals[2],0,30));

    imwrite("4.1_chanal_mean_ecval_0_stddev_ecval_60.jpg",awgn(chanals[0],0,60));
    imwrite("4.2_chanal_mean_ecval_0_stddev_ecval_60.jpg",awgn(chanals[1],0,60));
    imwrite("4.3_chanal_mean_ecval_0_stddev_ecval_60.jpg",awgn(chanals[2],0,60));

    imwrite("4.1_chanal_mean_ecval_50_stddev_ecval_30.jpg",awgn(chanals[0],50,30));
    imwrite("4.2_chanal_mean_ecval_50_stddev_ecval_30.jpg",awgn(chanals[1],50,30));
    imwrite("4.3_chanal_mean_ecval_50_stddev_ecval_30.jpg",awgn(chanals[2],50,30));
    /*imshow("lena", img);
    randn(img,0,30);
    imshow("lenaLeft",ma + img);
    randn(img,0,60);
    imshow("lenaLeft2",ma + img);
    randn(img,50,30);
    imshow("lenaLeft3",ma + img);
    

    waitKey(0);*/
    return 0;   
}
