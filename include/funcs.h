#ifndef _FUNCS_H_
#define _FUNCS_H_

#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <memory>
#include <deque>
#include "kcftracker.hpp" /* JOAO_KCF */
#include <QMainWindow>
#include <QMessageBox>
#include <QMenuBar>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QObject>

#include <QMediaDevices>
#include <QCamera>

#include <QMediaCaptureSession>
#include <QVideoSink>
#include <QVideoWidget>
#include <QLabel>
#include <QPalette>
#include <QMouseEvent>
#include <QVideoFrame>
#include <QPainter>
#include <QTimer>
#include <QImage>

#include <QTranslator>

#define MAX_CAM 9

#define NO_CAM 0x0000u
#define CAM0 0x0001u
#define CAM1 0x0002u
#define CAM2 0x0004u
#define CAM3 0x0008u
#define CAM4 0x0010u
#define CAM5 0x0020u
#define CAM6 0x0040u
#define CAM7 0x0080u
#define CAM8 0x0100u

#define LAYOUT_1x1 0x01u
#define LAYOUT_2x2 0x02u
#define LAYOUT_3x3 0x04u

#define CAM_SUM_H 3u
#define CAM_SUM_W 3u

#define MAIN_WIN_W 1354
#define MAIN_WIN_H 831

/* CAM_SIZE_W : CAM_SIZE_H = 16 : 9*/
#define CAM_SIZE_H 252u
#define CAM_SIZE_W 448u

/* Gap between cameras. */
#define CAM_GAP 5u

#define LABEL_H 20u

/* FPS. */
#define FPS 100

extern uint16_t cam_state;
extern uint8_t layout_state;
extern int current_w;
extern int current_h;
extern int main_win_w;
extern int main_win_h;
extern int label_h;
extern int cam_gap;
extern int avl_widget;
extern QImage back_grnd;


using namespace cv;
using namespace std;



namespace funcs{

bool camInit(VideoCapture& cam,int cam_id);

KCFTracker kcfInit(Mat first_frame);
bool kcfUpdate(KCFTracker& tracker,Mat& frame);

QImage cnvtMatToQImage(const Mat& mat);

}

#endif
