#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "qwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), widget(new Widget())
{
    ui->setupUi(this);

    this->setWindowTitle("Task 1-3");
    this->setStyleSheet(
        "background-color: #181818;"
        "color: white;");

    this->setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete widget;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_1:
            widget->startHanoi(1);
            break;
        case Qt::Key_2:
            widget->startHanoi(2);
            break;
        case Qt::Key_3:
            widget->startHanoi(3);
            break;
        case Qt::Key_4:
            widget->startHanoi(4);
            break;
        case Qt::Key_5:
            widget->startHanoi(5);
            break;
        case Qt::Key_6:
            widget->startHanoi(6);
            break;
        case Qt::Key_7:
            widget->startHanoi(7);
            break;
        case Qt::Key_8:
            widget->startHanoi(8);
            break;
        case Qt::Key_9:
            widget->startHanoi(9);
            break;
        case Qt::Key_0:
            widget->startHanoi(10);
            break;
        default:
            break;
    }
}