#include "funcs.h"
#include "viewer.h"

uint8_t layout_state=LAYOUT_3x3;
int current_w = CAM_SIZE_W;
int current_h = CAM_SIZE_H;
int main_win_w = MAIN_WIN_W;
int main_win_h = MAIN_WIN_H;
int label_h = LABEL_H;
int cam_gap = CAM_GAP;
int avl_widget = 9;

uint16_t cam_state=0x0000u;

int max_cam_used=0;

viewer::viewer(QWidget *parent): QMainWindow(parent) {
    this->setWindowTitle(QObject::tr("Object Tracking"));
    this->resize(MAIN_WIN_W,MAIN_WIN_H);

    this->devs = new QMediaDevices;

    this->menu_cams_on = new QMenu(QObject::tr("Add Camera"),this);
    this->menu_cams_off = new QMenu(QObject::tr("Cancel Camera"),this);
    this->menu_target = new QMenu(QObject::tr("Set Target"),this);
    this->menu_target_dismiss = new QMenu(QObject::tr("Dismiss Target"),this);
    this->menu_layout = new QMenu(QObject::tr("Layout"),this);
    this->menu_language = new QMenu(QObject::tr("Language/语言"),this);

    this->no_cam = new QAction(QObject::tr("No camera available"),this);

    this->act_layout_1x1 = new QAction(QObject::tr("1 x1"),this);
    this->act_layout_2x2 = new QAction(QObject::tr("2x2"),this);
    this->act_layout_3x3 = new QAction(QObject::tr("3x3"),this);

    this->act_eng = new QAction(QObject::tr("English"),this);
    this->act_cn = new QAction(QObject::tr("中文"),this);

    for(int i=0;i<MAX_CAM;++i){
        string str="Camera ";
        act_cams_on[i] = new QAction(QObject::tr((str+to_string(i)).c_str()),this);
        act_cams_off[i] = new QAction(QObject::tr((str+to_string(i)).c_str()),this);
        act_cams_target[i] = new QAction(QObject::tr((str+to_string(i)).c_str()),this);
        act_cams_target_dismiss[i] = new QAction(QObject::tr((str+to_string(i)).c_str()),this);
        cam_label[i] = new QLabel(QObject::tr(str.c_str()),this);
        cam_widget[i] = new CamWidget(this);

        cam_widget[i]->cam_label = cam_label[i];

        this->labelInit(i);
    }
setCamWidget(3,3);
    
    viewer::camInit();
    viewer::menuInit();
}


viewer::~viewer(void){
    delete this->devs;
    delete this->menu_cams_on;
    delete this->menu_cams_off;
    delete this->menu_target;
    delete this->menu_language;
    delete this->act_layout_1x1;
    delete this->act_layout_2x2;
    delete this->act_layout_3x3;
    delete this->act_eng;
    delete this->act_cn;
    for(int i=0;i<MAX_CAM;++i){
        delete this->act_cams_on[i];
        delete this->act_cams_off[i];
        delete this->act_cams_target[i];
        delete this->act_cams_target_dismiss[i];
        delete this->cam_widget[i];
    }
}

