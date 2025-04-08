#ifndef DIALOG_H
#define DIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QGridLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>

#include "mainwindow.h"
#include "vector.h"

template <typename T>
class Dialog : public QDialog
{
private:
    MainWindow *window;
    Vector<T> *vector;
    QComboBox *box;
    QPushButton *callButton;

    QString getStringValue(Pair<Vector<int>, Vector<Pair<int, double>>> &value);
    QString getStringValue(int value);
    QString getStringValue(Pair<int, double> &value);

    void getValue(Pair<Vector<int>, Vector<Pair<int, double>>> &value);
    void getValue(int &value);
    void getValue(Pair<int, double> &value);

public:
    Dialog(MainWindow *window, Vector<T> *vector, QDialog *next = nullptr,
           QWidget *parent = nullptr);

private slots:
    void call();
};

template <typename T>
Dialog<T>::Dialog(MainWindow *window, Vector<T> *vector, QDialog *next,
                  QWidget *parent)
    : window(window),
      vector(vector),
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

    box->addItems({"at", "back", "capacity", "clear", "data", "empty", "erase",
                   "front", "insert", "max_size", "pop_back", "push_back",
                   "reserve", "resize", "size"});
    box->setMinimumContentsLength(50);
    layout()->addWidget(box);

    callButton->setText("Call");
    connect(callButton, &QPushButton::clicked, this, &Dialog::call);
    layout()->addWidget(callButton);
}

template <typename T>
QString Dialog<T>::getStringValue(
    Pair<Vector<int>, Vector<Pair<int, double>>> &value)
{
    QString stringValue = "first: ";
    for (int item : value.first)
    {
        stringValue += QString::number(item) + ' ';
    }
    stringValue += "\nsecond: ";
    for (auto item : value.second)
    {
        stringValue += '(' + QString::number(item.first) + ", " +
                       QString::number(item.second) + ") ";
    }
    return stringValue;
}

template <typename T>
QString Dialog<T>::getStringValue(int value)
{
    return QString::number(value);
}

template <typename T>
QString Dialog<T>::getStringValue(Pair<int, double> &value)
{
    return "first: " + QString::number(value.first) +
           "\nsecond: " + QString::number(value.second);
}

template <typename T>
void Dialog<T>::getValue(Pair<Vector<int>, Vector<Pair<int, double>>> &value)
{
    QDialog *dialog = new QDialog();
    dialog->setStyleSheet(styleSheet());
    dialog->setMaximumSize(maximumSize());
    dialog->setMinimumSize(minimumSize());
    QGridLayout *layout = new QGridLayout();
    QLineEdit *firstLineEdit = new QLineEdit();
    QLineEdit *secondLineEdit = new QLineEdit();
    QPushButton *addButton = new QPushButton();
    addButton->setText("Add");
    connect(addButton, &QPushButton::clicked, dialog, &QDialog::close);
    layout->addWidget(firstLineEdit);
    layout->addWidget(secondLineEdit);
    layout->addWidget(addButton);
    dialog->setLayout(layout);
    dialog->exec();
    Vector<int> firstVector;
    Vector<Pair<int, double>> secondVector;
    QStringList text = firstLineEdit->text().trimmed().split(QRegExp("\\s+"));
    for (QString str : text)
    {
        firstVector.push_back(str.toInt());
    }
    QRegularExpressionMatchIterator iter =
        QRegularExpression("\\([\\s0-9]*,[\\s.0-9]*\\)")
            .globalMatch(secondLineEdit->text());
    while (iter.hasNext())
    {
        QStringList strList = iter.next()
                                  .captured(0)
                                  .remove(QRegExp("[^,.0-9]*"))
                                  .split(QRegExp(",+"));
        secondVector.push_back(Pair(strList[0].toInt(), strList[1].toDouble()));
    }
    value.first = firstVector;
    value.second = secondVector;
    delete dialog;
}

template <typename T>
void Dialog<T>::getValue(int &value)
{
    value = QInputDialog::getInt(this, "Value", "Value");
}

