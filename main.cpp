#include "mainwindow.h"
#include "mainhanlder.h"
#include"singleapp.h"
#include<QDebug>

#include<QMessageBox>
#include<QtGui>
#include<QtGlobal>

MainHanlder* MainHanlder::instance = nullptr;
QMutex MainHanlder::mutex;
#ifdef WIN32
#include "windows.h"
int main(int argc, char *argv[])
{
    SingleApp a(argc, argv);
    MainWindow w;
    w.setWindowTitle("hello");
    if (a.isRunning()) {
        QString wTitle = QString("hello");
        LPCWSTR appCaption = reinterpret_cast<LPCWSTR>(wTitle.unicode());
        HWND handle = FindWindow(nullptr, appCaption);
        if (handle == nullptr) {
            return -1;
        }
        WId wid = reinterpret_cast<WId>(handle);
        QWidget *cc = QWidget::find(wid);
        if (cc == nullptr) {
            QMessageBox::warning(nullptr, "", "1");
            return -1;
        }
        MainWindow *t = qobject_cast<MainWindow*>(cc);
        t->setText(4);
        ShowWindow(handle, SW_RESTORE);
        SetForegroundWindow(handle);
        return 0;
    } else {
        w.show();
    }
    return a.exec();

//    if (!a.isRunning())
//    {
//        MainWindow *w = MainHanlder::getInstance()->getCurMain();
//        //传入一个要激活程序的窗口，当多开时会激活已有进程的窗口，且多开失败
//        a.mainWindow = w;
//        a.data = 1;
//        qDebug()<<a.data;

//        w->show();

//        return a.exec();
//    }
//    qobject_cast<MainWindow*>(a.mainWindow)->setText(a.data);
//    qDebug()<<a.data;
//    return 0;
}
#elif __APPLE__
int main(int argc, char *argv[]) {
    SingleApp a(argc, argv);
    MainWindow w;
    if (a.isRunning()) {
        qDebug()<<"running";
        try {
            WId tmp = a.getWid();
            qDebug()<<tmp;
            QWidget *t = QWidget::find(tmp);
            if (t == nullptr) {
                QMessageBox::warning(nullptr, "", "1");
                return -1;
            }
            t->show();
            return 1;
        }  catch (QException e) {
            QMessageBox::warning(nullptr, "", e.what());
            return -1;
        }

    }
    a.wid = w.winId();
    w.show();

    return a.exec();
}
#endif




