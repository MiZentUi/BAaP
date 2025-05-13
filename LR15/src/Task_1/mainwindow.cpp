#include "mainwindow.h"

#include <QFileDialog>
#include <QGridLayout>
#include <QKeyEvent>
#include <QTimer>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      timer(new QTimer()),
      label(new QLabel())
{
    ui->setupUi(this);

    this->setWindowTitle("Task 1");
    this->setStyleSheet(
        "background-color: #181818;"
        "color: white;");

    label->setAlignment(Qt::AlignCenter);
    setCentralWidget(label);

    connect(timer, &QTimer::timeout, this, &MainWindow::next);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_O)
    {
        open();
    }
}

void MainWindow::open()
{
    timer->stop();
    QDir dir =
        QFileDialog::getExistingDirectory(this, "Select Folder", "/home");
    images.clear();
    for (QString filename : dir.entryList(QDir::Files))
    {
        images.push(dir.absoluteFilePath(filename));
    }
    timer->start(0);
}

void MainWindow::next()
{
    double scale = 0.85;
    label->setPixmap(
        QPixmap(images.front())
            .scaled(width() * scale, height() * scale, Qt::KeepAspectRatio));
    images.push(images.front());
    images.pop();
    timer->start(3000);
}