#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      bstButton(new QPushButton()),
      treeView(new QTreeView())
{
    ui->setupUi(this);

    this->setWindowTitle("Task 2");
    this->setStyleSheet(
        "background-color: #181818;"
        "color: white;");
    this->setFont(QFont("Noto Sans Mono", 15));

    bstButton->setText("BST");

    treeView->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 10px;"
        "padding: 5px;");
    treeView->setFont(QFont("Noto Sans Mono", 12));
    treeView->setHeaderHidden(true);

    auto *vLayout = new QVBoxLayout();
    vLayout->addWidget(bstButton);
    vLayout->addWidget(treeView);
    centralWidget()->setLayout(vLayout);

    connect(bstButton, &QPushButton::clicked, this, &MainWindow::bstClicked);

    for (int i = 0; i < 11; i++)
    {
        bst.insert(i, "value_" + QString::number(i));
    }

    update();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::update()
{
    treeView->setModel(bst.toModel());
    treeView->expandAll();
}

void MainWindow::bstClicked()
{
    auto *dialog = new Dialog(this, &bst);
    dialog->exec();
    delete dialog;
}