#include "dialog.h"

Dialog::Dialog(MainWindow *window, String *string, QDialog *next,
               QWidget *parent)
    : window(window),
      string(string),
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

    box->addItems({"append",        "at",
                   "back",          "c_str",
                   "capacity",      "clear",
                   "compare",       "contains",
                   "data",          "empty",
                   "ends_with",     "erase",
                   "find",          "find_first_not_of",
                   "find_first_of", "find_last_not_of",
                   "find_last_of",  "front",
                   "insert",        "length",
                   "max_size",      "pop_back",
                   "push_back",     "replace",
                   "reserve",       "resize",
                   "rfind",         "shrink_to_fit",
                   "size",          "starts_with",
                   "substr",        "",
                   "strcat",        "strcmp",
                   "strerror",      "strtok"});
    box->setMinimumContentsLength(50);
    layout()->addWidget(box);

    callButton->setText("Call");
    connect(callButton, &QPushButton::clicked, this, &Dialog::call);
    layout()->addWidget(callButton);
}

char Dialog::getCharacter()
{
    auto *dialog = new QDialog();
    dialog->setStyleSheet(styleSheet());
    dialog->setMaximumSize(maximumSize());
    dialog->setMinimumSize(minimumSize());
    dialog->setWindowTitle("Character");
    auto *layout = new QGridLayout();
    auto *lineEdit = new QLineEdit();
    auto *addButton = new QPushButton();
    addButton->setText("OK");
    connect(addButton, &QPushButton::clicked, dialog, &QDialog::close);
    layout->addWidget(lineEdit);
    layout->addWidget(addButton);
    dialog->setLayout(layout);
    dialog->exec();
    char chr = lineEdit->text().toLocal8Bit().constData()[0];
    delete dialog;
    return chr;
}

String Dialog::getString()
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