void viewer::retranslateUi(void){
    this->setWindowTitle(QCoreApplication::translate("QObject","Object Tracking"));

    this->menu_cams_on->setTitle(QCoreApplication::translate("QObject","Add Camera"));
    this->menu_cams_off->setTitle(QCoreApplication::translate("QObject","Cancel Camera"));
    this->menu_target->setTitle(QCoreApplication::translate("QObject","Set Target"));
    this->menu_target_dismiss->setTitle(QCoreApplication::translate("QObject","Dismiss Target"));
    this->menu_layout->setTitle(QCoreApplication::translate("QObject","Layout"));

    this->no_cam = new QAction(QObject::tr("No camera available"),this);
    this->act_cams_on[0]->setText(QCoreApplication::translate("QObject","Camera 0"));
    this->act_cams_on[1]->setText(QCoreApplication::translate("QObject","Camera 1"));
    this->act_cams_on[2]->setText(QCoreApplication::translate("QObject","Camera 2"));
    this->act_cams_on[3]->setText(QCoreApplication::translate("QObject","Camera 3"));
    this->act_cams_on[4]->setText(QCoreApplication::translate("QObject","Camera 4"));
    this->act_cams_on[5]->setText(QCoreApplication::translate("QObject","Camera 5"));
    this->act_cams_on[6]->setText(QCoreApplication::translate("QObject","Camera 6"));
    this->act_cams_on[7]->setText(QCoreApplication::translate("QObject","Camera 7"));
    this->act_cams_on[8]->setText(QCoreApplication::translate("QObject","Camera 8"));

    this->act_cams_off[0]->setText(QCoreApplication::translate("QObject","Camera 0"));
    this->act_cams_off[1]->setText(QCoreApplication::translate("QObject","Camera 1"));
    this->act_cams_off[2]->setText(QCoreApplication::translate("QObject","Camera 2"));
    this->act_cams_off[3]->setText(QCoreApplication::translate("QObject","Camera 3"));
    this->act_cams_off[4]->setText(QCoreApplication::translate("QObject","Camera 4"));
    this->act_cams_off[5]->setText(QCoreApplication::translate("QObject","Camera 5"));
    this->act_cams_off[6]->setText(QCoreApplication::translate("QObject","Camera 6"));
    this->act_cams_off[7]->setText(QCoreApplication::translate("QObject","Camera 7"));
    this->act_cams_off[8]->setText(QCoreApplication::translate("QObject","Camera 8"));

    this->act_cams_target[0]->setText(QCoreApplication::translate("QObject","Camera 0"));
    this->act_cams_target[1]->setText(QCoreApplication::translate("QObject","Camera 1"));
    this->act_cams_target[2]->setText(QCoreApplication::translate("QObject","Camera 2"));
    this->act_cams_target[3]->setText(QCoreApplication::translate("QObject","Camera 3"));
    this->act_cams_target[4]->setText(QCoreApplication::translate("QObject","Camera 4"));
    this->act_cams_target[5]->setText(QCoreApplication::translate("QObject","Camera 5"));
    this->act_cams_target[6]->setText(QCoreApplication::translate("QObject","Camera 6"));
    this->act_cams_target[7]->setText(QCoreApplication::translate("QObject","Camera 7"));
    this->act_cams_target[8]->setText(QCoreApplication::translate("QObject","Camera 8"));

    this->act_cams_target_dismiss[0]->setText(QCoreApplication::translate("QObject","Camera 0"));
    this->act_cams_target_dismiss[1]->setText(QCoreApplication::translate("QObject","Camera 1"));
    this->act_cams_target_dismiss[2]->setText(QCoreApplication::translate("QObject","Camera 2"));
    this->act_cams_target_dismiss[3]->setText(QCoreApplication::translate("QObject","Camera 3"));
    this->act_cams_target_dismiss[4]->setText(QCoreApplication::translate("QObject","Camera 4"));
    this->act_cams_target_dismiss[5]->setText(QCoreApplication::translate("QObject","Camera 5"));
    this->act_cams_target_dismiss[6]->setText(QCoreApplication::translate("QObject","Camera 6"));
    this->act_cams_target_dismiss[7]->setText(QCoreApplication::translate("QObject","Camera 7"));
    this->act_cams_target_dismiss[8]->setText(QCoreApplication::translate("QObject","Camera 8"));

}

