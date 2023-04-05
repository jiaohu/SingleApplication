#ifndef MAINHANLDER_H
#define MAINHANLDER_H

#include "mainwindow.h"
#include<QMutex>
class MainHanlder
{
public:
    MainHanlder();
    ~MainHanlder();

    MainWindow* getCurMain();
    static MainHanlder* getInstance();
    static MainHanlder *instance;
    static QMutex mutex;

private:
    MainWindow *curMain;

};

#endif // MAINHANLDER_H
