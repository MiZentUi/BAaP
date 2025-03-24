#include "mainwindow.h"

#include <qdebug.h>
#include <qfiledialog.h>

#include <QDesktopServices>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      fileSystemModel(new QFileSystemModel())
{
    ui->setupUi(this);

    this->setWindowTitle("Task 5");
    this->setStyleSheet(
        "background-color: #181818;"
        "color: white;");

    fileSystemModel->setRootPath(QDir::homePath());

    ui->treeView->setModel(fileSystemModel);
    ui->treeView->setRootIndex(fileSystemModel->index("/home"));
    ui->treeView->header()->resizeSections(QHeaderView::ResizeToContents);
    ui->treeView->header()->setMinimumSectionSize(100);
    ui->treeView->header()->setSectionResizeMode(0, QHeaderView::Stretch);

    long long dirsCount = 0;
    long long filesCount = 0;
    dirsAndFilesCount(QDir::homePath(), dirsCount, filesCount);
    ui->dirTextLabel->setText(QString::number(dirsCount));
    ui->filesTextLabel->setText(QString::number(filesCount));

    connect(ui->openPushButton, &QPushButton::clicked, this, &MainWindow::open);
    connect(ui->treeView, &QTreeView::doubleClicked, this,
            &MainWindow::openFile);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::open()
{
    QString dirPath = QFileDialog::getExistingDirectory(
        this, "Select Folder",
        fileSystemModel->filePath(ui->treeView->rootIndex()));
    if (dirPath.isEmpty())
    {
        return;
    }
    ui->treeView->setRootIndex(fileSystemModel->index(dirPath));
    long long dirsCount = 0;
    long long filesCount = 0;
    dirsAndFilesCount(dirPath, dirsCount, filesCount);
    ui->dirTextLabel->setText(QString::number(dirsCount));
    ui->filesTextLabel->setText(QString::number(filesCount));
}

void MainWindow::dirsAndFilesCount(QString dirPath, long long &dirsCount,
                                   long long &filesCount)
{
    QDir dir(dirPath);
    for (QFileInfo entry :
         dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot))
    {
        if (entry.isDir())
        {
            dirsCount++;
            dirsAndFilesCount(
                entry.absolutePath() + "/" + entry.completeBaseName() + "/",
                dirsCount, filesCount);
        }
        else
        {
            filesCount++;
        }
    }
}

void MainWindow::openFile(QModelIndex index)
{
    QFileInfo file(fileSystemModel->filePath(index));
    if (!file.isDir())
    {
        QDesktopServices::openUrl(fileSystemModel->filePath(index));
    }
}