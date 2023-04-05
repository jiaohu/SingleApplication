#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setText(int n)
{
    ui->label->setText(QString("%1").arg(n));
}

MainWindow::~MainWindow()
{
    delete ui;
}