void viewer::camInit(void){
    this->cams = devs->videoInputs();

    /* Not recommend old style SIGNAL() and SLOT(),too lazy to replace them. */
    connect(this->devs,SIGNAL(videoInputsChanged()),this,SLOT(updateCams()));

    connect(act_cams_on[0],SIGNAL(triggered(bool)),this,SLOT(camera0_on()));
    connect(act_cams_on[1],SIGNAL(triggered(bool)),this,SLOT(camera1_on()));
    connect(act_cams_on[2],SIGNAL(triggered(bool)),this,SLOT(camera2_on()));
    connect(act_cams_on[3],SIGNAL(triggered(bool)),this,SLOT(camera3_on()));
    connect(act_cams_on[4],SIGNAL(triggered(bool)),this,SLOT(camera4_on()));
    connect(act_cams_on[5],SIGNAL(triggered(bool)),this,SLOT(camera5_on()));
    connect(act_cams_on[6],SIGNAL(triggered(bool)),this,SLOT(camera6_on()));
    connect(act_cams_on[7],SIGNAL(triggered(bool)),this,SLOT(camera7_on()));
    connect(act_cams_on[8],SIGNAL(triggered(bool)),this,SLOT(camera8_on()));
    
    connect(act_cams_off[0],SIGNAL(triggered(bool)),this,SLOT(camera0_off()));
    connect(act_cams_off[1],SIGNAL(triggered(bool)),this,SLOT(camera1_off()));
    connect(act_cams_off[2],SIGNAL(triggered(bool)),this,SLOT(camera2_off()));
    connect(act_cams_off[3],SIGNAL(triggered(bool)),this,SLOT(camera3_off()));
    connect(act_cams_off[4],SIGNAL(triggered(bool)),this,SLOT(camera4_off()));
    connect(act_cams_off[5],SIGNAL(triggered(bool)),this,SLOT(camera5_off()));
    connect(act_cams_off[6],SIGNAL(triggered(bool)),this,SLOT(camera6_off()));
    connect(act_cams_off[7],SIGNAL(triggered(bool)),this,SLOT(camera7_off()));
    connect(act_cams_off[8],SIGNAL(triggered(bool)),this,SLOT(camera8_off()));

    connect(act_cams_target[0],SIGNAL(triggered(bool)),this,SLOT(camera0_target()));
    connect(act_cams_target[1],SIGNAL(triggered(bool)),this,SLOT(camera1_target()));
    connect(act_cams_target[2],SIGNAL(triggered(bool)),this,SLOT(camera2_target()));
    connect(act_cams_target[3],SIGNAL(triggered(bool)),this,SLOT(camera3_target()));
    connect(act_cams_target[4],SIGNAL(triggered(bool)),this,SLOT(camera4_target()));
    connect(act_cams_target[5],SIGNAL(triggered(bool)),this,SLOT(camera5_target()));
    connect(act_cams_target[6],SIGNAL(triggered(bool)),this,SLOT(camera6_target()));
    connect(act_cams_target[7],SIGNAL(triggered(bool)),this,SLOT(camera7_target()));
    connect(act_cams_target[8],SIGNAL(triggered(bool)),this,SLOT(camera8_target()));

    connect(act_cams_target_dismiss[0],SIGNAL(triggered(bool)),this,SLOT(camera0_target_dismiss()));
    connect(act_cams_target_dismiss[1],SIGNAL(triggered(bool)),this,SLOT(camera1_target_dismiss()));
    connect(act_cams_target_dismiss[2],SIGNAL(triggered(bool)),this,SLOT(camera2_target_dismiss()));
    connect(act_cams_target_dismiss[3],SIGNAL(triggered(bool)),this,SLOT(camera3_target_dismiss()));
    connect(act_cams_target_dismiss[4],SIGNAL(triggered(bool)),this,SLOT(camera4_target_dismiss()));
    connect(act_cams_target_dismiss[5],SIGNAL(triggered(bool)),this,SLOT(camera5_target_dismiss()));
    connect(act_cams_target_dismiss[6],SIGNAL(triggered(bool)),this,SLOT(camera6_target_dismiss()));
    connect(act_cams_target_dismiss[7],SIGNAL(triggered(bool)),this,SLOT(camera7_target_dismiss()));
    connect(act_cams_target_dismiss[8],SIGNAL(triggered(bool)),this,SLOT(camera8_target_dismiss()));
}

void viewer::menuInit(void){

    this->updateCams();

    this->menu_layout->addAction(this->act_layout_1x1);
    this->menu_layout->addAction(this->act_layout_2x2);
    this->menu_layout->addAction(this->act_layout_3x3);

    this->menu_language->addAction(this->act_eng);
    this->menu_language->addAction(this->act_cn);

    this->menuBar()->addMenu(this->menu_cams_on);
    this->menuBar()->addMenu(this->menu_cams_off);
    this->menuBar()->addMenu(this->menu_target);
    this->menuBar()->addMenu(this->menu_target_dismiss);
    this->menuBar()->addMenu(this->menu_layout);
    this->menuBar()->addMenu(this->menu_language);

    setMenuBar(this->menuBar());

    connect(no_cam,SIGNAL(triggered(bool)),this,SLOT(noCam()));

    connect(act_layout_1x1,SIGNAL(triggered(bool)),this,SLOT(layout_1x1()));
    connect(act_layout_2x2,SIGNAL(triggered(bool)),this,SLOT(layout_2x2()));
    connect(act_layout_3x3,SIGNAL(triggered(bool)),this,SLOT(layout_3x3()));

    connect(act_eng,SIGNAL(triggered(bool)),this,SLOT(changeToEng()));
    connect(act_cn,SIGNAL(triggered(bool)),this,SLOT(changeToCn()));
}

