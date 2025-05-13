#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "hashtable.h"
#include "qcustomplot.h"

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

private:
    Ui::MainWindow *ui;
    QCustomPlot *plot;
    QTimer *timer;
    HashTable<std::size_t, QString, 16> hashTable16;
    HashTable<std::size_t, QString, 64> hashTable64;
    HashTable<std::size_t, QString, 128> hashTable128;
    HashTable<std::size_t, QString, 2048> hashTable2048;

private slots:
    void updateGraphs();
};
#endif  // MAINWINDOW_H
