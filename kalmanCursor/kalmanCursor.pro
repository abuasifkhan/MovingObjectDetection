TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += C:\\opencv2410\include
SOURCES += main.cpp
LIBS += -LC:\\opencv2410\bin \
-llibopencv_contrib2410 \
-llibopencv_core2410 \
-llibopencv_features2d2410 \
-llibopencv_flann2410 \
-llibopencv_gpu2410 \
-llibopencv_highgui2410 \
-llibopencv_imgproc2410 \
-llibopencv_legacy2410 \
-llibopencv_ml2410 \
-llibopencv_nonfree2410 \
-llibopencv_objdetect2410 \
-llibopencv_ocl2410 \
-llibopencv_photo2410 \
-llibopencv_stitching2410 \
-llibopencv_superres2410 \
-llibopencv_video2410 \
-llibopencv_videostab2410

DISTFILES += \
    ../../../../videos/768x576.avi
