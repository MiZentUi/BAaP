#ifndef DIALOG_H
#define DIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QPushButton>
#include <QString>

#include "deque.h"
#include "mainwindow.h"

class Dialog : public QDialog
{
private:
    MainWindow *window;
    Deque<QString> *deque;
    QComboBox *box;
    QPushButton *callButton;

    QString getStringValue();

public:
    Dialog(MainWindow *window, Deque<QString> *deque, QDialog *next = nullptr,
           QWidget *parent = nullptr);

private slots:
    void call();
};

#endif  // DIALOG_H