#include "mainhanlder.h"
#include<QMutexLocker>
#include<QMutex>

MainHanlder::MainHanlder()
{
    curMain = new MainWindow;
}

MainHanlder::~MainHanlder()
{
    mutex.unlock();
}

MainWindow *MainHanlder::getCurMain()
{
    return curMain;
}

MainHanlder *MainHanlder::getInstance()
{
    if (instance == Q_NULLPTR) {
        mutex.lock();
        if (instance == Q_NULLPTR) {
            MainHanlder *_instance = new MainHanlder;
            instance = _instance;
        }
    }
    return instance;

}
