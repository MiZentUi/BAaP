#include "mainwindow.h"

#include <QBoxLayout>

#include "./ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      hashTableButton(new QPushButton()),
      textEdit(new QTextEdit())
{
    ui->setupUi(this);

    this->setWindowTitle("Task 3");
    this->setStyleSheet(
        "background-color: #181818;"
        "color: white;");

    hashTableButton->setText("StackHashTable");

    textEdit->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 10px;"
        "padding: 5px;"
        "font-size: 15px;");
    textEdit->setFont(QFont("Noto Sans Mono", 12));
    textEdit->setReadOnly(true);

    auto *vLayout = new QVBoxLayout();
    vLayout->addWidget(hashTableButton);
    vLayout->addWidget(textEdit);
    centralWidget()->setLayout(vLayout);

    connect(hashTableButton, &QPushButton::clicked, this,
            &MainWindow::hashTableClicked);

    update();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::update() { textEdit->setText(hashTable.toQString()); }

void MainWindow::hashTableClicked()
{
    auto *dialog = new Dialog(this, &hashTable);
    dialog->exec();
    delete dialog;
}