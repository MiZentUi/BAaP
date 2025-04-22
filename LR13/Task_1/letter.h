#ifndef LETTER_H
#define LETTER_H

#include <QLabel>

class Letter : public QLabel
{
private:
    QString letter;
    QString color;
    QString underline_color;
    bool underlined;
    int underline_width;
    int font_size;

public:
    explicit Letter(QString letter = " ", QWidget *parent = nullptr);

    void setLetter(QString letter);
    void setColor(QString color);
    void setUnderlineColor(QString color);
    void setUnderlined(bool underlined);
    void setFontSize(int size);
    void correct();
    void incorrect();
    void extra();
    void next();
    void reset();
    void update();

    QString text();
};

#endif  // LETTER_H