int viewer::camIDtoIndex(int cam_id){
    for(int i=0;i<MAX_CAM;++i){
        if(cam_widget[i]->cam_id == cam_id){
            return i;
        }
    }
    return -1;
}

void viewer::setCamWidget(int cols,int rows){
    avl_widget = cols*rows;

    float ratio = 1.0*main_win_w/MAIN_WIN_W;
    cam_gap = ratio*CAM_GAP;
    label_h = ratio*LABEL_H;

    // current_w = (1.0*main_win_w-(cols-1)*cam_gap)/cols;
    // current_h = 1.0*9/16*current_w;

    current_h = (1.0*main_win_h-(rows-1)*(cam_gap+label_h)+label_h)/rows;
    current_w = 1.0*16/9*current_h;

    for(int index=rows*cols;index<MAX_CAM;++index){
            cam_widget[index]->setVisible(false);
            if(cam_widget[index]->is_avl == false){
                this->videoOutputOff(cam_widget[index]->cam_id);
            }
            cam_label[index]->setVisible(false);
    }

    for(int i=0;i<rows;++i){
        for(int j=0;j<cols;++j){
            int index = i*cols+j;
            cam_widget[index] ->xx = j*(current_w+cam_gap);
            cam_widget[index] ->yy = label_h*(1+i)+i*(current_h+cam_gap);
            cam_widget[index] ->ww = current_w;
            cam_widget[index] ->hh = current_h;

            cam_widget[index]->setGeometry(cam_widget[index] ->xx,cam_widget[index] ->yy,\
                cam_widget[index] ->ww,cam_widget[i] ->hh);
                
            cam_label[index]->setGeometry(cam_widget[index] ->xx,cam_widget[index] ->yy-label_h,\
                cam_widget[index] ->ww,label_h);
            
            cam_widget[index]->setVisible(true);
            cam_label[index]->setVisible(true);
            cam_label[index]->update();
        }
    }
}

void viewer::resizeEvent(QResizeEvent* event){
    main_win_h = this->height();
    main_win_w = 1.63*main_win_h;
    if(this->width() != main_win_w){
        this->resize(main_win_w,main_win_h);
    }
    switch(layout_state){
        case LAYOUT_1x1:{
            this->setCamWidget(1,1);
            break;
        }
         case LAYOUT_2x2:{
            this->setCamWidget(2,2);
            break;
        }
         case LAYOUT_3x3:{
            this->setCamWidget(3,3);
        }
    }
}

void viewer::changeToEng(void){
    // QTranslator trans;
    QCoreApplication::removeTranslator(trans_cn);
    this->retranslateUi();
}

void viewer::changeToCn(void){
    // QTranslator trans;
    QCoreApplication::installTranslator(trans_cn);
    this->retranslateUi();
}

void viewer::layout_1x1(void){
    if(layout_state == LAYOUT_1x1){
    QMessageBox::warning(nullptr,QObject::tr("Layout has been placed !"),\
        QObject::tr("This layout has been placed,select a new one."));
    return;
    }
    layout_state = LAYOUT_1x1;
    setCamWidget(1,1);
}

void viewer::layout_2x2(void){
    if(layout_state == LAYOUT_2x2){
    QMessageBox::warning(nullptr,QObject::tr("Layout has been placed !"),\
        QObject::tr("This layout has been placed,select a new one."));
    return;
    }
    layout_state = LAYOUT_2x2;
    setCamWidget(2,2);
}

void viewer::layout_3x3(void){
    if(layout_state == LAYOUT_3x3){
    QMessageBox::warning(nullptr,QObject::tr("Layout has been placed !"),\
        QObject::tr("This layout has been placed,select a new one."));
    return;
    }
    layout_state = LAYOUT_3x3;
    setCamWidget(3,3);
}

