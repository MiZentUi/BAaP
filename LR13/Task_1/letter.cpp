#include "letter.h"

#include <utility>

Letter::Letter(QString letter, QWidget *parent)
    : letter(std::move(letter)),
      color("slategrey"),
      underline_color("slategrey"),
      underline_width(1),
      font_size(0),
      underlined(false),
      QLabel(parent)
{
    setMaximumSize(30, 30);
    setAlignment(Qt::AlignCenter);
    update();
}

void Letter::setLetter(QString letter)
{
    this->letter = letter;
    update();
}

void Letter::setColor(QString color)
{
    this->color = color;
    update();
}

void Letter::setUnderlineColor(QString color)
{
    underline_color = color;
    update();
}

void Letter::setUnderlined(bool underlined)
{
    this->underlined = underlined;
    update();
}

void Letter::setFontSize(int size)
{
    font_size = size;
    update();
}

void Letter::correct()
{
    color = "white";
    update();
}

void Letter::incorrect()
{
    color = "lightcoral";
    update();
}

void Letter::extra()
{
    color = "lightcoral";
    underline_color = "lightcoral";
    underline_width = 1;
    underlined = true;
    update();
}

void Letter::next()
{
    underline_color = "cornflowerblue";
    underline_width = 3;
    underlined = true;
    update();
}

void Letter::reset()
{
    letter = " ";
    color = "slategrey";
    underline_color = "slategrey";
    underline_width = 1;
    font_size = 20;
    underlined = false;
    update();
}

void Letter::update()
{
    setStyleSheet("font-size: " + QString::number(font_size) + "px;" +
                  "color: " + color + ";" +
                  (underlined
                       ? ("border-bottom: " + QString::number(underline_width) +
                          "px solid " + underline_color + ";")
                       : ""));
    setText(letter);
}

QString Letter::text() { return letter; }