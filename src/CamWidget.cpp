
#include "funcs.h"
#include "CamWidget.h"

CamWidget::CamWidget(QWidget *parent):QWidget(parent),parent(parent){
    cam_id = -1;
    kcfOpened = false;
    image = QImage(QSize(this->width(),this->height()),QImage::Format_Grayscale8);
    image.fill(0u);

    /* Widget is NOT full screen after initializing. */
    this->is_full_screen = false;

    this->is_avl = true;

    timer = new QTimer(this);
    apce_display_timer = 0;
    connect(timer,&QTimer::timeout,this,&CamWidget::displaying);

}

CamWidget::~CamWidget(void){

    if(cam.isOpened()) {
        cam.release();
    }
    delete timer;

}

bool CamWidget::kcfInit(void){
    if(!cam.isOpened()) {
        QMessageBox::warning(nullptr,QObject::tr("Camera wasn't displaying !"),\
        QObject::tr("Add camera first,before setting target for it."));
        return false;
    }
    if(this->kcfOpened == true) {
        QMessageBox::warning(nullptr,QObject::tr("Warning !"),\
        QObject::tr("KCF has been engaged on this camera."));
        return false;
    }
    // QMessageBox::information(nullptr,QObject::tr("Instruction"),\
    // QObject::tr("Select the target,press ENTER to confirm,press ESC to escape."));
    
    timer->stop();
    cam >> frame;
    tracker = funcs::kcfInit(frame);
    this->kcfOpened =true;
    timer->start(1.0*1000/FPS);

    return true;
}

void CamWidget::kcfStop(void){
    this->kcfOpened = false;
}



bool CamWidget::camInit(void){
    bool retv=funcs::camInit(this->cam,this->cam_id);
    if(!retv){
        qDebug()<<"Camera Init Failed: "<<Qt::endl;
        return false;
    }
    return true;
}

void CamWidget::camStop(void){
    if(cam.isOpened()) {
        cam.release();
    }
    image = QImage(QSize(this->width(),this->height()),QImage::Format_Grayscale8);
    image.fill(0u);
    this->update();
}

void CamWidget::displaying(void){

    cam >> frame;
// qDebug()<<"displaying"<<Qt::endl;
    if(kcfOpened == true) {
        funcs::kcfUpdate(tracker,frame);
    }
    image = funcs::cnvtMatToQImage(frame);

    this->update();

    if(apce_display_timer > FPS){
        apce_display_timer = 0;

        string text = "Camera:";
        text += to_string(cam_id);

        text += "   APCE:";
        text += to_string(int(tracker.current_apce_value));
        if(tracker.apce_accepted == true){
            text += "   Accepted";
        }

        cam_label->setText(QObject::tr(text.c_str()));
    }
    else{
        apce_display_timer += 4;
    }
}

void CamWidget::mouseDoubleClickEvent(QMouseEvent* event){

    if(this-> is_full_screen ){
        this->setWindowFlags(Qt::SubWindow);
        this->showNormal();
        this->setGeometry(this->xx,this->yy,this->ww,this->hh);
qDebug()<<"showFullScreen"<<Qt::endl;
    }
    else{
        /* Subwindow could NOT be full-screen. */
        this->setWindowFlags(Qt::Window);
        this->showFullScreen();
qDebug()<<"showNormal"<<Qt::endl;
    }

    /* Toggle between full-screen and normal. */
    this-> is_full_screen = !(this-> is_full_screen);

qDebug()<<"double clicked"<<Qt::endl;
}



void CamWidget::paintEvent(QPaintEvent* event){

    QWidget::paintEvent(event);

    QPainter painter(this);

    image = image.scaled(this->width(),this->height());
    painter.drawImage(QRect(0,0,this->width(),this->height()),image);


// qDebug()<<"Paint event"<<Qt::endl;

}

