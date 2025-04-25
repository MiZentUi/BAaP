#include "mainwindow.h"

#include <QComboBox>
#include <QDebug>
#include <QDialog>
#include <QGridLayout>
#include <QInputDialog>
#include <QPushButton>
#include <QRadioButton>
#include <QTextEdit>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Task 1-2");
    this->setStyleSheet(
        "background-color: #181818;"
        "color: white;");

    auto *gridLayout = new QGridLayout();
    auto *vLayout = new QVBoxLayout();

    auto *writeTextButton = new QPushButton("Write Text");
    auto *readTextButton = new QPushButton("Read Text");
    auto *writeArrayButton = new QPushButton("Write Array");
    auto *readArrayButton = new QPushButton("Read Array");
    auto *addLaptopButton = new QPushButton("Add Laptop");
    auto *readLaptopsButton = new QPushButton("Read Laptops");
    auto *addBinLaptopButton = new QPushButton("Add Bin Laptop");
    auto *readBinLaptopsButton = new QPushButton("Read Bin Laptops");
    auto *addSentenceButton = new QPushButton("Add Sentence");
    auto *readSentenciesButton = new QPushButton("Read Sentencies");
    auto *exitButton = new QPushButton("Exit");

    vLayout->addWidget(writeTextButton);
    vLayout->addWidget(readTextButton);
    vLayout->addWidget(writeArrayButton);
    vLayout->addWidget(readArrayButton);
    vLayout->addWidget(addLaptopButton);
    vLayout->addWidget(readLaptopsButton);
    vLayout->addWidget(addBinLaptopButton);
    vLayout->addWidget(readBinLaptopsButton);
    vLayout->addWidget(addSentenceButton);
    vLayout->addWidget(readSentenciesButton);
    vLayout->addWidget(exitButton);

    gridLayout->addLayout(vLayout, 1, 1);
    gridLayout->setRowStretch(0, 1);
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setRowStretch(1, 1);
    gridLayout->setColumnStretch(1, 1);
    gridLayout->setRowStretch(2, 1);
    gridLayout->setColumnStretch(2, 1);

    connect(writeTextButton, &QPushButton::clicked, this,
            &MainWindow::writeTextClicked);
    connect(readTextButton, &QPushButton::clicked, this,
            &MainWindow::readTextClicked);
    connect(writeArrayButton, &QPushButton::clicked, this,
            &MainWindow::writeArrayClicked);
    connect(readArrayButton, &QPushButton::clicked, this,
            &MainWindow::readArrayClicked);
    connect(addLaptopButton, &QPushButton::clicked, this,
            &MainWindow::addLaptopClicked);
    connect(readLaptopsButton, &QPushButton::clicked, this,
            &MainWindow::readLaptopsClicked);
    connect(addBinLaptopButton, &QPushButton::clicked, this,
            &MainWindow::addBinLaptopClicked);
    connect(readBinLaptopsButton, &QPushButton::clicked, this,
            &MainWindow::readBinLaptopsClicked);
    connect(addSentenceButton, &QPushButton::clicked, this,
            &MainWindow::addSentenceClicked);
    connect(readSentenciesButton, &QPushButton::clicked, this,
            &MainWindow::readSentenciesClicked);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::close);

    this->centralWidget()->setLayout(gridLayout);
}

MainWindow::~MainWindow() { delete ui; }

Laptop MainWindow::getLaptop(QString title)
{
    auto *dialog = new QDialog();
    auto *vLayout = new QVBoxLayout();
    auto *diagonalBox = new QComboBox();
    auto *priceLineEdit = new QLineEdit();
    auto *osBox = new QComboBox();
    auto *gamingButton = new QRadioButton("Gaming");
    auto *button = new QPushButton("OK");

    dialog->setWindowTitle(title);
    dialog->setStyleSheet(styleSheet());
    dialog->setMinimumSize(400, 200);
    dialog->setMaximumSize(1000, 200);
    priceLineEdit->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 5px;"
        "padding: 5px;");
    priceLineEdit->setPlaceholderText("Price");
    for (int diagonal : Laptop::DIAGONALS)
    {
        diagonalBox->addItem(QString::number(diagonal));
    }
    for (auto opSys : Laptop::OSs)
    {
        osBox->addItem(QString(opSys));
    }
    connect(button, &QPushButton::clicked, dialog, &QDialog::close);

    vLayout->addWidget(diagonalBox);
    vLayout->addWidget(priceLineEdit);
    vLayout->addWidget(osBox);
    vLayout->addWidget(gamingButton);
    vLayout->addWidget(button);
    dialog->setLayout(vLayout);
    dialog->exec();

    Laptop laptop;
    laptop.diagonal = diagonalBox->currentText().toInt();
    laptop.price = priceLineEdit->text().toDouble();
    laptop.opSys = osBox->currentText()[0].toLatin1();
    laptop.gaming = gamingButton->isChecked();
    return laptop;
}

