#ifndef SINGLEAPP_H
#define SINGLEAPP_H

#include <QApplication>
#include <QSharedMemory>
#include<ctime>
#include<QTimer>
#include "mainwindow.h"
class QWidget;
class QLocalServer;


class SingleApp : public QApplication
{
    Q_OBJECT
    public:
        SingleApp(int &argc, char **argv);
        ~SingleApp();
        bool isRunning();               // 是否已经有实例在运行
        QWidget *mainWindow;            // MainWindow指针
        int data;
        struct Memory {
//            time_t lastProcessed;
            WId wid;
            Memory(WId id) {
                this->wid = id;
            };
        };
        WId wid;
        WId getWid();
        void setWid(WId wid);
//        bool isCurrentOwnerNoLock();
        bool isCurrentOwner();
        void setGlobalId(uint64_t);
protected:
        static const int EVENT_TIMER_MS = 1000;
        static const int EVENT_GC_TIMEOUT = 5;
        static const int EVENT_QUEUE_SIZE = 32;
        static const int OWNERSHIP_TIMEOUT_S = 5;

    private:

        void processEvents();
        bool bRunning = false;                  // 是否已经有实例在运行

        QSharedMemory m_share;
        uint64_t globalId;
        QTimer timer;
};

#endif // SINGLEAPP_H
