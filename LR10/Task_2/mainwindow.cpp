#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Train Schedule");
    this->setStyleSheet("background-color: #181818;"
                        "color: white;");

    ui->tableWidget->setStyleSheet("background-color: #1f1f1f;"
                                   "border-color: #2b2b2b;"
                                   "border-radius: 10px;");
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    ui->tableWidget->horizontalHeader()->setMinimumSectionSize(50);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->tableWidget->hideColumn(6);

    fileManager = new FileManager();
    scheduleManager = new ScheduleManager(ui->tableWidget);

    connect(ui->openPushButton, &QPushButton::clicked, this, &MainWindow::open);
    connect(ui->savePushButton, &QPushButton::clicked, this, &MainWindow::save);
    connect(ui->saveAsPushButton, &QPushButton::clicked, this, &MainWindow::saveAs);
    connect(ui->filterLineEdit, &QLineEdit::textChanged, [=] { scheduleManager->setFilter(ui->filterLineEdit->text().toStdString()); scheduleManager->update(); });

    connect(ui->tableWidget, &QTableWidget::itemChanged, this, &MainWindow::itemChanged);

    scheduleManager->update();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fileManager;
    delete scheduleManager;
}

void MainWindow::itemChanged(QTableWidgetItem *item)
{
    scheduleManager->itemChanged(item);
}

void MainWindow::open()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Text File"), "/home", tr("Text Files (*.txt)"));
    if (filename.isEmpty())
        return;
    fileManager->setFilename(filename.toStdString());
    TrainRoute **trainRoutes;
    int trainRoutesSize;
    fileManager->getTrainRoutes(trainRoutes, trainRoutesSize);
    scheduleManager->setTrainRoutes(trainRoutes, trainRoutesSize);
    scheduleManager->update();
}

void MainWindow::save()
{
    if (fileManager->getFilename().empty())
        saveAs();
    else
    {
        TrainRoute **trainRoutes;
        int trainRoutesSize;
        scheduleManager->getTrainRoutes(trainRoutes, trainRoutesSize);
        fileManager->save(trainRoutes, trainRoutesSize);
    }
}

void MainWindow::saveAs()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save As Text File"), "/home", tr("Text Files (*.txt)"));
    if (filename.isEmpty())
        return;
    TrainRoute **trainRoutes;
    int trainRoutesSize;
    scheduleManager->getTrainRoutes(trainRoutes, trainRoutesSize);
    fileManager->setFilename(filename.toStdString());
    fileManager->save(filename.toStdString(), trainRoutes, trainRoutesSize);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_O:
        if (event->modifiers() & Qt::ControlModifier)
            open();
        break;
    case Qt::Key_S:
        if (event->modifiers() & Qt::ControlModifier)
        {
            if (event->modifiers() & Qt::ShiftModifier)
                saveAs();
            else
                save();
        }
        break;
    case Qt::Key_F:
        if (event->modifiers() & Qt::ControlModifier)
            ui->filterLineEdit->setFocus();
        break;
    case Qt::Key_Delete:
        scheduleManager->deleteSelected();
        break;
    default:
        break;
    }
}