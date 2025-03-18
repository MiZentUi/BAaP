#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Date Editor");
    this->setStyleSheet("background-color: #181818;"
                        "color: white;");

    ui->tableWidget->setStyleSheet("background-color: #1f1f1f;"
                                   "border-color: #2b2b2b;"
                                   "border-radius: 10px;");
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    fileManger = new FileManager();
    dateTableManager = new DateTableManager(ui->tableWidget);
    bithdayDate = nullptr;

    connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::open);
    connect(ui->bithdayLineEdit, &QLineEdit::textChanged, [=, this](QString string) { bithdayChanged(string); });
    connect(ui->tableWidget, &QTableWidget::itemChanged, this, &MainWindow::itemChanged);

    calculate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    fileManger->setFilename(QFileDialog::getOpenFileName(this, tr("Open Text File"), "/home", tr("Text Files (*.txt)")));
    calculate();
}

void MainWindow::calculate()
{
    strings = fileManger->getStrings();
    dateTableManager->setDates(fileManger->getDates(), strings);
    dateTableManager->fillTable();
}

void MainWindow::bithdayChanged(QString string)
{
    try
    {
        Date *currentBithdayDate = new Date(string);
        if (bithdayDate != nullptr)
        {
            delete bithdayDate;
            bithdayDate = nullptr;
        }
        bithdayDate = currentBithdayDate;
        dateTableManager->setBithDayDate(bithdayDate);
    }
    catch(const std::exception& e)
    {
        dateTableManager->setBithDayDate(nullptr);
    }
    dateTableManager->fillTable();
}

void MainWindow::itemChanged(QTableWidgetItem *item)
{
    if (item->column() == 0 && item->row() != 0 && item->row() < strings.size() && item->isSelected() && strings.at(item->row() - 1) != item->text() || item->row() >= strings.size() && item->isSelected())
    {
        item->setSelected(false);
        fileManger->writeLine(item->row() - 1, item->text());
        calculate();
    }
}