template <typename T>
void Dialog<T>::getValue(Pair<int, double> &value)
{
    int first = QInputDialog::getInt(this, "First value", "First value");
    double second =
        QInputDialog::getDouble(this, "Second value", "Second value");
    value = Pair(first, second);
}

template <typename T>
void Dialog<T>::call()
{
    QString method = box->currentText();
    QMessageBox messageBox;
    messageBox.setStyleSheet(this->styleSheet() + "margin: 10px");
    messageBox.setMinimumSize(200, 100);
    messageBox.layout()->setAlignment(Qt::AlignCenter);
    if (method == "at")
    {
        bool ok = false;
        size_t index = QInputDialog::getInt(this, "Index", "Index", 0, 0,
                                            vector->size() - 1, 1, &ok);
        if (ok)
        {
            if (vector->empty())
            {
                messageBox.setText("Vector is empty!");
            }
            else
            {
                messageBox.setText(getStringValue(vector->at(index)));
            }
            messageBox.exec();
        }
    }
    else if (method == "back")
    {
        if (vector->empty())
        {
            messageBox.setText("Vector is empty!");
        }
        else
        {
            messageBox.setText(getStringValue(vector->back()));
        }
        messageBox.exec();
    }
    else if (method == "capacity")
    {
        messageBox.setText(QString::number(vector->capacity()));
        messageBox.exec();
    }
    else if (method == "clear")
    {
        vector->clear();
        window->update();
    }
    else if (method == "data")
    {
        messageBox.setText(QString::number((size_t)vector->data(), 16));
        messageBox.exec();
    }
    else if (method == "empty")
    {
        messageBox.setText(vector->empty() ? "true" : "false");
        messageBox.exec();
    }
    else if (method == "erase")
    {
        bool ok = false;
        size_t index = QInputDialog::getInt(this, "Index", "Index", 0, 0,
                                            vector->size() - 1, 1, &ok);
        if (ok)
        {
            vector->erase(vector->begin() + index);
            window->update();
        }
    }
    else if (method == "front")
    {
        if (vector->empty())
        {
            messageBox.setText("Vector is empty!");
        }
        else
        {
            messageBox.setText(getStringValue(vector->front()));
        }
        messageBox.exec();
    }
    else if (method == "insert")
    {
        bool ok = false;
        size_t index = QInputDialog::getInt(this, "Index", "Index", 0, 0,
                                            vector->size() - 1, 1, &ok);
        if (ok)
        {
            size_t count = QInputDialog::getInt(
                this, "Count", "Count", 1, 1,
                vector->max_size() > INT32_MAX ? INT32_MAX : vector->max_size(),
                1, &ok);
            if (ok)
            {
                T value;
                getValue(value);
                vector->insert(vector->cbegin() + index, count, value);
                window->update();
            }
        }
    }
    else if (method == "max_size")
    {
        messageBox.setText(QString::number(vector->max_size()));
        messageBox.exec();
    }
    else if (method == "pop_back")
    {
        vector->pop_back();
        window->update();
    }
    else if (method == "push_back")
    {
        T value;
        getValue(value);
        vector->push_back(value);
        window->update();
    }
    else if (method == "reserve")
    {
        bool ok = false;
        size_t capacity = QInputDialog::getInt(this, "Capacity", "Capacity",
                                               vector->capacity(), 0,
                                               vector->max_size(), 1, &ok);
        if (ok)
        {
            vector->reserve(capacity);
            window->update();
        }
    }
    else if (method == "resize")
    {
        bool ok = false;
        size_t size = QInputDialog::getInt(this, "Size", "Size", vector->size(),
                                           0, vector->max_size(), 1, &ok);
        if (ok)
        {
            if (size > vector->size())
            {
                T value;
                getValue(value);
                vector->resize(size, value);
            }
            else
            {
                vector->resize(size);
            }
            window->update();
        }
    }
    else if (method == "size")
    {
        messageBox.setText(QString::number(vector->size()));
        messageBox.exec();
    }
}

#endif  // DIALOG_H