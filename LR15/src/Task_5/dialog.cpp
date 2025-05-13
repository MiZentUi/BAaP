#include "dialog.h"

#include <QGridLayout>
#include <QInputDialog>
#include <QMessageBox>

Dialog::Dialog(MainWindow *window, Deque<QString> *deque, QDialog *next,
               QWidget *parent)
    : window(window),
      deque(deque),
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

    box->addItems({"size", "empty", "clear", "resize", "push_back",
                   "push_front", "pop_back", "pop_front", "front", "back",
                   "[]"});
    box->setMinimumContentsLength(50);
    layout()->addWidget(box);

    callButton->setText("Call");
    connect(callButton, &QPushButton::clicked, this, &Dialog::call);
    layout()->addWidget(callButton);
}

QString Dialog::getStringValue()
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

void Dialog::call()
{
    QString method = box->currentText();
    QMessageBox messageBox;
    messageBox.setStyleSheet(this->styleSheet() + "margin: 10px");
    messageBox.setMinimumSize(200, 100);
    messageBox.layout()->setAlignment(Qt::AlignCenter);
    if (method == "size")
    {
        messageBox.setText(QString::number(deque->size()));
        messageBox.exec();
    }
    else if (method == "empty")
    {
        messageBox.setText(deque->empty() ? "true" : "false");
        messageBox.exec();
    }
    else if (method == "clear")
    {
        deque->clear();
        window->update();
    }
    else if (method == "resize")
    {
        bool good = false;
        size_t size = QInputDialog::getInt(this, "Size", "Size", deque->size(),
                                           0, INT32_MAX, 1, &good);
        if (good)
        {
            deque->resize(size, getStringValue());
            window->update();
        }
    }
    else if (method == "push_back")
    {
        deque->push_back(getStringValue());
        window->update();
    }
    else if (method == "push_front")
    {
        deque->push_front(getStringValue());
        window->update();
    }
    else if (method == "pop_back")
    {
        deque->pop_back();
        window->update();
    }
    else if (method == "pop_front")
    {
        deque->pop_front();
        window->update();
    }
    else if (method == "front")
    {
        if (deque->size() > 0)
        {
            deque->front() = getStringValue();
        }
        window->update();
    }
    else if (method == "back")
    {
        if (deque->size() > 0)
        {
            deque->back() = getStringValue();
        }
        window->update();
    }
    else if (method == "[]")
    {
        bool good = false;
        size_t index = QInputDialog::getInt(
            this, "Index", "Index", 0, 0,
            !deque->empty() ? deque->size() - 1 : 0, 1, &good);
        if (good)
        {
            if (index < deque->size())
            {
                (*deque)[index] = getStringValue();
            }
            window->update();
        }
    }
}