#ifndef DIALOG_H
#define DIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QGridLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>

#include "include/string.h"
#include "mainwindow.h"

class Dialog : public QDialog
{
private:
    MainWindow *window;
    String *string;
    QComboBox *box;
    QPushButton *callButton;

    char getCharacter();
    String getString();

public:
    Dialog(MainWindow *window, String *string, QDialog *next = nullptr,
           QWidget *parent = nullptr);

private slots:
    void call();
};

#endif  // DIALOG_H