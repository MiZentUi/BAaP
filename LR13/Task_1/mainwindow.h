#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "keyboard.h"
#include "text.h"

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
    Text *text;
    Keyboard *keyboard;
    QTimer *timer;
    QLabel *timerLabel;
    QLabel *wordsPerMinute;
    int seconds;

private slots:
    void changeLanguage(const QString &item);
    void statusUpdate();
    void openFile();
};
#endif  // MAINWINDOW_H
