#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>

#include "filemanager.h"
#include "datetablemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FileManager *fileManger;
    DateTableManager *dateTableManager;
    Date *bithdayDate;
    QVector<QString> strings;
    
    void calculate();

private slots:
    void open();
    void bithdayChanged(QString string);
    void itemChanged(QTableWidgetItem *item);
};
#endif // MAINWINDOW_H