void viewer::labelInit(int index){
    cam_label[index]->setGeometry(this->x()+(index%3)*(CAM_SIZE_W+CAM_GAP),\
                               this->y()+LABEL_H*(int)(index/3)+\
                               (CAM_SIZE_H+CAM_GAP)*(int)(index/3),CAM_SIZE_W, LABEL_H);
    cam_label[index]->setAlignment(Qt::AlignTop|Qt::AlignJustify);
    cam_label[index]->setScaledContents(true);
    cam_label[index]->setAutoFillBackground(true);
    cam_label[index]->setFrameStyle(QFrame::Box);
    cam_label[index]->setStyleSheet("background-color: rgb(193, 210, 240);");
    cam_label[index]->show();
}

int viewer::camCount(void){
    return ((cam_state<<7>>15)+(cam_state<<8>>15)+(cam_state<<9>>15)+\
            (cam_state<<10>>15)+(cam_state<<11>>15)+(cam_state<<12>>15)\
            +(cam_state<<13>>15)+(cam_state<<14>>15)+(cam_state<<15>>15));
}


void viewer::updateCams(void){
    this->cams = devs->videoInputs();
    if(this->cams.isEmpty()){
        this->menu_cams_on->clear();
        this->menu_cams_on->addAction(this->no_cam);
        return;
    }
    
    int cam_counter = (int)(this->cams.size()>MAX_CAM? MAX_CAM:this->cams.size());
    if(cam_counter > max_cam_used) max_cam_used = cam_counter;
    
    for(int i=0;i<cam_counter;++i){
        this->menu_cams_on->addAction(this->act_cams_on[i]);
        this->menu_cams_off->addAction(this->act_cams_off[i]);
        this->menu_target->addAction(this->act_cams_target[i]);
        this->menu_target_dismiss->addAction(this->act_cams_target_dismiss[i]);
    }

}

void viewer::noCam(void){
    QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("There is no camera available !"));
}

void viewer::videoOutputOn(int cam_id){
// qDebug()<<"ouput on"<<Qt::endl;
    int index = -1;
    for(int i=0;i<avl_widget;++i){
        if(cam_widget[i]->is_avl){
            index = i;
            break;
        }
    }
    if(index == -1){
        QMessageBox::warning(this,QObject::tr("There is no window available !"),\
            QObject::tr("Cancel camera you arn't currently using or place a bigger layout !"));
        return;
    }
    cam_widget[index]->cam_id = cam_id;
    cam_widget[index]->is_avl = false;
    cam_widget[index]->camInit();
    cam_widget[index]->timer->start(1.0*1000/FPS);
    cam_label[index]->setText(QObject::tr(((cam_label[index]->text()).toStdString()+\
        to_string(cam_id)).c_str()));
    /* Toggle camera state,cause only legal camera can jump into this function. */
    cam_state = (cam_state ^ (CAM0<<cam_id));
}

void viewer::videoOutputOff(int cam_id){
// qDebug()<<"ouput off"<<Qt::endl;
    int index = this->camIDtoIndex(cam_id);
    if(index == -1){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Invaild camera ID !"));
        return;
    }
    cam_widget[index]->timer->stop();
    cam_widget[index]->camStop();
    cam_widget[index]->kcfStop();
    cam_widget[index]->is_avl = true;
    cam_widget[index]->cam_id = -1;
    cam_label[index]->setText(QObject::tr("Camera"));
    /* Toggle camera state,cause only legal camera can jump into this function. */
    cam_state = (cam_state ^ (CAM0<<cam_id));
}


void viewer::camera0_on(void){
    if((cam_state&CAM0) == CAM0){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Camera0 has been displayed !"));
        return;
    }

    this->videoOutputOn(0);
}

void viewer::camera1_on(void){
    if((cam_state&CAM1) == CAM1){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Camera1 has been displayed !"));
        return;
    }

    this->videoOutputOn(1);
}

void viewer::camera2_on(void){
    if((cam_state&CAM2) == CAM2){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Camera2 has been displayed !"));
        return;
    }
    cam_state = (cam_state | CAM2);
    
    this->videoOutputOn(2);
}

void viewer::camera3_on(void){
    if((cam_state&CAM3) == CAM3){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("camera3 has been displayed !"));
        return;
    }
    
    this->videoOutputOn(3);
}

void viewer::camera4_on(void){
    if((cam_state&CAM4) == CAM4){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("camera4 has been displayed !"));
        return;
    }
   
    this->videoOutputOn(4);
}

