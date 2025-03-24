#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qfilesystemmodel.h>

#include <QMainWindow>
#include <QTreeWidgetItem>

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
    QFileSystemModel *fileSystemModel;

    void open();
    static void dirsAndFilesCount(QString dirPath, long long &dirsCount,
                                  long long &filesCount);

private slots:
    void openFile(QModelIndex index);
};
#endif  // MAINWINDOW_H
