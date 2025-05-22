#ifndef DIALOG_H
#define DIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QPushButton>
#include <QString>

#include "custommap.h"
#include "mainwindow.h"

class Dialog : public QDialog
{
private:
    MainWindow *window;
    CustomMap<QString, QString> *map;
    QComboBox *box;
    QPushButton *callButton;

    QString getString(const QString &title);

public:
    Dialog(MainWindow *window, CustomMap<QString, QString> *map,
           QWidget *parent = nullptr);

private slots:
    void call();
};

#endif  // DIALOG_H