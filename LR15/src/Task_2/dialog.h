#ifndef DIALOG_H
#define DIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QGridLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <cstdint>
#include <utility>

#include "custombst.h"
#include "mainwindow.h"

template <typename K = long long, typename V = QString>
class Dialog : public QDialog
{
private:
    MainWindow *window;
    CustomBST<K, V> *bst;
    QComboBox *box;
    QPushButton *callButton;

    QString getStringValue();

public:
    Dialog(MainWindow *window, CustomBST<K, V> *bst, QDialog *next = nullptr,
           QWidget *parent = nullptr);

private slots:
    void call();
};

template <typename K, typename V>
Dialog<K, V>::Dialog(MainWindow *window, CustomBST<K, V> *bst, QDialog *next,
                     QWidget *parent)
    : window(window),
      bst(bst),
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

    box->addItems({"balance", "insert", "search", "remove", "inorderTravelsal",
                   "preorderTravelsal", "postorderTravelsal",
                   "getValueByMiddleKey"});
    box->setMinimumContentsLength(50);
    layout()->addWidget(box);

    callButton->setText("Call");
    connect(callButton, &QPushButton::clicked, this, &Dialog::call);
    layout()->addWidget(callButton);
}

template <typename K, typename V>
QString Dialog<K, V>::getStringValue()
{
    auto *dialog = new QDialog();
    dialog->setStyleSheet(styleSheet());
    dialog->setMaximumSize(maximumSize());
    dialog->setMinimumSize(minimumSize());
    dialog->setWindowTitle("Value");
    auto *layout = new QGridLayout();
    auto *lineEdit = new QLineEdit();
    auto *addButton = new QPushButton();
    addButton->setText("OK");
    connect(addButton, &QPushButton::clicked, dialog, &QDialog::close);
    layout->addWidget(lineEdit);
    layout->addWidget(addButton);
    dialog->setLayout(layout);
    dialog->exec();
    QString str = lineEdit->text().toLocal8Bit().constData();
    delete dialog;
    return str;
}

template <typename K, typename V>
void Dialog<K, V>::call()
{
    QString method = box->currentText();
    QMessageBox messageBox;
    messageBox.setStyleSheet(this->styleSheet() + "margin: 10px");
    messageBox.setMinimumSize(200, 100);
    messageBox.layout()->setAlignment(Qt::AlignCenter);
    if (method == "balance")
    {
        bst->balance();
        window->update();
    }
    else if (method == "insert")
    {
        bool ok = false;
        size_t key = QInputDialog::getInt(this, "Key", "Key", 0, INT32_MIN,
                                          INT32_MAX, 1, &ok);
        if (ok)
        {
            bst->insert(key, getStringValue());
            window->update();
        }
    }
    else if (method == "search")
    {
        bool ok = false;
        size_t key = QInputDialog::getInt(this, "Key", "Key", 0, INT32_MIN,
                                          INT32_MAX, 1, &ok);
        if (ok)
        {
            messageBox.setText(bst->search(key));
            messageBox.exec();
        }
    }
    else if (method == "remove")
    {
        bool ok = false;
        size_t key = QInputDialog::getInt(this, "Key", "Key", 0, INT32_MIN,
                                          INT32_MAX, 1, &ok);
        if (ok)
        {
            bst->remove(key);
            window->update();
        }
    }
    else if (method == "inorderTravelsal")
    {
        std::vector<std::pair<K, V>> nodes;
        bst->inorderTraversal(nodes);
        QString result;
        for (const std::pair<K, V> &node : nodes)
        {
            result +=
                "{" + QString::number(node.first) + ", " + node.second + "} ";
        }
        messageBox.setText(result);
        messageBox.exec();
    }
    else if (method == "preorderTravelsal")
    {
        std::vector<std::pair<K, V>> nodes;
        bst->preorderTraversal(nodes);
        QString result;
        for (const std::pair<K, V> &node : nodes)
        {
            result +=
                "{" + QString::number(node.first) + ", " + node.second + "} ";
        }
        messageBox.setText(result);
        messageBox.exec();
    }
    else if (method == "postorderTravelsal")
    {
        std::vector<std::pair<K, V>> nodes;
        bst->postorderTraversal(nodes);
        QString result;
        for (const std::pair<K, V> &node : nodes)
        {
            result +=
                "{" + QString::number(node.first) + ", " + node.second + "} ";
        }
        messageBox.setText(result);
        messageBox.exec();
    }
    else if (method == "getValueByMiddleKey")
    {
        K key;
        V value = bst->getValueByMiddleKey(&key);
        messageBox.setText("{" + QString::number(key) + ", " + value + "}");
        messageBox.exec();
    }
}

#endif  // DIALOG_H