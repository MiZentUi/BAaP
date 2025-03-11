#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QMainWindow>
#include "scene.h"

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
    Scene *scene;
    QTimer *timer;
    QTimer *statusTimer;

    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void updateStatus();

private slots:
    void timerSlot();
    void on_trianglePushButton_clicked();
    void on_circlePushButton_clicked();
    void on_rhombusPushButton_clicked();
    void on_squarePushButton_clicked();
    void on_rectanglePushButton_clicked();
    void on_starPushButton_clicked();
    void on_polygonPushButton_clicked();
    void on_trapezoidPushButton_clicked();
    void on_penColorPushButton_clicked();
    void on_brushColorPushButton_clicked();
    void on_penWidthPushButton_clicked();
    void on_erasePushButton_clicked();
};
#endif // MAINWINDOW_H
