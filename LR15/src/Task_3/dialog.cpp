#include "dialog.h"

#include <QGridLayout>
#include <QInputDialog>
#include <QMessageBox>

Dialog::Dialog(MainWindow *window, CustomStackHashTable *hashTable,
               QDialog *next, QWidget *parent)
    : window(window),
      hashTable(hashTable),
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

    box->addItems({"size", "empty", "contains", "clear", "randomFill",
                   "getPairByMaxKey", "[]"});
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
        messageBox.setText(QString::number(hashTable->size()));
        messageBox.exec();
    }
    else if (method == "empty")
    {
        messageBox.setText(hashTable->empty() ? "true" : "false");
        messageBox.exec();
    }
    else if (method == "contains")
    {
        bool good = false;
        long long key = QInputDialog::getInt(this, "Key", "Key", 0, INT32_MIN,
                                             INT32_MAX, 1, &good);
        if (good)
        {
            messageBox.setText(hashTable->contains(key) ? "true" : "false");
            messageBox.exec();
        }
    }
    else if (method == "clear")
    {
        hashTable->clear();
        window->update();
    }
    else if (method == "randomFill")
    {
        bool good = false;
        size_t count = QInputDialog::getInt(this, "Count", "Count", 0, 0,
                                            INT32_MAX, 1, &good);
        if (good)
        {
            hashTable->randomFill(count);
            window->update();
        }
    }
    else if (method == "getPairByMaxKey")
    {
        std::pair<long long, QString> maxPair = hashTable->getPairByMaxKey();
        messageBox.setText("{" + QString::number(maxPair.first) + ", " +
                           maxPair.second + "}");
        messageBox.exec();
    }
    else if (method == "[]")
    {
        bool good = false;
        long long key = QInputDialog::getInt(this, "Key", "Key", 0, INT32_MIN,
                                             INT32_MAX, 1, &good);
        if (good)
        {
            (*hashTable)[key] = getStringValue();
            window->update();
        }
    }
}