#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qtreeview.h>

#include <QMainWindow>
#include <QPushButton>
#include <QTreeView>

#include "custombst.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void update();

private:
    Ui::MainWindow *ui;
    CustomBST<long long, QString> bst;
    QPushButton *bstButton;
    QTreeView *treeView;

private slots:
    void bstClicked();
};
#endif  // MAINWINDOW_H
