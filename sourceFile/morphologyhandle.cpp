#include"diptool.h"

void DIPTool::corrosionFilter()
{

    Mat tempImage = QImageToIplImage(image);

    Mat resultImage;

    //输入图像
    //输出图像
    //单元大小，这里是5*5的8位单元
    //腐蚀位置，为负值取核中心
    //腐蚀次数两次
    erode(tempImage,resultImage, Mat(5,5,CV_8U),Point(-1, -1),2);

    IplImage  imageTest= resultImage;

    updateImagedisplay(&imageTest);
    isModified = true;

}



void DIPTool::expansionFilter()
{
    IplImage * srcImage = QImageToIplImage(image);
    Mat tempImage = srcImage;

    Mat resultImage;

    //输入图像
    //输出图像
    //单元大小，这里是5*5的8位单元
    //膨胀位置，为负值取核中心
    //膨胀次数两次
    dilate(tempImage, resultImage, Mat(5,5,CV_8U),Point(-1, -1),1);

    IplImage imageTest= resultImage;
    updateImagedisplay(&imageTest);
    isModified = true;

}


void DIPTool::openMorphology()
{
    IplImage * srcImage = QImageToIplImage(image);
    Mat tempImage = srcImage;

    Mat resultImage ;


    //输入图像
     //输出图像
     //定义操作：MORPH_OPEN为开操作
     //单元大小，这里是3*3的8位单元
     //开闭操作位置
     //开闭操作次数

    morphologyEx(tempImage, resultImage, MORPH_OPEN, Mat(3,3,CV_8U), Point(-1, -1),1);

    IplImage imageTest= resultImage;
    updateImagedisplay(&imageTest);
    isModified = true;
}


void DIPTool::closeMorphology()
{
    IplImage * srcImage = QImageToIplImage(image);
    Mat tempImage = srcImage;

    Mat resultImage ;

    //输入图像
     //输出图像
     //定义操作：MORPH_CLOSE为闭操作
     //单元大小，这里是3*3的8位单元
     //开闭操作位置
     //开闭操作次数

    morphologyEx(tempImage, resultImage, MORPH_CLOSE, Mat(3,3,CV_8U), Point(-1, -1),1);

    IplImage imageTest= resultImage;
    updateImagedisplay(&imageTest);
    isModified = true;

}
