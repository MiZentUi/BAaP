#include "mainwindow.h"

#include <qboxlayout.h>

#include "./ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      string(""),
      stringButton(new QPushButton()),
      textEdit(new QTextEdit())
{
    ui->setupUi(this);

    this->setWindowTitle("Task 2");
    this->setStyleSheet(
        "background-color: #181818;"
        "color: white;");

    stringButton->setText("String");

    textEdit->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 10px;"
        "padding: 5px;"
        "font-size: 30px;");
    textEdit->setReadOnly(true);

    auto *vLayout = new QVBoxLayout();
    vLayout->addWidget(stringButton);
    vLayout->addWidget(textEdit);
    centralWidget()->setLayout(vLayout);

    connect(stringButton, &QPushButton::clicked, this,
            &MainWindow::stringClicked);

    update();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::update() { textEdit->setText(QString(string.c_str())); }

void MainWindow::stringClicked()
{
    auto *dialog = new Dialog(this, &string);
    dialog->exec();
    delete dialog;
}