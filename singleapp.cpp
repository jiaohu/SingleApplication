#include "singleapp.h"
#include <QWidget>
#include <QtNetwork/QLocalSocket>
#include <QtNetwork/QLocalServer>
#include <QFileInfo>
#include <QLibrary>
#include<random>
#include<QBuffer>
#include<QMessageBox>
#include<qmath.h>


SingleApp::SingleApp(int &argc, char **argv)
    : QApplication(argc, argv), m_share("hello")
{

    QMessageBox::information(nullptr, "", "construct");
//    timer.setInterval(EVENT_TIMER_MS);
//    timer.setSingleShot(true);
//    connect(&timer, &QTimer::timeout, this, &SingleApp::processEvents);

    // 用来生成随机的globalId
//    std::default_random_engine randEngine((std::random_device())());
//    std::uniform_int_distribution<uint64_t> distribution;
//    globalId = distribution(randEngine);
    if (m_share.attach()) {
                bRunning = true;
        QMessageBox::information(nullptr, "","could not lock to take owner");
        WId mem = getWid();
        QMessageBox::information(nullptr, "","getMemory");

        globalId = mem;
        QMessageBox::information(nullptr, "",QString("globalId = %1").arg(mem));
    } else {
        m_share.create(sizeof(Memory));
    }
}

SingleApp::~SingleApp()
{
    if (!m_share.lock()) {
        return;
    }

    m_share.unlock();
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
    WId mem;
    buffer.setData((char*)m_share.data(), m_share.size());
    buffer.open(QBuffer::ReadOnly);
    in >> mem;

    return mem;
}

void SingleApp::setWid(WId wid)
{
    if (m_share.lock()) {
        QBuffer buffer;
        buffer.open(QBuffer::ReadWrite);
        QDataStream out(&buffer);
        out << wid;
    //            mem->lastProcessed = time(nullptr);
        memcpy(m_share.data(), buffer.data(), qMin(m_share.size(), int(buffer.size())));
        m_share.unlock();
    }
}

bool SingleApp::isCurrentOwner()
{
    if (bRunning) {
        m_share.lock();
        return true;
    }
    return false;
}

void SingleApp::setGlobalId(uint64_t t)
{
    globalId = t;
}

void SingleApp::processEvents()
{
//    qDebug()<<"processEvents";
//    if (!m_share.lock()) {
//        timer.start();
//        return;
//    }

//    Memory *mem = getMemory();

//    if (mem->wid == globalId) {
//        mem->lastProcessed = time(nullptr);
//    } else {
//        if (difftime(time(nullptr), mem->lastProcessed) >= OWNERSHIP_TIMEOUT_S) {
//            qDebug()<<"previous owner timed out, taking ownership"<<mem->wid<<"->"<<globalId;
//            memset(mem, 0, sizeof(Memory));
//            mem->wid = globalId;
//            mem->lastProcessed = time(nullptr);
//        }
//    }

//    m_share.unlock();
//    timer.start();
}