void viewer::camera5_on(void){
    if((cam_state&CAM5) == CAM5){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("camera5 has been displayed !"));
        return;
    }
    
    this->videoOutputOn(5);
}

void viewer::camera6_on(void){
    if((cam_state&CAM6) == CAM6){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("camera6 has been displayed !"));
        return;
    }
    
    this->videoOutputOn(6);
}

void viewer::camera7_on(void){
    if((cam_state&CAM7) == CAM7){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("camera7 has been displayed !"));
        return;
    }
    
    this->videoOutputOn(7);
}

void viewer::camera8_on(void){
    if((cam_state&CAM8) == CAM8){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("camera8 has been displayed !"));
        return;
    }
    
    this->videoOutputOn(8);
}



void viewer::camera0_off(void){
    if((cam_state&CAM0) == NO_CAM){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Camera0 is NOT displayed !"));
        return;
    }
    
    this->videoOutputOff(0);
}

void viewer::camera1_off(void){
    if((cam_state&CAM1) == NO_CAM){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Camera1 is NOT displayed !"));
        return;
    }
    
    this->videoOutputOff(1);
}

void viewer::camera2_off(void){
    if((cam_state&CAM2) == NO_CAM){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Camera2 is NOT displayed !"));
        return;
    }
    
    this->videoOutputOff(2);
}

void viewer::camera3_off(void){
    if((cam_state&CAM3) == NO_CAM){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Camera3 is NOT displayed !"));
        return;
    }
    
    this->videoOutputOff(3);
    
}

void viewer::camera4_off(void){
    if((cam_state&CAM4) == NO_CAM){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Camera4 is NOT displayed !"));
        return;
    }
    
    this->videoOutputOff(4);
}

void viewer::camera5_off(void){
    if((cam_state&CAM5) == NO_CAM){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Camera5 is NOT displayed !"));
        return;
    }
    
    this->videoOutputOff(5);
    
}

void viewer::camera6_off(void){
    if((cam_state&CAM6) == NO_CAM){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Camera6 is NOT displayed !"));
        return;
    }
    
    this->videoOutputOff(6);
    
}

void viewer::camera7_off(void){
    if((cam_state&CAM7) == NO_CAM){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Camera7 is NOT displayed !"));
        return;
    }
    
    this->videoOutputOff(7);
    
}

void viewer::camera8_off(void){
    if((cam_state&CAM8) == NO_CAM){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Camera8 is NOT displayed !"));
        return;
    }
    
    this->videoOutputOff(8);
    
}


void viewer::setTarget(int cam_id){
    int index = this->camIDtoIndex(cam_id);
    if(index == -1){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Camera is NOT displayed !"));
        return;
    }
    cam_widget[index]->kcfInit();

}

void viewer::dismissTarget(int cam_id){
    int index = this->camIDtoIndex(cam_id);
    if(index == -1){
        QMessageBox::warning(this,QObject::tr("Warning"),QObject::tr("Camera is NOT displayed !"));
        return;
    }
    cam_widget[index]->kcfStop();
}

void viewer::camera0_target(void){
    setTarget(0);
}

void viewer::camera1_target(void){
    setTarget(1);
}

void viewer::camera2_target(void){
    setTarget(2);
}

void viewer::camera3_target(void){
    setTarget(3);
}

void viewer::camera4_target(void){
    setTarget(4);
}

void viewer::camera5_target(void){
    setTarget(5);
}

void viewer::camera6_target(void){
    setTarget(6);
}

void viewer::camera7_target(void){
    setTarget(7);
}

void viewer::camera8_target(void){
    setTarget(8);
}

void viewer::camera0_target_dismiss(void){
    dismissTarget(0);
}

void viewer::camera1_target_dismiss(void){
    dismissTarget(1);
}

void viewer::camera2_target_dismiss(void){
    dismissTarget(2);
}

void viewer::camera3_target_dismiss(void){
    dismissTarget(3);
}

void viewer::camera4_target_dismiss(void){
    dismissTarget(4);
}

void viewer::camera5_target_dismiss(void){
    dismissTarget(5);
}

void viewer::camera6_target_dismiss(void){
    dismissTarget(6);
}

void viewer::camera7_target_dismiss(void){
    dismissTarget(7);
}

void viewer::camera8_target_dismiss(void){
    dismissTarget(8);
}


