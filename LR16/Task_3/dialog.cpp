#include "dialog.h"

#include <QGridLayout>
#include <QInputDialog>
#include <QMessageBox>

Dialog::Dialog(MainWindow *window, CustomMap<QString, QString> *map,
               QWidget *parent)
    : window(window),
      map(map),
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

    box->addItems({"size", "empty", "contains", "insert", "remove", "clear",
                   "min", "max", "inorder", "[]"});
    box->setMinimumContentsLength(50);
    layout()->addWidget(box);

    callButton->setText("Call");
    connect(callButton, &QPushButton::clicked, this, &Dialog::call);
    layout()->addWidget(callButton);
}

QString Dialog::getString(const QString &title)
{
    auto *dialog = new QDialog();
    dialog->setStyleSheet(styleSheet());
    dialog->setMaximumSize(maximumSize());
    dialog->setMinimumSize(minimumSize());
    dialog->setWindowTitle(title);
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
        messageBox.setText(QString::number(map->size()));
        messageBox.exec();
    }
    else if (method == "empty")
    {
        messageBox.setText(map->empty() ? "true" : "false");
        messageBox.exec();
    }
    else if (method == "contains")
    {
        messageBox.setText(map->contains(getString("Key")) ? "true" : "false");
        messageBox.exec();
    }
    else if (method == "insert")
    {
        map->insert({getString("Key"), getString("Value")});
        window->update();
    }
    else if (method == "remove")
    {
        map->remove(getString("Key"));
        window->update();
    }
    else if (method == "clear")
    {
        map->clear();
        window->update();
    }
    else if (method == "min" && !map->empty())
    {
        messageBox.setText('{' + map->min().first + ": " + map->min().second +
                           '}');
        messageBox.exec();
    }
    else if (method == "max" && !map->empty())
    {
        messageBox.setText('{' + map->max().first + ": " + map->max().second +
                           '}');
        messageBox.exec();
    }
    else if (method == "inorder")
    {
        QString result;
        for (const std::pair<QString, QString> &entry : map->inorder())
        {
            result += '{' + entry.first + ": " + entry.second + "} ";
        }
        messageBox.setText(result);
        messageBox.exec();
    }
    else if (method == "[]")
    {
        QString key = getString("Key");
        (*map)[key] = getString("Value (current: " + (*map)[key] + ')');
        window->update();
    }
}