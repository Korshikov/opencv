#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

# define M_PIl          3.141592653589793238462643383279502884L /* pi */
# define M_PI           3.14159265358979323846  /* pi */

struct coin
{
    unsigned pixelCounter;
    unsigned posX; // pos of center
    unsigned posY;

    coin(unsigned pixelCounter = 0, unsigned posX = 0, unsigned posY = 0):pixelCounter(pixelCounter),posX(posX),posY(posY){}

    bool operator<(coin rhs)
    {
        return pixelCounter < rhs.pixelCounter;
    }
};



int main(int argc, char *argv[])
{
    Mat img = imread("coins_1.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty()) 
       return -1;
    cv::Size lenaSize = img.size();

    Mat result;

    cvtColor(img,img,CV_RGB2GRAY);
    imshow("source",img);

    threshold(img, result, 64, 255, CV_THRESH_BINARY);
 
    erode(result,result, getStructuringElement(MORPH_RECT,Size(2,2),Point(1,1)),Point(-1,-1));

    Mat res2;
    result.copyTo(res2);    
    morphologyEx(res2,res2,CV_MOP_CLOSE,getStructuringElement(MORPH_RECT,Size(3,3),Point(1,1)),Point(-1,-1),4);
    res2.copyTo(result);
    cvtColor(result,result,CV_GRAY2RGB);
        
     

    std::vector<coin> coins;
    CvScalar newColor; 

    for(int y(res2.rows - 1); y >= 0; --y)
    {
        unsigned char *const scanLine( res2.ptr<unsigned char>(y) );

        for(int x(res2.cols - 1); x >= 0 ; --x)
        {
            if(scanLine[x] == 255)
            {
                newColor = CV_RGB(std::rand()%246 +5,std::rand()%246+5,std::rand()%246+5); //for never rand = 255
                unsigned scvear =  floodFill(res2, Point(x,y), newColor);
                unsigned radius = (unsigned) std::sqrt(scvear/M_PIl)+1;
                coins.push_back( coin(floodFill(result, Point(x,y-radius), newColor),x,y-radius));
            } 
        }
    }

    std::sort(coins.begin(),coins.end());
    int counter=0;
    for(std::vector<coin>::reverse_iterator  i = coins.rbegin();i!=coins.rend();++i)
    {
        
        std::string text = std::to_string(++counter);
        int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
        double fontScale = 1;
        int thickness = 3;

        int baseline=0;
        Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
        baseline += thickness;


        Point textOrg((*i).posX - (textSize.width)/2, (*i).posY + (   textSize.height)/2);

        putText(result, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
    }

    imshow("result",result);
    //imshow("res2",res2);
    imwrite("6.jpg",result);

    waitKey(0);
    
        
    return 0;
}
