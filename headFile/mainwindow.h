#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QLabel>



class DIPTool;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    //hist display
    void histDisplay(DIPTool* child);
    void updateHistDisplay(QImage * srcImage);

    void updateMenus();


private:

    bool hasToolChild;
    DIPTool * child;
    QLabel * label;
    QBoxLayout * layout;


private slots:

    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionGrayChange_triggered();

    void on_actionAvergeFilter_triggered();

    void on_actionMedianFilter_triggered();

    void on_actionGaussianFilter_triggered();

    void on_actionSharpen_triggered();

    void on_actionFT_triggered();

    void on_actionCorrosion_triggered();

    void on_actionExpansion_triggered();

    void on_actionOpen_2_triggered();

    void on_actionClose_triggered();

    void on_actionAddGuassianNoise_triggered();

    void on_actionSPNoise_triggered();

    void on_actionReload_triggered();

    void on_actionGetPath_triggered();

    void on_actionIDE_triggered();



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
