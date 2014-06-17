#include"diptool.h"
#include <qmath.h>
#include <tchar.h>

void DIPTool::updateImagedisplay(IplImage *srcImage)
{
     image =*( IplImageToQImage(srcImage) );

     label ->setPixmap(QPixmap::fromImage(image));
     label->show();

}


void DIPTool::grayScaleValue()
{

    IplImage * srcImage =QImageToIplImage(image) ;
    IplImage * tempImage;
    tempImage =  cvCloneImage(srcImage);


    CvSize size = cvGetSize(srcImage);
    int maxGrayValue = qPow(2, srcImage ->depth);


    CvScalar s;
    for(int i = 0; i < size.height; ++i)
        for(int j = 0; j < size.width; ++j)
        {
            s = cvGet2D(tempImage,i,j); // get the (i,j) pixel value
            s.val[0]=maxGrayValue -  s.val[0];
            s.val[1]=maxGrayValue -  s.val[1];
            s.val[2]=maxGrayValue -  s.val[2];
            cvSet2D(tempImage, i, j, s);//set the (i,j) pixel value
        }


    updateImagedisplay(tempImage);
    isModified = true;


}



void DIPTool::avergeFilter()
{
    IplImage * srcImage =QImageToIplImage(image);
    IplImage * resultImage = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_8U, srcImage->nChannels);

    cvSmooth(srcImage, resultImage, CV_BLUR, 3, srcImage ->nChannels);

   updateImagedisplay(resultImage);
   isModified = true;

}



void DIPTool::medianFilter()
{
    IplImage * srcImage = QImageToIplImage(image);
    IplImage * resultImage = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_8U, srcImage->nChannels);

    cvSmooth(srcImage, resultImage, CV_MEDIAN, 3, srcImage ->nChannels);

    updateImagedisplay(resultImage);
    isModified = true;

}


void DIPTool::gaussFilter()
{
    IplImage * srcImage = QImageToIplImage(image);
    IplImage * resultImage = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_8U, srcImage->nChannels);

    cvSmooth(srcImage, resultImage, CV_GAUSSIAN, 3, srcImage ->nChannels);

    updateImagedisplay(resultImage);
    isModified = true;

}

void DIPTool::sobelSharpFilter()
{
    Mat iImage = QImageToIplImage(image);
    if(!iImage.data)
        return ;

    Mat result;
    sobelSharpFilterHelper(iImage, result);

    IplImage resultTemp= result;
    IplImage * resultImage= & resultTemp;

    updateImagedisplay(resultImage);
    isModified = true;

}



void DIPTool::sobelSharpFilterHelper(Mat &img, Mat &result)
{
        result.create(img.size(), img.type());
        //处理边界内部的像素点, 图像最外围的像素点应该额外处理
        for (int row = 1; row < img.rows-1; row++)
        {
            //前一行像素点
            const uchar* previous = img.ptr<const uchar>(row-1);
            //待处理的当前行
            const uchar* current = img.ptr<const uchar>(row);
            //下一行
            const uchar* next = img.ptr<const uchar>(row+1);
            uchar *output = result.ptr<uchar>(row);
            int ch = img.channels();
            int starts = ch;
            int ends = (img.cols - 1) * ch;
            for (int col = starts; col < ends; col++)
            {
                //输出图像的遍历指针与当前行的指针同步递增, 以每行的每一个像素点的每一个通道值为一个递增量, 因为要考虑到图像的通道数
                *output++ = saturate_cast<uchar>(5 * current[col] - current[col-ch] - current[col+ch] - previous[col] - next[col]);
            }
        } //end loop
        //处理边界, 外围像素点设为 0
        result.row(0).setTo(Scalar::all(0));
        result.row(result.rows-1).setTo(Scalar::all(0));
        result.col(0).setTo(Scalar::all(0));
        result.col(result.cols-1).setTo(Scalar::all(0));

}




