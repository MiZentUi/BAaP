#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Task 4-5");
    this->setStyleSheet(
        "background-color: #181818;"
        "color: white;");

    ui->firstTextEdit->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 10px;"
        "padding: 5px;");

    ui->secondTextEdit->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 10px;"
        "padding: 5px;");

    ui->firstTextEdit->setReadOnly(true);
    ui->secondTextEdit->setReadOnly(true);

    connect(ui->vectorPushButton, &QPushButton::clicked, this,
            &MainWindow::vectorClicked);
    connect(ui->firstVectorPushButton, &QPushButton::clicked, this,
            &MainWindow::firstVectorClicked);
    connect(ui->secondVectorPushButton, &QPushButton::clicked, this,
            &MainWindow::secondVectorClicked);
    update();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::update()
{
    QString firstString;
    QString secondString;
    for (auto pair : sausage)
    {
        for (int item : pair.first)
        {
            firstString += QString::number(item) + ' ';
        }
        firstString += '\n';
        for (auto item : pair.second)
        {
            secondString += '(' + QString::number(item.first) + ", " +
                            QString::number(item.second) + ") ";
        }
        secondString += '\n';
    }
    ui->firstTextEdit->setText(firstString);
    ui->secondTextEdit->setText(secondString);
}

void MainWindow::vectorClicked()
{
    auto *dialog = new Dialog(this, &sausage);
    dialog->exec();
    delete dialog;
}

void MainWindow::firstVectorClicked()
{
    if (!sausage.empty())
    {
        bool good = false;
        size_t index = QInputDialog::getInt(this, "Index", "Index", 0, 0,
                                            (int)sausage.size(), 1, &good);
        if (good)
        {
            auto *dialog = new Dialog(this, &sausage[index].first);
            dialog->exec();
            delete dialog;
        }
    }
    else
    {
        QMessageBox messageBox;
        messageBox.setStyleSheet(styleSheet());
        messageBox.setText("Vector is empty!");
        messageBox.exec();
    }
}

void MainWindow::secondVectorClicked()
{
    if (!sausage.empty())
    {
        bool good = false;
        size_t index = QInputDialog::getInt(this, "Index", "Index", 0, 0,
                                            (int)sausage.size(), 1, &good);
        if (good)
        {
            auto *dialog = new Dialog(this, &sausage[index].second);
            dialog->exec();
            delete dialog;
        }
    }
    else
    {
        QMessageBox messageBox;
        messageBox.setStyleSheet(styleSheet());
        messageBox.setText("Vector is empty!");
        messageBox.exec();
    }
}