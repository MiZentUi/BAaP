#include "mainwindow.h"

#include <QBoxLayout>

#include "./ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      mapButton(new QPushButton()),
      treeView(new QTreeView()),
      textEdit(new QTextEdit())
{
    ui->setupUi(this);

    this->setWindowTitle("Task 3");
    this->setStyleSheet(
        "background-color: #181818;"
        "color: white;");

    mapButton->setText("Map");

    treeView->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 10px;"
        "padding: 5px;");
    treeView->setFont(QFont("Noto Sans Mono", 12));
    treeView->setHeaderHidden(true);

    textEdit->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 10px;"
        "padding: 5px;"
        "font-size: 15px;");
    textEdit->setFont(QFont("Noto Sans Mono", 12));
    textEdit->setReadOnly(true);

    auto *vLayout = new QVBoxLayout();
    auto *hLayout = new QHBoxLayout();
    hLayout->addWidget(treeView);
    hLayout->addWidget(textEdit);
    vLayout->addWidget(mapButton);
    vLayout->addLayout(hLayout);
    centralWidget()->setLayout(vLayout);

    connect(mapButton, &QPushButton::clicked, this, &MainWindow::mapClicked);

    update();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mapButton;
    delete treeView;
    delete textEdit;
}

void MainWindow::update()
{
    treeView->setModel(map.toModel());
    treeView->expandAll();
    QString result;
    for (const std::pair<QString, QString> &entry : map)
    {
        result += '{' + entry.first + ": " + entry.second + "}\n";
    }
    textEdit->setText(result);
}

void MainWindow::mapClicked()
{
    auto *dialog = new Dialog(this, &map);
    dialog->exec();
    delete dialog;
}