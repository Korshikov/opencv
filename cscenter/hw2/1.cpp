#include <cstdio>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv; 

void shiftDFT(Mat& fImage )
{
  	Mat tmp, q0, q1, q2, q3;

	fImage = fImage(Rect(0, 0, fImage.cols & -2, fImage.rows & -2));

	int cx = fImage.cols/2;
	int cy = fImage.rows/2;

	q0 = fImage(Rect(0, 0, cx, cy));
	q1 = fImage(Rect(cx, 0, cx, cy));
	q2 = fImage(Rect(0, cy, cx, cy));
	q3 = fImage(Rect(cx, cy, cx, cy));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}

Mat csmd(Mat& complexImg, bool rearrange)
{
    Mat planes[2];
    split(complexImg, planes);
    magnitude(planes[0], planes[1], planes[0]);

    Mat mag = (planes[0]).clone();
    mag += Scalar::all(1);
    log(mag, mag);

    if (rearrange)
    {
        shiftDFT(mag);
    }

    normalize(mag, mag, 0, 1, CV_MINMAX);

    return mag;

}

void clpf(Mat &dft_Filter, int D, int n)
{
	Mat tmp = Mat(dft_Filter.rows, dft_Filter.cols, CV_32F);

	Point centre = Point(dft_Filter.rows / 2, dft_Filter.cols / 2);
	double radius;

	for(int i = 0; i < dft_Filter.rows; i++)
	{
		for(int j = 0; j < dft_Filter.cols; j++)
		{
			radius = (double) sqrt(pow((i - centre.x), 2.0) + pow((double) (j - centre.y), 2.0));
			tmp.at<float>(i,j) = (float)
						( 1 / (1 + pow((double) (radius /  D), (double) (2 * n))));
		}
	}

    Mat toMerge[] = {tmp, tmp};
	merge(toMerge, 2, dft_Filter);
}


void chpf(Mat &dft_Filter, int D, int n)
{
	Mat tmp = Mat(dft_Filter.rows, dft_Filter.cols, CV_32F);

	Point centre = Point(dft_Filter.rows / 2, dft_Filter.cols / 2);
	double radius;

	for(int i = 0; i < dft_Filter.rows; i++)
	{
		for(int j = 0; j < dft_Filter.cols; j++)
		{
			radius = (double) sqrt(pow((i - centre.x), 2.0) + pow((double) (j - centre.y), 2.0));
			tmp.at<float>(i,j) = (float)
						( 1 / (1 - pow((double) (radius /  D), (double) (2 * n))));
		}
	}

    Mat toMerge[] = {tmp, tmp};
	merge(toMerge, 2, dft_Filter);
}


int main( int argc, char** argv )
{

  	Mat img, imgGray, imgOutput1,imgOutput2, result1,result2, resultImgGray;	

  	Mat padded;	
  	Mat complexImg, filter1, filterOutput1,filter2, filterOutput2,mag;
  	Mat planes[2];

  	int N, M; 

  	int radius;				
  	int order = 2;		
  	char fileName[50];

  	const int radiuses[5] = {5,15,30,255,380};		

  	img = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);


	M = getOptimalDFTSize( img.rows );
	N = getOptimalDFTSize( img.cols );

	cvtColor(img, imgGray, CV_BGR2GRAY);
	imgGray.copyTo(resultImgGray);
	resultImgGray.convertTo(resultImgGray,img.type());

	 for(int i=0;i<5;++i)
 	{
	 	radius = radiuses[i];


		copyMakeBorder(imgGray, padded, 0, M - imgGray.rows, 0,N - imgGray.cols, BORDER_CONSTANT, Scalar::all(0));
		planes[0] = Mat_<float>(padded);
		planes[1] = Mat::zeros(padded.size(), CV_32F);

		merge(planes, 2, complexImg);

		dft(complexImg, complexImg);
					

		filter1 = complexImg.clone();
		filter2 = complexImg.clone();

		clpf(filter1, radius, order);
		chpf(filter1, radius, order);

		shiftDFT(complexImg);

		mulSpectrums(complexImg, filter1, imgOutput1, 0);
		shiftDFT(imgOutput1);
		mulSpectrums(complexImg, filter1, imgOutput2, 0);
		shiftDFT(imgOutput2);
 

		mag = csmd(imgOutput1, true);
		imwrite("lpf_filter",mag);
		waitKey(0);
	    //hconcat(resultImgGray,mag,result1);		
	    mag = csmd(imgOutput2, true);
		imshow("hpf_filter",mag);
		//mag.convertTo(mag,img.type());
	    //hconcat(resultImgGray,mag,result2);
	    
		
		idft(imgOutput1, imgOutput1);
		idft(imgOutput2, imgOutput2);
				
		split(imgOutput1, planes);
		normalize(planes[0], imgOutput1, 0, 1, CV_MINMAX);		
		split(filter1, planes);
		normalize(planes[0], filterOutput1, 0, 1, CV_MINMAX);
			
		split(imgOutput2, planes);
		normalize(planes[0], imgOutput2, 0, 1, CV_MINMAX);		
		split(filter2, planes);
		normalize(planes[0], filterOutput2, 0, 1, CV_MINMAX);

		/*imgOutput1.convertTo(imgOutput1,result1.type());
		hconcat(result1,imgOutput1,result1);
		filterOutput1.convertTo(filterOutput1,result1.type());
		hconcat(result1,filterOutput1,result1);
		imgOutput2.convertTo(imgOutput2,result2.type());
		hconcat(result2,imgOutput2,result2);
		filterOutput2.convertTo(filterOutput2,result2.type());
		hconcat(result2,filterOutput2,result2);*/

		imshow("imgout_lpf",imgOutput1);
		imshow("filterout_lpf",filterOutput1);

		imshow("imgout_hpf",imgOutput2);
		imshow("filterout_hpf",filterOutput2);



		/*sprintf(fileName,"LPF_%d.jpg",radius);
		imwrite(fileName,result1 );
		sprintf(fileName,"HPF_%d.jpg",radius);
		imwrite(fileName,result2 );*/
		
	}


    return 0;

}