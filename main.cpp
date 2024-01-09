#include "mainwindow.h"

#include "SingleApplication"

int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv, true);
    if( a.isSecondary() ) {
       qDebug()<<argc;
       a.sendMessage(  a.arguments().join(' ').toUtf8() );
       return 0;
    }

    MainWindow w;
    QObject::connect(&a,
                     &SingleApplication::receivedMessage,
                     &w,
                     &MainWindow::receivedMessage);
    w.show();
    return a.exec();
}
