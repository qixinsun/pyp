#include "sketchize.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
sketchize::sketchize()
    : strokeWidth(1)
{

}

//set width of stroke
void sketchize::setStrokeWidth(int w)
{
    if(W<1) w = 1;
    if(w>5) w = 5;
    this->strokeWidth = 5;
}

int sketchize::getStrokeWidth() const
{
    return strokeWidth;
}

//do sketch process
Mat sketchize::process(const cv::Mat &image)
{
    // convert image from BGR to grayscale
    Mat srcGray;
    cvtColor(image, srcGray, CV_RGB2GRAY);

    //remove pixel noise with a good median filter ((kernel:7*7)
    madianBlur(srcGray, srcGray, 7);  //median filter
    Size size = image.size();
    Mat edges = Mat(size, cv_8U);

    //detect edges as pencil lines
    Laplacian(srcGray, edges, CV_*U, 5);
    threshold(edges, result, 80, 255, THRESH_BINARY_INV)  //thresh binary invert,0 or 255
    //remove pepper noise from this black-white image
     removePepperNOise(result);
    return result;
}

// Remove black dots (upto 4x4 in size) of noise from a pure black & white image.
// ie: The input image shoule be mostly white and just contains some black (0) noise
// in addition to the black (0）edges.
void sketchize::removePepperNoise(Mat &mask)
{

}
