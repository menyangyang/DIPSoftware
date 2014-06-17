#include"diptool.h"
#include <tchar.h>


void DIPTool::imageThin()
{
    IplImage * frame;
    IplImage *srcFrame;
    IplImage *tempFrame;
    IplImage *resultFrame;

    frame = QImageToIplImage(image);
    CvSize size = cvGetSize(frame);

    if(!frame)
    {
        printf("Can not find the image!");
        return ;
    }

    srcFrame =  cvCreateImage(size, frame ->depth, 1);
    cvCvtColor(frame, srcFrame, CV_BGR2GRAY);

    tempFrame = cvCloneImage(srcFrame);
    resultFrame = cvCreateImage(cvGetSize(srcFrame), srcFrame ->depth, srcFrame ->nChannels);
    cvZero(resultFrame);
    cvThreshold(srcFrame, tempFrame, 68, 1, CV_THRESH_BINARY_INV);

    int iter = 100;

    thinMethod(tempFrame, resultFrame ,iter);

    cvReleaseImage(&resultFrame);
    cvReleaseImage(&srcFrame);
    cvReleaseImage(&tempFrame);


}


void DIPTool::thinMethod(IplImage *srcImage, IplImage *resultImage, int itera)
{
            CvSize size = cvGetSize(srcImage);
            cvCopy(srcImage, resultImage);

            cvNamedWindow("Thining",1);


            int p[10];
            for(int t = 1; t < itera; ++t)
            {
                IplImage * tempImage = cvCloneImage(resultImage);
                for(int i = 0; i < size.height; ++i)
                    for(int j = 0; j < size.width; ++j)
                    {

                        if(CV_IMAGE_ELEM(tempImage, uchar, i, j)==1)
                        {
                            for(int t = 0; t < 10; ++t)
                                p[t] = 0;
                            getNeighbourhood(tempImage,p, i, j);

                            if((p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]+p[9])>1 && (p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]+p[9])<7)
                            {
                                if(p[0] == 1)
                                {
                                    if(!(p[2]&&p[4]&&p[6]))
                                        if(!(p[4]&&p[6]&&p[8]))
                                            CV_IMAGE_ELEM(resultImage, uchar, i, j) = 0;
                                }

                            }

                        }

                    }


                    cvReleaseImage(&tempImage);

                    tempImage = cvCloneImage(resultImage);

                    for(int i = 0; i < size.height; ++i)
                        for(int j = 0; j < size.width; ++j)
                        {   if(CV_IMAGE_ELEM(tempImage, uchar, i, j)==1)
                            {
                                for(int t = 0; t < 10; ++t)
                                p[t] = 0;

                                getNeighbourhood(tempImage,p, i,j);

                                if((p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]+p[9])>1 && (p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]+p[9])<7)
                                {
                                    if(p[0] == 1)
                                    {
                                      if(!(p[2]&&p[4]&&p[8]))
                                        if(!(p[2]&&p[6]&&p[8]))
                                            CV_IMAGE_ELEM(resultImage, uchar, i, j) = 0;
                                    }

                                 }

                            }

                        }

                ///输出视频
                for(int i = 0; i < size.height; ++i)
                    for(int j = 0; j < size.width; ++j)
                    {
                        if(CV_IMAGE_ELEM(resultImage, uchar, i, j) == 1)
                            CV_IMAGE_ELEM(tempImage, uchar, i, j) =0;
                        else
                            CV_IMAGE_ELEM(tempImage, uchar, i, j) =255;

                    }

                cvShowImage("Thining",tempImage);
                cvWaitKey(11);

                cvReleaseImage(&tempImage);
            }



}


void DIPTool::getNeighbourhood(IplImage *Image, int *p, int i, int j)
{

    CvSize size = cvGetSize(Image);
    p[2] = (i==0)?0:CV_IMAGE_ELEM(Image,uchar, i-1, j);
    p[3] = (i==0 || j==size.width-1)?0:CV_IMAGE_ELEM(Image,uchar, i-1, j+1);

    if(p[2] == 0 && p[3] == 1)
        p[0]++;

    p[4] = (j == size.width-1)?0:CV_IMAGE_ELEM(Image, uchar, i, j+1);
    if(p[4] == 1&&p[3] == 0)
        p[0]++;

    p[5] = (i==size.height-1 || j==size.width-1)?0:CV_IMAGE_ELEM(Image, uchar, i+1, j+1);
    if(p[4]==0&&p[5]==1)
        p[0]++;

    p[6] = (i == size.height-1)?0:CV_IMAGE_ELEM(Image , uchar, i+1, j);
    if(p[5] == 0&&p[6] == 1)
        p[0]++;;

    p[7] = (i==size.height-1 || j==0)?0:CV_IMAGE_ELEM(Image,uchar,i+1,j-1);
    if(p[6]==0 && p[7]==1)
        p[0]++;;
    p[8] = (j==0)?0:CV_IMAGE_ELEM(Image,uchar,i,j-1);
    if(p[7]==0 && p[8]==1)
        p[0]++;

    p[9] = (i==0 || j==0)?0:CV_IMAGE_ELEM(Image,uchar,i-1,j-1);
    if(p[8]==0 && p[9]==1)
        p[0]++;
    if(p[9]==0 && p[2]==1)
        p[0]++;

}
