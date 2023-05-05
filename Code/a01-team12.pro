# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = a01-team12

QT = core gui widgets

HEADERS = \
   $$PWD/filters.h \
   $$PWD/frequency.h \
   $$PWD/functions.h \
   $$PWD/histogram.h \
   $$PWD/mainwindow.h \
   $$PWD/testing.h \
   activecontour.h \
   halfdetection.h

SOURCES = \
   $$PWD/filters.cpp \
   $$PWD/frequency.cpp \
   $$PWD/histogram.cpp \
   $$PWD/main.cpp \
   $$PWD/mainwindow.cpp \
   $$PWD/testing.cpp \
   activecontour.cpp \
   halfdetection.cpp

INCLUDEPATH = \
    $$PWD/.
    FORMS += \
        mainwindow.ui
        INCLUDEPATH += C:\opencv\release\install\include
        LIBS += C:/opencv/release/bin/libopencv_core460.dll
        LIBS += C:/opencv/release/bin/libopencv_highgui460.dll
        LIBS += C:/opencv/release/bin/libopencv_imgcodecs460.dll
        LIBS += C:/opencv/release/bin/libopencv_imgproc460.dll
        LIBS += C:/opencv/release/bin/libopencv_calib3d460.dll
#DEFINES = 

