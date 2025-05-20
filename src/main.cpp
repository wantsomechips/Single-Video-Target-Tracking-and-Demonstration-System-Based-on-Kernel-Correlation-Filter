#include "viewer.h"
#include "funcs.h"
#include "CamWidget.h"

QTranslator* trans_cn = new QTranslator;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!trans_cn->load("../bin/viewer_cn.qm")){
        QMessageBox::warning(nullptr,"Translator load failed !",\
            "Laguage changing is disabled.");
    }


    //QCoreApplication::installTranslator(trans_cn);

    viewer w;
    w.show();

    return a.exec();

}


