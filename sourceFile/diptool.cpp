#include "diptool.h"
#include <QFile>
#include <QCloseEvent>
#include <QPushButton>
#include<QDebug>


DIPTool::DIPTool(QWidget *parent)
{

    label = new QLabel;
    scrollArea = new QScrollArea;
    scrollArea ->setBackgroundRole(QPalette::Dark);
    scrollArea ->setWidget(label);

    setCentralWidget(scrollArea);
    setWindowTitle(tr("Image Process"));

    isModified = false;


}


bool DIPTool::okToCountinue()
{
    if( isModified )
    {
        int r = QMessageBox::warning(this, tr("DIP Tool"), tr("The image has been modified.\n""Do you want to save your changes? "), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(r == QMessageBox::Yes)
            return save();
        else if(r == QMessageBox::Cancel)
            return false;
    }

    return true;

}



bool DIPTool::load(const QString &fileName)
{

    image.load(fileName);
    if(image.isNull())
    {
        QMessageBox::information(this, tr("DIP tool"), tr("Can not load %1").arg(fileName));
        return false;

    }

    label ->setPixmap(QPixmap::fromImage(image));

    label->setGeometry(0,0, 900, 768);

    label->show();

    setCurrentFile(fileName);

    isModified = false;
    return true;
}




void DIPTool::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();

}


bool DIPTool::save()
{
    if(curFile.isEmpty())
        return saveAs();
    else
        return saveFile(curFile);
}



bool DIPTool::saveAs()
{

   QString fileName = QFileDialog::getSaveFileName(this, tr("SaveAs"), curFile);

   if(fileName.isEmpty())
       return false;

   return saveFile(fileName);

}



bool DIPTool::saveFile(const QString &fileName)
{

    QImage * iImage = &image;

    if( !iImage ->save(fileName) )
     {
         QMessageBox::information(this,
                     tr("Failed to save the image"),
                     tr("Failed to save the image!"));
     }

    isModified = false;

     return true;


}



bool DIPTool::closeEvent()
{
    if( okToCountinue() )
    {
        label ->clear();
        isModified = false;
        return true;
    }

    return false;

}


QImage * DIPTool::IplImageToQImage(IplImage *pIplImage)
{
    QImage *qImage;

    int w = pIplImage->width;
    int h = pIplImage->height;

    qImage = new QImage(w, h, QImage::Format_RGB32);

    int x, y;
    for(x = 0; x < pIplImage->width; ++x)
    {
        for(y = 0; y < pIplImage->height; ++y)
        {
            CvScalar color = cvGet2D(pIplImage, y, x);

            int r = color.val[2];
            int g = color.val[1];
            int b = color.val[0];

            qImage->setPixel(x, y, qRgb(r,g,b));
        }
    }

    return qImage;
}



IplImage * DIPTool::QImageToIplImage(QImage  qImage)
{
    int width = qImage.width();
    int height = qImage.height();
    CvSize Size;
    Size.height = height;
    Size.width = width;
    IplImage *IplImageBuffer = cvCreateImage(Size, IPL_DEPTH_8U, 3);
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            QRgb rgb = qImage.pixel(x, y);
            cvSet2D(IplImageBuffer, y, x, CV_RGB(qRed(rgb), qGreen(rgb), qBlue(rgb)));
        }
    }
       return IplImageBuffer;
}


