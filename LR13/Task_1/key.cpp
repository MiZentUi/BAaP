#include "key.h"

#include <utility>

Key::Key(QString key, QWidget *parent) : key(std::move(key)), QLabel(parent)
{
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHeightForWidth(true);
    setSizePolicy(sizePolicy);
    setAlignment(Qt::AlignCenter);
    setStyleSheet(BASE_STYLE);
    update();
}

const QString Key::BASE_STYLE =
    ("border: 1px solid white;"
     "border-radius: 5px;"
     "color: white;"
     "font-size: 15px;");

void Key::setLetter(QString letter)
{
    key = letter;
    update();
}

void Key::setActive(bool active)
{
    if (active)
    {
        setStyleSheet(BASE_STYLE + "background-color: white; color: #181818");
    }
    else
    {
        setStyleSheet(BASE_STYLE);
    }
}

void Key::update()
{
    if (key == " ")
    {
        setMaximumSize(250, 50);
        setMinimumSize(50, 25);
    }
    else
    {
        setMaximumSize(50, 50);
        setMinimumSize(25, 25);
    }
    setText(key);
}

bool Key::operator==(const Key &other)
{
    return key.toLower() == other.key.toLower();
}

bool Key::operator==(const QString &string)
{
    return key.toLower() == string.toLower();
}

bool Key::operator!=(const Key &other) { return !(*this == other); }

bool Key::operator!=(const QString &string) { return !(*this == string); }