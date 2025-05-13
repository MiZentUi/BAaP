#include "mainwindow.h"

#include <QBoxLayout>

#include "./ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      dequeButton(new QPushButton()),
      textEdit(new QTextEdit())
{
    ui->setupUi(this);

    this->setWindowTitle("Task 5");
    this->setStyleSheet(
        "background-color: #181818;"
        "color: white;");

    dequeButton->setText("Deque");

    textEdit->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 10px;"
        "padding: 5px;"
        "font-size: 15px;");
    textEdit->setFont(QFont("Noto Sans Mono", 12));
    textEdit->setReadOnly(true);

    auto *vLayout = new QVBoxLayout();
    vLayout->addWidget(dequeButton);
    vLayout->addWidget(textEdit);
    centralWidget()->setLayout(vLayout);

    connect(dequeButton, &QPushButton::clicked, this,
            &MainWindow::dequeClicked);

    update();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::update()
{
    QString result;
    for (const QString &str : deque)
    {
        result += str + '\n';
    }
    textEdit->setText(result);
}

void MainWindow::dequeClicked()
{
    auto *dialog = new Dialog(this, &deque);
    dialog->exec();
    delete dialog;
}