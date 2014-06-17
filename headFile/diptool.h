#ifndef DIPTOOL_H
#define DIPTOOL_H
#include <QLabel>
#include <QScrollArea>
#include <QWidget>
#include <QMainWindow>
#include <QMessageBox>
#include<QFileDialog>
#include <opencv2/opencv.hpp>


#define iFilterSize 8

using namespace cv;



class DIPTool : public QMainWindow
{
    Q_OBJECT
public:
    explicit DIPTool(QWidget *parent = 0);

    ///*************************************basic file operate***************************
    bool okToCountinue();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    bool load(const QString &fileName);
    bool closeEvent();
    void updateImagedisplay(IplImage *srcImage);
    void resetImage();

    QImage  getImage()
    {
        return image;
    }

    QString  getCurFileName()
     {
        return curFile;
    }

    void setCurrentFile(const QString &fileName);


    //convert QImage and IplImage
    QImage * IplImageToQImage(IplImage *pIplImage);
    IplImage *QImageToIplImage(QImage qImage);


    ///************************* *pixl domain **********************************

    //GRAY value change
    void grayScaleValue();


    //thining image
    void imageThin();
    void thinMethod(IplImage *srcImage, IplImage* resultImage, int itera);
    void getNeighbourhood(IplImage * Image, int *p,int i, int j);



     //averge filter

    void avergeFilter();
    void avergeFilterHelper(IplImage *& srcImage, CvScalar *p, int i, int j);
    void getNerborElemValue(IplImage * srcImage, CvScalar *p, int i, int j);

    //median filter
    void medianFilter();
    void medianFilterHelper(IplImage *& srcImage, CvScalar *p, int i, int j);

    //gauss filter
    void gaussFilter();


    //Robel Sharp
    void robelSharpFilter();
    void robelSharpFilterHelper(IplImage *& srcImage, CvScalar *p, int i, int j);

   //Sobel Sharp
    void sobelSharpFilter();
    void sobelSharpFilterHelper(Mat &img, Mat &result);


    //morphology handle
    void corrosionFilter();
    void expansionFilter();
    void openMorphology();
    void closeMorphology();


   //add noise
    void addGuassianNoise();
    void addSaltPepperNoise();




    ///**************************frequence domain******************************************
    void fftConvert();


private:

    bool isModified;

    QLabel * label;
    QImage  image;
    QScrollArea * scrollArea;

    QString curFile;

signals:

public slots:

};

#endif // DIPTOOL_H
