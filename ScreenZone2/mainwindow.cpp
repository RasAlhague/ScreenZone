#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QCoreApplication>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    //    setParent(0); // Create TopLevel-Widget
    //    setAttribute(Qt::WA_NoSystemBackground, true);
    //    setAttribute(Qt::WA_TranslucentBackground, true);
    //    setAttribute(Qt::WA_PaintOnScreen); // not needed in Qt 5.2 and up

    //    setWindowOpacity(0.8);

        ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "handleButton";
}
