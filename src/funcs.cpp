#include "funcs.h"

/* Testing only, VideoCapture::grab() suits muti-camera environment. */

QImage back_grnd(QSize(CAM_SIZE_W,CAM_SIZE_H),QImage::Format_Grayscale8);


KCFTracker funcs::kcfInit(Mat first_frame){

    /* Bounding box. */
    Rect2i bbox(0,0,0,0);

    /* Self-defined ROI.*/
    bbox=selectROI(QObject::tr("Select target bounding box:").toStdString(),first_frame);
    destroyWindow(QObject::tr("Select target bounding box:").toStdString());

    /* Initialize KCF Tracker. */
    bool HOG = true;
	bool FIXEDWINDOW = false;
	bool MULTISCALE = true;
	bool SILENT = true;
	bool LAB = false;
    KCFTracker tracker(HOG, FIXEDWINDOW, MULTISCALE, LAB);
    tracker.init(bbox,first_frame);

    return tracker;
}


bool funcs::kcfUpdate(KCFTracker& tracker,Mat& frame){
    Rect2i bbox(0,0,0,0);
    bbox=tracker.update(frame);
    putText(frame,"KCF",Point(bbox.x,bbox.y-1),FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255));
    rectangle(frame,bbox,Scalar(0,0,255),3); /* Last parameter is thickness. */
// qDebug()<<"KCF updated"<<Qt::endl;
    return true;
}

bool funcs::camInit(VideoCapture& cam,int cam_id){
    cam.open(cam_id);
    if(!cam.isOpened()){
        return false;
    }
    return true;
}

QImage funcs::cnvtMatToQImage(const Mat& mat){
    switch(mat.type()){
        case CV_8UC4:{
            QImage image(mat.data, mat.cols, mat.rows, (int)(mat.step), QImage::Format_ARGB32);
            return image;
        }
        case CV_8UC3:{
            QImage image(mat.data, mat.cols, mat.rows, (int)(mat.step), QImage::Format_RGB888);
// qDebug()<<"Image converted"<<Qt::endl;
            return image.rgbSwapped();
        }
        case CV_8UC1:{
            QImage image(mat.data, mat.cols, mat.rows, (int)(mat.step), QImage::Format_Grayscale8);
            return image;
        }
        default:{
            QMessageBox::warning(nullptr,"Unacceptable Frame Format",\
            "Only support ARGB32、RGB888 and Grayscale8");

            return back_grnd;
        }
    }
}


