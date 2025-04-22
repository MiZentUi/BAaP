#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>

#include "include/string.h"

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
    String string;
    QPushButton *stringButton;
    QTextEdit *textEdit;

    void stringClicked();
};
#endif  // MAINWINDOW_H
