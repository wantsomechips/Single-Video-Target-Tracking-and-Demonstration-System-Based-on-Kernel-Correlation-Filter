//
//  video_widget.hpp
//  test
//
//  Created by GaoHao on 2023/3/28.
//

#ifndef _CAM_WIDGET_H_
#define _CAM_WIDGET_H_

#include "funcs.h"



class CamWidget : public QWidget{
    
    Q_OBJECT
public:
    CamWidget(QWidget *parent = nullptr);
    ~CamWidget(void);
    
    QWidget* parent;

    /* Proper geometry set by it's parent. */
    int xx;
    int yy;
    int ww;
    int hh;

    /* QWidget::isFullScreen() isn't working fine with subwindow,so I make my own. */
    bool is_full_screen;

    /* Short for "is available",equal to TRUE if CamWidget is free. */
    bool is_avl;

    int cam_id;
    VideoCapture cam;
    KCFTracker tracker;
    bool kcfOpened;
    bool kcfInit(void);
    void kcfStop(void);

    bool camInit(void);
    void camStop(void);

    QTimer* timer;
    int apce_display_timer;
    QLabel* cam_label;


private:
    void displaying(void);
    QImage image;
    Mat frame;
  
protected:
    /* Events .*/
    void mouseDoubleClickEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

};

#endif 
