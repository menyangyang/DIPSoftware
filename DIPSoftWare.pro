#-------------------------------------------------
#
# Project created by QtCreator 2014-05-10T15:58:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DIPSoftWare
TEMPLATE = app


SOURCES +=     sourceFile/thinmethod.cpp \
    sourceFile/morphologyhandle.cpp \
    sourceFile/mainwindow.cpp \
    sourceFile/main.cpp \
    sourceFile/filter.cpp \
    sourceFile/diptool.cpp \
    sourceFile/dft.cpp \
    sourceFile/addnoise.cpp

HEADERS  +=    headFile/mainwindow.h \
    headFile/diptool.h

FORMS    += mainwindow.ui




INCLUDEPATH +=D:/opencv/build/include/ \
               E:/DIPSoftWare/headFile


LIBS +=D:/opencv/build/x86/vc11/lib/opencv_core246d.lib \
         D:/opencv/build/x86/vc11/lib/opencv_highgui246d.lib  \
          D:/opencv/build/x86/vc11/lib/opencv_imgproc246d.lib  \
          D:/opencv/build/x86/vc11/lib/opencv_calib3d246d.lib

#INCLUDEPATH += E:/DTLDownLoads/opencv/build/include


#LIBS += E:/DTLDownLoads/opencv/build/x86/vc11/lib/opencv_core246d.lib \
#           E:/DTLDownLoads/opencv/build/x86/vc11/lib/opencv_core246d.lib   \
#          E:/DTLDownLoads/opencv/build/x86/vc11/lib/opencv_highgui246d.lib  \
#          E:/DTLDownLoads/opencv/build/x86/vc11/lib/opencv_imgproc246d.lib  \
 #        E:/DTLDownLoads/opencv/build/x86/vc11/lib/opencv_calib3d246d.lib

RESOURCES += \
    images.qrc
