#ifndef DIALOG_H
#define DIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QGridLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>

#include "bitset.h"
#include "mainwindow.h"

template <std::size_t N>
class Dialog : public QDialog
{
private:
    MainWindow *window;
    BitSet<N> *bitset;
    QComboBox *box;
    QPushButton *callButton;

    String getString();

public:
    Dialog(MainWindow *window, BitSet<N> *bitset, QDialog *next = nullptr,
           QWidget *parent = nullptr);

private slots:
    void call();
};

template <std::size_t N>
Dialog<N>::Dialog(MainWindow *window, BitSet<N> *bitset, QDialog *next,
                  QWidget *parent)
    : window(window),
      bitset(bitset),
      box(new QComboBox()),
      callButton(new QPushButton()),
      QDialog(parent)
{
    setStyleSheet(
        "background-color: #181818;"
        "color: white;");
    setMaximumSize(1920, 500);
    setMinimumSize(150, 100);
    setWindowFlags(Qt::WindowStaysOnTopHint);

    setLayout(new QGridLayout());
    layout()->setAlignment(Qt::AlignCenter);

    box->addItems({"all", "any", "test", "none", "count", "size", "set",
                   "reset", "flip", "to_string", "to_ulong", "to_ullong", "[]",
                   "~", "&", "|", "^"});
    box->setMinimumContentsLength(50);
    layout()->addWidget(box);

    callButton->setText("Call");
    connect(callButton, &QPushButton::clicked, this, &Dialog::call);
    layout()->addWidget(callButton);
}

template <std::size_t N>
String Dialog<N>::getString()
{
    auto *dialog = new QDialog();
    dialog->setStyleSheet(styleSheet());
    dialog->setMaximumSize(maximumSize());
    dialog->setMinimumSize(minimumSize());
    dialog->setWindowTitle("String");
    auto *layout = new QGridLayout();
    auto *lineEdit = new QLineEdit();
    auto *addButton = new QPushButton();
    addButton->setText("OK");
    connect(addButton, &QPushButton::clicked, dialog, &QDialog::close);
    layout->addWidget(lineEdit);
    layout->addWidget(addButton);
    dialog->setLayout(layout);
    dialog->exec();
    String str = lineEdit->text().toLocal8Bit().constData();
    delete dialog;
    return str;
}

template <std::size_t N>
void Dialog<N>::call()
{
    QString method = box->currentText();
    QMessageBox messageBox;
    messageBox.setStyleSheet(this->styleSheet() + "margin: 10px");
    messageBox.setMinimumSize(200, 100);
    messageBox.layout()->setAlignment(Qt::AlignCenter);
    if (method == "all")
    {
        messageBox.setText(bitset->all() ? "true" : "false");
        messageBox.exec();
    }
    else if (method == "any")
    {
        messageBox.setText(bitset->any() ? "true" : "false");
        messageBox.exec();
    }
    else if (method == "test")
    {
        bool good = false;
        size_t index = QInputDialog::getInt(this, "Index", "Index", 0, 0,
                                            (int)bitset->size() - 1, 1, &good);
        if (good)
        {
            messageBox.setText(bitset->test(index) ? "true" : "false");
            messageBox.exec();
        }
    }
    else if (method == "none")
    {
        messageBox.setText(bitset->none() ? "true" : "false");
        messageBox.exec();
    }
    else if (method == "count")
    {
        messageBox.setText(QString::number(bitset->count()));
        messageBox.exec();
    }
    else if (method == "size")
    {
        messageBox.setText(QString::number(bitset->size()));
        messageBox.exec();
    }
    else if (method == "set")
    {
        bool good = false;
        size_t index = QInputDialog::getInt(this, "Index", "Index", 0, -1,
                                            (int)bitset->size() - 1, 1, &good);
        if (good)
        {
            if (index == -1)
            {
                bitset->set();
            }
            else
            {
                bitset->set(index);
            }
            window->update();
        }
    }
    else if (method == "reset")
    {
        bool good = false;
        size_t index = QInputDialog::getInt(this, "Index", "Index", 0, -1,
                                            (int)bitset->size() - 1, 1, &good);
        if (good)
        {
            if (index == -1)
            {
                bitset->reset();
            }
            else
            {
                bitset->reset(index);
            }
            window->update();
        }
    }
    else if (method == "flip")
    {
        bool good = false;
        size_t index = QInputDialog::getInt(this, "Index", "Index", 0, -1,
                                            (int)bitset->size() - 1, 1, &good);
        if (good)
        {
            if (index == -1)
            {
                bitset->flip();
            }
            else
            {
                bitset->flip(index);
            }
            window->update();
        }
    }
    else if (method == "to_string")
    {
        messageBox.setText(QString(bitset->to_string().c_str()));
        messageBox.exec();
    }
    else if (method == "to_ulong")
    {
        messageBox.setText(QString::number(bitset->to_ulong()));
        messageBox.exec();
    }
    else if (method == "to_ullong")
    {
        messageBox.setText(QString::number(bitset->to_ullong()));
        messageBox.exec();
    }
    else if (method == "[]")
    {
        bool good = false;
        size_t index = QInputDialog::getInt(this, "Index", "Index", 0, 0,
                                            (int)bitset->size() - 1, 1, &good);
        if (good)
        {
            messageBox.setText(bitset[index] == true ? "true" : "false");
            messageBox.exec();
        }
    }
    else if (method == "~")
    {
        messageBox.setText(QString((~(*bitset)).to_string().c_str()));
        messageBox.exec();
    }
    else if (method == "&")
    {
        messageBox.setText(
            QString((*bitset & BitSet<N>(getString())).to_string().c_str()));
        messageBox.exec();
    }
    else if (method == "|")
    {
        messageBox.setText(
            QString((*bitset | BitSet<N>(getString())).to_string().c_str()));
        messageBox.exec();
    }
    else if (method == "^")
    {
        messageBox.setText(
            QString((*bitset ^ BitSet<N>(getString())).to_string().c_str()));
        messageBox.exec();
    }
}

#endif  // DIALOG_H