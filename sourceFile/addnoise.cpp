#include"diptool.h"


void DIPTool::addGuassianNoise()
{
    float delta = 20;
    IplImage *img;
    IplImage * srcImage = QImageToIplImage(image);
    img=cvCreateImage( cvGetSize(srcImage), srcImage ->depth, srcImage ->nChannels );
    cvZero(img);
    CvRNG rng = cvRNG(0);//初始化随机数发生器
    cvRandArr(&rng, img, CV_RAND_NORMAL, cvScalarAll(0), cvScalarAll(delta));
    cvAdd(srcImage, img, srcImage);

    updateImagedisplay(srcImage);
    isModified = true;


}


void DIPTool::addSaltPepperNoise()
{
    IplImage * srcImage = QImageToIplImage(image);

    Mat tempImage = srcImage;

    Mat  saltpepper_noise = Mat::zeros(tempImage.rows, tempImage.cols, CV_8U);
    randn(saltpepper_noise, 129, 1);

    Mat black = saltpepper_noise < 126.3;
    Mat white = saltpepper_noise > 131;

    Mat resultImage = tempImage.clone();

    resultImage.setTo(255, white);
    resultImage.setTo(0, black);

    IplImage imageTest= resultImage;
    updateImagedisplay(&imageTest);

    isModified = true;


}
