#ifndef _VIEWER_H_
#define _VIEWER_H_

#include"CamWidget.h"

extern QTranslator* trans_cn;

class viewer : public QMainWindow
{
    Q_OBJECT

public:
    viewer(QWidget *parent = nullptr);
    ~viewer(void);

    void retranslateUi(void);

protected:
    void resizeEvent(QResizeEvent* event);

private:

    /* Initializing. */
    void menuInit(void);
    void camInit(void);
    // void camWidgetInit(int i);
    void setCamWidget(int cols,int rows);
    void labelInit(int index);

    int camIDtoIndex(int cam_id);

    /* For menu. */
    QMenu* menu_cams_on;
    QMenu* menu_cams_off;
    QMenu* menu_target;
    QMenu* menu_target_dismiss;
    QMenu* menu_layout;
    QMenu* menu_language;

    QAction* no_cam;
    QAction* act_cams_on[MAX_CAM];
    QAction* act_cams_off[MAX_CAM];
    QAction* act_cams_target[MAX_CAM];
    QAction* act_cams_target_dismiss[MAX_CAM];
    QAction* act_layout_1x1;
    QAction* act_layout_2x2;
    QAction* act_layout_3x3;
    QAction* act_eng;
    QAction* act_cn;

    /* For cameras.*/
    QMediaDevices* devs;
    QList<QCameraDevice> cams;

    /* Cameras displaying. */
    CamWidget* cam_widget[MAX_CAM];
    QLabel* cam_label[MAX_CAM];

private slots:
    /* Menu actions. */

    int camCount(void);

    /* set KCF Target Bounding Box. */
    void setTarget(int cam_id);
    void dismissTarget(int cam_id);
    
    /* For cameras. */
    void updateCams(void);
    void noCam(void);

    void videoOutputOn(int cam_id);
    void videoOutputOff(int cam_id);

    void changeToEng(void);
    void changeToCn(void);

    void layout_1x1(void);
    void layout_2x2(void);
    void layout_3x3(void);

    void camera0_on(void);
    void camera1_on(void);
    void camera2_on(void);
    void camera3_on(void);
    void camera4_on(void);
    void camera5_on(void);
    void camera6_on(void);
    void camera7_on(void);
    void camera8_on(void);

    void camera0_off(void);
    void camera1_off(void);
    void camera2_off(void);
    void camera3_off(void);
    void camera4_off(void);
    void camera5_off(void);
    void camera6_off(void);
    void camera7_off(void);
    void camera8_off(void);

    void camera0_target(void);
    void camera1_target(void);
    void camera2_target(void);
    void camera3_target(void);
    void camera4_target(void);
    void camera5_target(void);
    void camera6_target(void);
    void camera7_target(void);
    void camera8_target(void);

    void camera0_target_dismiss(void);
    void camera1_target_dismiss(void);
    void camera2_target_dismiss(void);
    void camera3_target_dismiss(void);
    void camera4_target_dismiss(void);
    void camera5_target_dismiss(void);
    void camera6_target_dismiss(void);
    void camera7_target_dismiss(void);
    void camera8_target_dismiss(void);

};

#endif
