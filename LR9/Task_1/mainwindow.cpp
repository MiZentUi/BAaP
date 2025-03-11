#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qdebug.h>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // this->resize/*(1000, 1000);
    // this->setFixedSize(1000, 1000);*/
    this->size();
    ui->graphicsView->setBackgroundBrush(Qt::cyan);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::resizeSlot);
    timer->start(100);
    balloon = new Balloon(width() / 2 - 450, height(), 300, 450);
    scene->addItem(balloon);
    balloon->start_fly(150);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    timer->start(200);
}

void MainWindow::resizeSlot()
{
    timer->stop();
    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    balloon->setXc(width() / 2 - balloon->getWidth() / 2);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space)
    {
        balloon->reload();
        balloon->start_fly(150);
        balloon->setYc(height());
    }
}
