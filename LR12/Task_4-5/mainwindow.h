#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "pair.h"
#include "vector.h"

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

    Vector<Pair<Vector<int>, Vector<Pair<int, double>>>> sausage;

    void vectorClicked();
    void firstVectorClicked();
    void secondVectorClicked();
};
#endif  // MAINWINDOW_H