QString MainWindow::getText(QString title)
{
    auto *dialog = new QDialog();
    auto *vLayout = new QVBoxLayout();
    auto *textEdit = new QTextEdit();
    auto *button = new QPushButton("OK");
    connect(button, &QPushButton::clicked, dialog, &QDialog::close);
    dialog->setWindowTitle(title);
    dialog->setStyleSheet(styleSheet());
    dialog->setMinimumSize(1000, 200);
    dialog->setMaximumSize(1000, 200);
    textEdit->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 5px;"
        "padding: 5px;");
    vLayout->addWidget(textEdit);
    vLayout->addWidget(button);
    dialog->setLayout(vLayout);
    dialog->exec();
    return textEdit->toPlainText();
}

void MainWindow::showText(QString text, QString title)
{
    auto *dialog = new QDialog();
    auto *vLayout = new QVBoxLayout();
    auto *textEdit = new QTextEdit();
    auto *button = new QPushButton("OK");
    connect(button, &QPushButton::clicked, dialog, &QDialog::close);
    dialog->setWindowTitle(title);
    dialog->setStyleSheet(styleSheet());
    dialog->setMinimumSize(1000, 200);
    dialog->setMaximumSize(1000, 200);
    textEdit->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 5px;"
        "padding: 5px;");
    textEdit->setReadOnly(true);
    textEdit->setText(text);
    vLayout->addWidget(textEdit);
    vLayout->addWidget(button);
    dialog->setLayout(vLayout);
    dialog->exec();
}

void MainWindow::writeTextClicked()
{
    std::wstring wtext = getText().toStdWString();
    std::wfstream file("text.txt", std::ios::out);
    for (wchar_t wch : wtext)
    {
        file << wch;
    }
}

void MainWindow::readTextClicked()
{
    std::wstring wtext;
    std::wfstream file("text.txt", std::ios::in);
    wchar_t wch = '\0';
    while (file.get(wch))
    {
        wtext += wch;
    }
    showText(QString::fromStdWString(wtext));
}

void MainWindow::writeArrayClicked()
{
    QStringList items = getText("Array").split(QRegExp("[^\\d.]+"));
    auto *array = new float[items.size()];
    for (int i = 0; i < items.size(); i++)
    {
        array[i] = items.at(i).toFloat();
    }
    std::fstream file("array.txt", std::ios::out);
    for (size_t i = 0; i < items.size(); i++)
    {
        file << std::to_string(array[i]) << '<';
    }
    delete[] array;
}

void MainWindow::readArrayClicked()
{
    std::fstream file("array.txt", std::ios::in);
    size_t size = 0;
    while (file.good())
    {
        if (file.get() == '<')
        {
            size++;
        }
    }
    auto *array = new float[size];
    file.clear();
    file.seekg(std::fstream::beg);
    for (size_t i = 0; i < size && file.good(); i++)
    {
        file >> array[i];
        file.get();
    }
    QString text;
    for (size_t i = 0; i < size; i++)
    {
        text += QString::number(array[i]) + ' ';
    }
    delete[] array;
    showText(text, "Array");
}

void MainWindow::addLaptopClicked()
{
    auto laptop = getLaptop();
    std::fstream file("laptops.txt", std::ios::app);
    file << laptop.diagonal << ' ' << laptop.price << ' ' << laptop.opSys << ' '
         << laptop.gaming << std::endl;
}

void MainWindow::readLaptopsClicked()
{
    QString text;
    std::vector<Laptop> laptops;
    std::fstream file("laptops.txt", std::ios::in);
    std::string line;
    while (std::getline(file, line))
    {
        Laptop laptop;
        std::stringstream strstream(line);
        strstream >> laptop.diagonal >> laptop.price >> laptop.opSys >>
            laptop.gaming;
        laptops.push_back(laptop);
    }
    text += "[\n";
    for (auto laptop : laptops)
    {
        text += QString("    {diagonal: %0, price: %1, os: %2, gaming: %3}\n")
                    .arg(laptop.diagonal)
                    .arg(laptop.price)
                    .arg(laptop.opSys)
                    .arg(laptop.gaming ? "true" : "false");
    }
    text += ']';
    showText(text, "Laptops");
}

void MainWindow::addBinLaptopClicked()
{
    auto laptop = getLaptop();
    std::fstream file("laptops.bin", std::ios::app | std::ios::binary);
    file.write((char *)&laptop, sizeof(laptop));
}

void MainWindow::readBinLaptopsClicked()
{
    QString text;
    std::vector<Laptop> laptops;
    std::fstream file("laptops.bin", std::ios::in | std::ios::binary);
    Laptop laptop;
    while (file.read((char *)&laptop, sizeof(laptop)))
    {
        laptops.push_back(laptop);
    }
    text += "[\n";
    for (auto laptop : laptops)
    {
        text += QString("    {diagonal: %0, price: %1, os: %2, gaming: %3}\n")
                    .arg(laptop.diagonal)
                    .arg(laptop.price)
                    .arg(laptop.opSys)
                    .arg(laptop.gaming ? "true" : "false");
    }
    text += ']';
    showText(text, "Laptops");
}

void MainWindow::addSentenceClicked()
{
    std::fstream file("sentencies.txt", std::ios::app);
    file << getText("Sentence").toStdString() << std::endl;
}

void MainWindow::readSentenciesClicked()
{
    std::string text;
    std::fstream file("sentencies.txt", std::ios::in);
    std::string line;
    while (std::getline(file, line))
    {
        text += line + '\n';
    }
    showText(QString::fromStdString(text), "Sentencies");
}