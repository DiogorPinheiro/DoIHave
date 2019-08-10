#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QPixmap>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *splash = new QSplashScreen();
    splash->setPixmap(QPixmap(":/new/prefix1/Imagens/doIhave_Splash.png"));
    splash->show();
    splash->showMessage("Starting...");
    //QSplashScreen splash(pixmap,Qt::WindowStaysOnTopHint);

    MainWindow w;
    //w.setWindowTitle(QObject::tr(" my title"));
    //w.hide();// mainwindow disappears


    QTimer::singleShot(3500,splash,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));



    //w.show();

    return a.exec();
}
