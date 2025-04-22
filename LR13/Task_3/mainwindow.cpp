#include "mainwindow.h"

#include <qboxlayout.h>

#include "./ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      bitset(""),
      bitsetButton(new QPushButton()),
      textEdit(new QTextEdit())
{
    ui->setupUi(this);

    this->setWindowTitle("Task 3");
    this->setStyleSheet(
        "background-color: #181818;"
        "color: white;");

    bitsetButton->setText("BitSet");

    textEdit->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 10px;"
        "padding: 5px;"
        "font-size: 30px;");
    textEdit->setReadOnly(true);

    auto *vLayout = new QVBoxLayout();
    vLayout->addWidget(bitsetButton);
    vLayout->addWidget(textEdit);
    centralWidget()->setLayout(vLayout);

    connect(bitsetButton, &QPushButton::clicked, this,
            &MainWindow::bitsetClicked);

    update();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::update()
{
    textEdit->setText(QString(bitset.to_string().c_str()));
}

void MainWindow::bitsetClicked()
{
    auto *dialog = new Dialog(this, &bitset);
    dialog->exec();
    delete dialog;
}