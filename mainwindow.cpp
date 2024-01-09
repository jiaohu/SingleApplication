#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleMessage(const QString &t)
{
    ui->plainTextEdit->setPlaceholderText(t);
}

void MainWindow::receivedMessage(int instanceId, QByteArray message)
{
    qDebug() << "Received message from instance: " << instanceId;
        qDebug() << "Message Text: " << message;
    ui->plainTextEdit->setPlaceholderText(message);
}

