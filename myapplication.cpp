#include "myapplication.h"
#include<QFileOpenEvent>
#include<QtDebug>


MyApplication::MyApplication(int &argc, char **argv) : QApplication(argc, argv)
{

}

bool MyApplication::event(QEvent *event)
{
    if (event->type() == QEvent::FileOpen)    {
        QFileOpenEvent *openEvent = static_cast<QFileOpenEvent*>(event);
        qDebug()<<"open file"<<openEvent->file();
    }
    return QApplication::event(event);
}
