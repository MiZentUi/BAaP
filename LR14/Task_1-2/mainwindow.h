#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

struct Laptop
{
    static constexpr char OSs[3] = {'L', 'W', 'M'};
    static constexpr int DIAGONALS[5] = {14, 15, 16, 17, 18};

    int diagonal = 0;
    double price = 0;
    char opSys = '\0';
    bool gaming = false;
};

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

    Laptop getLaptop(QString title = "Laptop");
    QString getText(QString title = "Text");
    void showText(QString text, QString title = "Text");

private slots:
    void writeTextClicked();
    void readTextClicked();
    void writeArrayClicked();
    void readArrayClicked();
    void addLaptopClicked();
    void readLaptopsClicked();
    void addBinLaptopClicked();
    void readBinLaptopsClicked();
    void addSentenceClicked();
    void readSentenciesClicked();
};
#endif  // MAINWINDOW_H
