#ifndef SINGLEAPP_H
#define SINGLEAPP_H

#include <QApplication>
#include <QSharedMemory>
#include "mainwindow.h"
class QWidget;
class QLocalServer;


class SingleApp : public QApplication
{
    Q_OBJECT
    public:
        SingleApp(int &argc, char **argv);
        bool isRunning();               // 是否已经有实例在运行
        QWidget *mainWindow;            // MainWindow指针
        int data;

    private slots:
        // 有新连接时触发
        void newLocalConnection();

    private:
        // 初始化本地连接
        void initLocalConnection();
        // 创建服务端
        void newLocalServer();
        bool bRunning;                  // 是否已经有实例在运行
        QLocalServer *localServer;      // 本地socket Server
        QString serverName;             // 服务名称
};

#endif // SINGLEAPP_H
