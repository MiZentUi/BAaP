#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>
#include <QKeyEvent>

#include "schedulemanager.h"
#include "filemanager.h"

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
    FileManager *fileManager;
    ScheduleManager *scheduleManager;

    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void itemChanged(QTableWidgetItem *item);
    void open();
    void save();
    void saveAs();
};
#endif // MAINWINDOW_H
