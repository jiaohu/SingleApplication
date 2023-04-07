#include "singleapp.h"
#include <QWidget>
#include <QtNetwork/QLocalSocket>
#include <QtNetwork/QLocalServer>
#include <QFileInfo>
#include <QLibrary>
#include<QBuffer>


SingleApp::SingleApp(int &argc, char **argv)
    : QApplication(argc, argv), m_share("trimatch")
{
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << this->wid;
    int size = buffer.size();
    if (!m_share.create(size)) {
        bRunning = true;
        m_share.lock();
        memcpy((char*)m_share.data(), buffer.data().data(), size);
        m_share.unlock();

    }
}

SingleApp::~SingleApp()
{
    m_share.detach();
}

//#ifdef WIN32
//SingleApp::SingleApp(int &argc, char **argv)
//    : QApplication(argc, argv)
//    , bRunning(false)
//    , localServer(NULL)
//    , mainWindow(NULL)
//{
//    // 取应用程序名作为LocalServer的名字
//    serverName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
//    //qDebug()<<serverName;
//    initLocalConnection();
//}
//#elif __APPLE__
//SingleApp::SingleApp(int &argc, char **argv)
//    : QApplication(argc, argv), m_share("trimatch")
//{
//    if (!m_share.create(1)) {

//        bRunning = true;

//    }
//}
//#endif




// 说明：
// 检查是否已經有一个实例在运行, true - 有实例运行， false - 没有实例运行

bool SingleApp::isRunning()
{
    return bRunning;
}

WId SingleApp::getWid()
{
    QBuffer buffer;
    QDataStream in(&buffer);
    WId res;

    m_share.lock();
    buffer.setData((char*)m_share.constData(), m_share.size());
    buffer.open(QBuffer::ReadOnly);
    in >> res;
    m_share.unlock();
    return res;
}


// 说明：
// 通过socket通讯实现程序单实例运行，监听到新的连接时触发该函数

void SingleApp::newLocalConnection()
{
    QLocalSocket *socket = localServer->nextPendingConnection();
    if (!socket)
        return;
    socket->waitForReadyRead(1000);
    QTextStream stream(socket);
    //其他处理
    delete socket;
    if (mainWindow != NULL)
    {
        //激活窗口
        mainWindow->raise();
        mainWindow->activateWindow();
        mainWindow->setWindowState((mainWindow->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
        mainWindow->show();
    }
}


// 说明：
// 通过socket通讯实现程序单实例运行，
// 初始化本地连接，如果连接不上server，则创建，否则退出

void SingleApp::initLocalConnection()
{
    bRunning = false;
    QLocalSocket socket;
    socket.connectToServer(serverName);
    if(socket.waitForConnected(500))
    {
        bRunning = true;
        // 其他处理，如：将启动参数发送到服务端
        QTextStream stream(&socket);
        QStringList args = QCoreApplication::arguments();
        if (args.count() > 1)
            stream << args.last();
        else
            stream << QString();
        stream.flush();
        socket.waitForBytesWritten();

        return;
    }

    //连接不上服务器，就创建一个
    newLocalServer();
}


// 说明：
// 创建LocalServer

void SingleApp::newLocalServer()
{
    localServer = new QLocalServer(this);
    connect(localServer, SIGNAL(newConnection()), this, SLOT(newLocalConnection()));
    if(!localServer->listen(serverName))
    {
        // 此时监听失败，可能是程序崩溃时,残留进程服务导致的,移除之
        if(localServer->serverError() == QAbstractSocket::AddressInUseError)
        {
            QLocalServer::removeServer(serverName); // <-- 重点
            localServer->listen(serverName); // 再次监听
        }
    }
}
