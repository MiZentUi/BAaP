#include "mainwindow.h"

#include <exception>

#include "./ui_mainwindow.h"
#include "qlist.h"
#include "qmainwindow.h"
#include "qregexp.h"
#include "qwidget.h"
#include "tools.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Task 1-3");
    this->setStyleSheet(
        "background-color: #181818;"
        "color: white;");

    ui->decToBinLineEdit->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 15px;"
        "padding: 0 3px;");

    ui->ackermannLineEdit->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 15px;"
        "padding: 0 3px;");

    ui->reverseLineEdit->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 15px;"
        "padding: 0 3px;");

    connect(ui->decToBinLineEdit, &QLineEdit::textChanged, this,
            &MainWindow::decToBinChanged);
    connect(ui->ackermannLineEdit, &QLineEdit::textChanged, this,
            &MainWindow::ackermannChanged);
    connect(ui->reverseLineEdit, &QLineEdit::textChanged, this,
            &MainWindow::reverseChanged);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::decToBinChanged()
{
    ui->decToBinResultLabel->setText(QString::fromStdString(
        dec_to_bin(ui->decToBinLineEdit->text().toDouble())));
}

void MainWindow::ackermannChanged()
{
    try
    {
        const QStringList data =
            ui->ackermannLineEdit->text().trimmed().split(QRegExp("\\s+"));
        if (data.size() == 2 && !data.at(0).isEmpty() &&
            !data.at(1).isEmpty() && data.at(0).toLongLong() >= 0 &&
            data.at(1).toLongLong() >= 0)
        {
            ui->ackermannResultLabel->setText(
                QString::fromStdString(std::to_string(ackermann(
                    data.at(0).toLongLong(), data.at(1).toLongLong()))));
        }
        else
        {
            ui->ackermannResultLabel->setText("");
        }
    }
    catch (std::exception &e)
    {
        throw;
    }
}

void MainWindow::reverseChanged()
{
    if (QRegExp("\\d*").exactMatch(ui->reverseLineEdit->text()) &&
        !ui->reverseLineEdit->text().isEmpty())
    {
        ui->reverseResultLabel->setText(
            QString::fromStdString(
                std::to_string(reverse(
                    (long long)ui->reverseLineEdit->text().toLongLong(), 0)))
                .split(".")[0]);
    }
    else
    {
        ui->reverseResultLabel->setText("");
    }
}