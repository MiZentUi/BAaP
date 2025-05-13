#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>

#include "customstackhashtable.h"

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
    CustomStackHashTable hashTable;
    QPushButton *hashTableButton;
    QTextEdit *textEdit;

private slots:
    void hashTableClicked();
};
#endif  // MAINWINDOW_H
