#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    const QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
