#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "diptool.h"
#include <QLabel>
#include<QLayout>

#define cvQueryHistValue_1D( hist, idx0 ) \
    ((float)cvGetReal1D( (hist)->bins, (idx0)))


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("DIP Tool");

    label = new QLabel;

    child = new DIPTool;

    hasToolChild = false;

    updateMenus();

}


void MainWindow::updateHistDisplay(QImage *srcImage)
{
    label ->setPixmap(QPixmap::fromImage(*srcImage));
    label->setGeometry(0,0, 1024, 768);
    label->show();
}


void MainWindow::histDisplay(DIPTool *child)
{

    IplImage * src= child ->QImageToIplImage(child ->getImage());

    IplImage* gray_dst= cvCreateImage(cvGetSize(src), 8, 1);
    cvCvtColor(src, gray_dst, CV_BGR2GRAY);

    //一维维数
    int dims= 1;
    //直方图的尺寸
    int size= 256;
    //直方图的高度
    int height = 256;
    //灰度图的范围0到255
    float range[]= {0, 256};
    float *ranges[]= {range};

    //创建一维直方图
    CvHistogram* hist;
    hist= cvCreateHist(dims, &size, CV_HIST_ARRAY, ranges, 1);

    //计算灰度图的一维直方图
    cvCalcHist(&gray_dst, hist, 0, 0);
    //归一化直方图
    cvNormalizeHist(hist, 1.0);

    int scale= 2;
    //创建图像，用于显示直方图
    IplImage* hist_img= cvCreateImage(cvSize(size* scale, height), 8, 3);
    //图像置零
    cvZero(hist_img);

    //计算直方图的最大方块值,初始化为0
    float max_value= 0;
    cvGetMinMaxHistValue(hist, 0, &max_value, 0, 0);

    //绘制直方图
    for(int i=0; i<size; i++)
    {
        float bin_val= cvQueryHistValue_1D(hist, i);   //像素i的概率
        int intensity = cvRound(bin_val* height/ max_value);  // 绘制的高度
        cvRectangle(hist_img,
                    cvPoint(i* scale, height- 1),
                    cvPoint((i+1)* scale- 1, height- intensity),
                    CV_RGB(255, 255, 255));
    }


    QImage * imageTemp = child ->IplImageToQImage(hist_img);

    label ->setPixmap(QPixmap::fromImage(*imageTemp));

}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{

    if(child ->okToCountinue())
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath());

        if(!fileName.isEmpty())
        {
            child ->load(fileName);
            histDisplay(child);

            layout = new QHBoxLayout;
            layout->addWidget(child);
            layout ->addWidget(label);
            ui ->mdiArea ->setLayout(layout);
            hasToolChild = true;
            updateMenus();

        }
    }

}




void MainWindow::updateMenus()
{
    ui ->actionSave ->setEnabled(hasToolChild);
    ui ->actionSaveAs ->setEnabled(hasToolChild);
    ui ->actionExit ->setEnabled(hasToolChild);
    ui ->actionGetPath ->setEnabled(hasToolChild);
    ui ->actionGrayChange ->setEnabled(hasToolChild);
    ui ->actionAddGuassianNoise ->setEnabled(hasToolChild);
    ui ->actionAvergeFilter ->setEnabled(hasToolChild);
    ui ->actionOpen_2 ->setEnabled(hasToolChild);
    ui ->actionCorrosion ->setEnabled(hasToolChild);
    ui ->actionExpansion ->setEnabled(hasToolChild);
    ui ->actionMedianFilter ->setEnabled(hasToolChild);
    ui ->actionFT ->setEnabled(hasToolChild);
    ui ->actionReload ->setEnabled(hasToolChild);
    ui ->actionSPNoise ->setEnabled(hasToolChild);
    ui ->actionSharpen ->setEnabled(hasToolChild);
    ui ->actionGaussianFilter ->setEnabled(hasToolChild);
    ui ->actionClose ->setEnabled(hasToolChild);
}



void MainWindow::on_actionExit_triggered()
{
   bool flag = child ->closeEvent();
   if(flag)
   {
       label ->clear();
       delete layout;
       hasToolChild = false;
       updateMenus();
   }
}



void MainWindow::on_actionSave_triggered()
{
    if(child ->save())
        ui ->statusBar ->showMessage(tr("Save Successfully"), 2000);
}

void MainWindow::on_actionSaveAs_triggered()
{
    if(child ->saveAs())
    ui ->statusBar ->showMessage(tr("Save Successfully"), 2000);
}



void MainWindow::on_actionGrayChange_triggered()
{
    child ->grayScaleValue();
    histDisplay(child);
}


void MainWindow::on_actionAvergeFilter_triggered()
{
    child ->avergeFilter();
     histDisplay(child);
}

void MainWindow::on_actionMedianFilter_triggered()
{
    child ->medianFilter();
     histDisplay(child);
}


void MainWindow::on_actionGaussianFilter_triggered()
{
    child ->gaussFilter();
     histDisplay(child);
}

void MainWindow::on_actionSharpen_triggered()
{
    child ->sobelSharpFilter();
     histDisplay(child);
}

void MainWindow::on_actionFT_triggered()
{
    child ->fftConvert();

}

void MainWindow::on_actionCorrosion_triggered()
{
    child ->corrosionFilter();
    histDisplay(child);
}

void MainWindow::on_actionExpansion_triggered()
{
    child ->expansionFilter();
     histDisplay(child);
}

void MainWindow::on_actionOpen_2_triggered()
{
    child ->openMorphology();
     histDisplay(child);

}

void MainWindow::on_actionClose_triggered()
{
    child ->closeMorphology();
    histDisplay(child);
}

void MainWindow::on_actionAddGuassianNoise_triggered()
{
    child ->addGuassianNoise();
     histDisplay(child);
}

void MainWindow::on_actionSPNoise_triggered()
{
    child ->addSaltPepperNoise();
     histDisplay(child);
}

void MainWindow::on_actionReload_triggered()
{
    child ->load(child ->getCurFileName());
     histDisplay(child);
}

void MainWindow::on_actionGetPath_triggered()
{
    child ->imageThin();
}

void MainWindow::on_actionIDE_triggered()
{
    QMessageBox::information(this, tr("关于DIP Tool"),
                                  tr("The IDE is Qt creator5.1.1 vs opencv 2.4.6."),
                                  QMessageBox::Ok);

}