void Dialog::call()
{
    QString method = box->currentText();
    QMessageBox messageBox;
    messageBox.setStyleSheet(this->styleSheet() + "margin: 10px");
    messageBox.setMinimumSize(200, 100);
    messageBox.layout()->setAlignment(Qt::AlignCenter);
    if (method == "append")
    {
        string->append(getString());
        window->update();
    }
    else if (method == "at")
    {
        bool good = false;
        size_t index = QInputDialog::getInt(this, "Index", "Index", 0, 0,
                                            (int)string->size() - 1, 1, &good);
        if (good)
        {
            if (string->empty())
            {
                messageBox.setText("String is empty!");
            }
            else
            {
                messageBox.setText(QString(string->at(index)));
            }
            messageBox.exec();
        }
    }
    else if (method == "back")
    {
        if (string->empty())
        {
            messageBox.setText("String is empty!");
        }
        else
        {
            messageBox.setText(QString(string->back()));
        }
        messageBox.exec();
    }
    else if (method == "c_str")
    {
        messageBox.setText(
            QString::number(reinterpret_cast<size_t>(string->c_str()), 16));
        messageBox.exec();
    }
    else if (method == "capacity")
    {
        messageBox.setText(QString::number(string->capacity()));
        messageBox.exec();
    }
    else if (method == "clear")
    {
        string->clear();
        window->update();
    }
    else if (method == "compare")
    {
        messageBox.setText(QString::number(string->compare(getString())));
        messageBox.exec();
    }
    else if (method == "contains")
    {
        messageBox.setText(string->contains(getString().c_str()) ? "true"
                                                                 : "false");
        messageBox.exec();
    }
    else if (method == "data")
    {
        messageBox.setText(
            QString::number(reinterpret_cast<size_t>(string->data()), 16));
        messageBox.exec();
    }
    else if (method == "empty")
    {
        messageBox.setText(string->empty() ? "true" : "false");
        messageBox.exec();
    }
    else if (method == "ends_with")
    {
        messageBox.setText(string->ends_with(getString().c_str()) ? "true"
                                                                  : "false");
        messageBox.exec();
    }
    else if (method == "erase")
    {
        bool good = false;
        size_t index = QInputDialog::getInt(this, "Index", "Index", 0, 0,
                                            (int)string->size() - 1, 1, &good);
        if (good)
        {
            string->erase(index);
            window->update();
        }
    }
    else if (method == "find")
    {
        messageBox.setText(QString::number(string->find(getString())));
        messageBox.exec();
    }
    else if (method == "find_first_not_of")
    {
        messageBox.setText(
            QString::number(string->find_first_not_of(getString())));
        messageBox.exec();
    }
    else if (method == "find_first_of")
    {
        messageBox.setText(QString::number(string->find_first_of(getString())));
        messageBox.exec();
    }
    else if (method == "find_last_not_of")
    {
        messageBox.setText(
            QString::number(string->find_last_not_of(getString())));
        messageBox.exec();
    }
    else if (method == "find_last_of")
    {
        messageBox.setText(QString::number(string->find_last_of(getString())));
        messageBox.exec();
    }
    else if (method == "front")
    {
        if (string->empty())
        {
            messageBox.setText("String is empty!");
        }
        else
        {
            messageBox.setText(QString(string->front()));
        }
        messageBox.exec();
    }
    else if (method == "insert")
    {
        bool good = false;
        size_t index = QInputDialog::getInt(this, "Index", "Index", 0, 0,
                                            (int)string->size() - 1, 1, &good);
        if (good)
        {
            string->insert(index, getString());
            window->update();
        }
    }
    else if (method == "length")
    {
        messageBox.setText(QString::number(string->length()));
        messageBox.exec();
    }
    else if (method == "max_size")
    {
        messageBox.setText(QString::number(string->max_size()));
        messageBox.exec();
    }
    else if (method == "pop_back")
    {
        string->pop_back();
        window->update();
    }
    else if (method == "push_back")
    {
        string->push_back(getCharacter());
        window->update();
    }
    else if (method == "replace")
    {
        bool good = false;
        size_t index = QInputDialog::getInt(this, "Index", "Index", 0, 0,
                                            (int)string->size() - 1, 1, &good);
        if (good)
        {
            size_t count = QInputDialog::getInt(this, "Count", "Count", 1, 1,
                                                string->max_size() > INT32_MAX
                                                    ? INT32_MAX
                                                    : (int)string->max_size(),
                                                1, &good);
            if (good)
            {
                string->replace(index, count, getString());
                window->update();
            }
        }
    }
    else if (method == "reserve")
    {
        bool good = false;
        size_t capacity = QInputDialog::getInt(this, "Capacity", "Capacity",
                                               (int)string->capacity(), 0,
                                               INT32_MAX, 1, &good);
        if (good)
        {
            string->reserve(capacity);
            window->update();
        }
    }
    else if (method == "resize")
    {
        bool good = false;
        size_t size = QInputDialog::getInt(
            this, "Size", "Size", (int)string->size(), 0, INT32_MAX, 1, &good);
        if (good)
        {
            if (size > string->size())
            {
                string->resize(size, getCharacter());
            }
            else
            {
                string->resize(size);
            }
            window->update();
        }
    }
    else if (method == "rfind")
    {
        messageBox.setText(QString::number(string->rfind(getString())));
        messageBox.exec();
    }
    else if (method == "shrink_to_fit")
    {
        string->shrink_to_fit();
        window->update();
    }
    else if (method == "size")
    {
        messageBox.setText(QString::number(string->size()));
        messageBox.exec();
    }
    else if (method == "starts_with")
    {
        messageBox.setText(string->starts_with(getString().c_str()) ? "true"
                                                                    : "false");
        messageBox.exec();
    }
    else if (method == "substr")
    {
        bool good = false;
        size_t index = QInputDialog::getInt(this, "Index", "Index", 0, 0,
                                            (int)string->size() - 1, 1, &good);
        if (good)
        {
            size_t count = QInputDialog::getInt(this, "Count", "Count", 1, 1,
                                                string->max_size() > INT32_MAX
                                                    ? INT32_MAX
                                                    : (int)string->max_size(),
                                                1, &good);
            if (good)
            {
                messageBox.setText(string->substr(index, count).c_str());
                messageBox.exec();
            }
        }
    }
    else if (method == "strcat")
    {
        messageBox.setText(strcat(getString().data(), getString().c_str()));
        messageBox.exec();
    }
    else if (method == "strcmp")
    {
        messageBox.setText(
            QString::number(strcmp(getString().c_str(), getString().c_str())));
        messageBox.exec();
    }
    else if (method == "strerror")
    {
        bool good = false;
        int errnum =
            QInputDialog::getInt(this, "Error number", "Error number", 0, 0,
                                 (int)SYS_ERRLIST_SIZE, 1, &good);
        if (good)
        {
            messageBox.setText(strerror(errnum));
            messageBox.exec();
        }
    }
    else if (method == "strtok")
    {
        QString text;
        String str = getString();
        String delim = getString();
        char *token = strtok(str.data(), delim.c_str());
        while (token != nullptr)
        {
            text += QString(token) + '\n';
            token = strtok(nullptr, delim.c_str());
        }
        messageBox.setText(text);
        messageBox.exec();
    }
}