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

int main(int argc, char *argv[])
{
    Mat img = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty()) 
       return -1;
    cv::Size lenaSize = img.size();

    Mat chanals[3];

    split(img,chanals);

    imwrite("3.1_chanal_p_ecval_q_ecval_0.05.jpg",salt_and_pepper(chanals[0],0.05,0.05));
    imwrite("3.2_chanal_p_ecval_q_ecval_0.05.jpg",salt_and_pepper(chanals[1],0.05,0.05));
    imwrite("3.3_chanal_p_ecval_q_ecval_0.05.jpg",salt_and_pepper(chanals[2],0.05,0.05));

    imwrite("3.1_chanal_p_ecval_q_ecval_0.1.jpg",salt_and_pepper(chanals[0],0.1,0.1));
    imwrite("3.2_chanal_p_ecval_q_ecval_0.1.jpg",salt_and_pepper(chanals[1],0.1,0.1));
    imwrite("3.3_chanal_p_ecval_q_ecval_0.1.jpg",salt_and_pepper(chanals[2],0.1,0.1));

    imwrite("3.1_chanal_p_ecval_q_ecval_0.15.jpg",salt_and_pepper(chanals[0],0.15,0.15));
    imwrite("3.2_chanal_p_ecval_q_ecval_0.15.jpg",salt_and_pepper(chanals[1],0.15,0.15));
    imwrite("3.3_chanal_p_ecval_q_ecval_0.15.jpg",salt_and_pepper(chanals[2],0.15,0.15));
    /*imshow("lenaLeft", salt_and_pepper(chanals[0],0.5,0.5));
    

    waitKey(0);*/
    return 0;   
}
