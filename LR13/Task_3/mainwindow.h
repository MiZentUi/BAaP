#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>

#include "bitset.h"

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
    BitSet<32> bitset;
    QPushButton *bitsetButton;
    QTextEdit *textEdit;

    void bitsetClicked();
};
#endif  // MAINWINDOW_H
