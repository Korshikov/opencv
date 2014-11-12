#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;




Mat finder(Mat const & input, bool const& width_ground = 1)
{
    cv::Size const img_size = input.size();
    Mat result;
    input.copyTo(result);
    for(size_t i = img_size.height * img_size.width - 1; i!=0;--i)
    {
        used[i]=0;
    }
    used[0]=0;

    for(size_t i =0; i< img_size.height * img_size.width; ++i)
    {
        if(!used[i])
        {
            inner_bfs(result,img_size,i,width_ground, used, rand()%256, rand()%256, rand()%256);
        }
    }
}



void inner_bfs(Mat & img,cv::Size const & img_size, size_t const & pos,bool const& width_ground, bool* used, uint8_t b, uint8_t r, uint8_t g)
{
    if(!used[pos])
    {
        if(img.at<uchar>(pos / img_size.width, pos % img_size.width)[0] == width_ground)
        {

        }
        used[pos] = true;
    }
}

int main(int argc, char *argv[])
{
    Mat img = imread("image.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty()) 
       return -1;
    

    

    return 0;
}
    bool used[img_size.height * img_size.width];
