#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QTextEdit>
#include <QTreeView>

#include "custommap.h"

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
    CustomMap<QString, QString> map;
    QPushButton *mapButton;
    QTreeView *treeView;
    QTextEdit *textEdit;

private slots:
    void mapClicked();
};
#endif  // MAINWINDOW_H
