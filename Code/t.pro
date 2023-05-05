# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = t

QT = core gui widgets

HEADERS = \
   $$PWD/activecontour.h \
   $$PWD/filters.h \
   $$PWD/frequency.h \
   $$PWD/functions.h \
   $$PWD/halfdetection.h \
   $$PWD/histogram.h \
   $$PWD/mainwindow.h \
   $$PWD/testing.h \
   featurematching.h \
   harris.h \
   image.h \
   segmatation.h \
   sift.h \
   stb_image.h \
   stb_image_write.h \
   threshold.h

SOURCES = \
   $$PWD/activecontour.cpp \
   $$PWD/filters.cpp \
   $$PWD/frequency.cpp \
   $$PWD/halfdetection.cpp \
   $$PWD/histogram.cpp \
   $$PWD/main.cpp \
   $$PWD/mainwindow.cpp \
   $$PWD/testing.cpp \
   featurematching.cpp \
   harris.cpp \
   image.cpp \
   segmatation.cpp \
   sift.cpp \
   threshold.cpp

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
        LIBS += C:/opencv/release/bin/libopencv_features2d460.dll

#DEFINES = 

