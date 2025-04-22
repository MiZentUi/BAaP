#include "text.h"

#include <QKeyEvent>

#include "keyboard.h"

Text::Text(QWidget *parent)
    : QWidget(parent),
      layout(new QGridLayout()),
      keyboardLayout(English),
      offset(0)
{
    setFont(QFont("Noto Sans Mono"));
    setMaximumHeight(35 * ROW_COUNT);
    grabKeyboard();
    setLayout(layout);
    layout->setSpacing(0);
    for (int i = 0; i < ROW_COUNT; i++)
    {
        letters.push_back(QVector<Letter *>());
        for (int j = 0; j < COLUMN_COUNT; j++)
        {
            auto *letter = new Letter();
            letter->setFont(QFont("Noto Sans Mono"));
            layout->addWidget(letter, i, j);
            letters[i].push_back(letter);
        }
    }
    generateConverter();
    restart();
}

Text::~Text()
{
    for (auto &row : letters)
    {
        for (Letter *&letter : row)
        {
            letter->~Letter();
        }
    }
}

QString Text::generate()
{
    QMap<Layout, QString> alphabets{
        {English, "abcdefghijklmnopqrstuvwxyz"},
        {Russian, "абвгдежзийклмнопстуфхцчшщъыьэюя"},
        {German, "abcdefghijklmnopqrstuvwxyzäöü"},
        {French, "abcdefghijklmnpqrstuvwxyzù"},
        {Arabic, "ءؤئاابةتثجحخدرزسشصضطظعغفقكللمنهوىي"},
        {Chinese, "一中人十卜口土大女尸山廿弓心戈手日月木水火田竹重金難"},
        {Belarusian, "абвгдежзйклмнопрстуфхцчшыьэюяіў"},
        {Hebrew, "אבגדהוזחטיךכלםמןנסעףפץצקרשת"}};
    srand(time(nullptr));
    QString result_text;
    for (int i = 2; i <= 6; i++)
    {
        for (int j = 0; j < (COLUMN_COUNT - i) / 2; j += i + 1)
        {
            QString word;
            for (int k = 0; k < i; k++)
            {
                word += alphabets[keyboardLayout]
                                 [rand() % alphabets[keyboardLayout].size()];
            }
            result_text += word + " ";
        }
    }
    result_text = result_text.left(result_text.size());
    return result_text;
}

void Text::generateConverter()
{
    converter.clear();
    for (int i = 0; i < Keyboard::layouts[English].size(); i++)
    {
        for (int j = 0; j < Keyboard::layouts[English][i].size(); j++)
        {
            converter[Keyboard::layouts[English][i][j].toLower()] =
                Keyboard::layouts[keyboardLayout][i][j].toLower();
        }
    }
}

void Text::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier)
    {
        if (event->key() == Qt::Key_R)
        {
            restart();
        }
        else if (event->key() == Qt::Key_O)
        {
            emit openFile();
        }
    }
    else if (!event->text().isEmpty())
    {
        if (text.isEmpty())
        {
            emit startTyping();
        }
        if (event->text()[0].isPrint() && text.size() < hint.size())
        {
            if (converter.contains(event->text().toLower()))
            {
                text += event->text().isUpper() && event->text()[0].isLetter()
                            ? converter[event->text().toLower()].toUpper()
                            : converter[event->text().toLower()];
            }
            else
            {
                text += event->text();
            }
        }
        else if (event->text() == "\b")
        {
            text = text.left(text.size() - 1);
        }
        update();
    }
}

void Text::setHint(QString hint)
{
    this->hint = hint;
    text = "";
    offset = 0;
    update();
    reset();
}

void Text::setText(QString text) { this->text = text; }

void Text::setKeyboardLayout(Layout layout)
{
    this->keyboardLayout = layout;
    generateConverter();
    restart();
}

int Text::getTypedWordsCount()
{
    return hint.left(text.size()).count(QRegExp("[^\\s]+"));
}

void Text::update()
{
    if (text.size() - offset > COLUMN_COUNT * (ROW_COUNT / 2 + 1) &&
        text.size() < hint.size() - COLUMN_COUNT)
    {
        offset += COLUMN_COUNT;
    }
    int index = offset;
    for (auto &row : letters)
    {
        for (Letter *&letter : row)
        {
            letter->reset();
            if (keyboardLayout == Chinese)
            {
                letter->setFontSize(15);
            }
            if (index < text.size() && index < hint.size())
            {
                letter->setLetter(QString(hint[index]));
                if (text[index] == hint[index])
                {
                    letter->correct();
                }
                else
                {
                    letter->incorrect();
                }
            }
            else if (index < hint.size())
            {
                letter->setLetter(QString(hint[index]));
            }
            index++;
        }
    }
    emit setActive("");
    if (text.size() < hint.size())
    {
        letters[(text.size() - offset) / COLUMN_COUNT]
               [(text.size() - offset) % COLUMN_COUNT]
                   ->next();
        emit setActive(letters[(text.size() - offset) / COLUMN_COUNT]
                              [(text.size() - offset) % COLUMN_COUNT]
                                  ->text());
    }
    if (text.size() == hint.size())
    {
        emit stopTyping();
    }
}

void Text::restart()
{
    hint = generate();
    text = "";
    offset = 0;
    update();
    emit reset();
}