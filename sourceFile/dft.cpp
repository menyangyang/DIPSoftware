#include "diptool.h"

void DIPTool::fftConvert()
{
     IplImage * tempImage = cvCreateImage(cvGetSize(QImageToIplImage(image)), IPL_DEPTH_8U, 1);
     cvCvtColor(QImageToIplImage(image), tempImage, CV_BGR2GRAY);

       Mat img =tempImage;
       if( img.empty() )
            return ;
       int M = getOptimalDFTSize( img.rows );                               // 获得最佳DFT尺寸，为2的次方
       int N = getOptimalDFTSize( img.cols );                                 //同上
       Mat padded;
       copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0));   // opencv中的边界扩展函数，提供多种方式扩展

       Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};          // Mat 数组，第一个为扩展后的图像，一个为空图像，
       Mat complexImg;
       merge(planes, 2, complexImg);                                                                              // 合并成一个Mat

       dft(complexImg, complexImg);                                                                              // FFT变换， dft需要一个2通道的Mat

       // compute log(1 + sqrt(Re(DFT(img))**2 + Im(DFT(img))**2))
       split(complexImg, planes);                                                                                     //分离通道， planes[0] 为实数部分，planes[1]为虚数部分
       magnitude(planes[0], planes[1], planes[0]);                                                          // 求模
       Mat mag = planes[0];
       mag += Scalar::all(1);
       log(mag, mag);                                                                                                      // 模的对数

       // crop the spectrum, if it has an odd number of rows or columns
       mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));                                        //保证偶数的边长

       int cx = mag.cols/2;
       int cy = mag.rows/2;

       // rearrange the quadrants of Fourier image                                                        //对傅立叶变换的图像进行重排，4个区块，从左到右，从上到下 分别为q0, q1, q2, q3
       // so that the origin is at the image center                                                          //  对调q0和q3, q1和q2
       Mat tmp;
       Mat q0(mag, Rect(0, 0, cx, cy));
       Mat q1(mag, Rect(cx, 0, cx, cy));
       Mat q2(mag, Rect(0, cy, cx, cy));
       Mat q3(mag, Rect(cx, cy, cx, cy));

       q0.copyTo(tmp);
       q3.copyTo(q0);
       tmp.copyTo(q3);

       q1.copyTo(tmp);
       q2.copyTo(q1);
       tmp.copyTo(q2);

       normalize(mag, mag, 0, 1, CV_MINMAX);                                                           // 规范化值到 0~1 显示图片的需要


       imshow("DFT", mag);

}
