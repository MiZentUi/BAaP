#ifndef KEY_H
#define KEY_H

#include <QChar>
#include <QLabel>

class Key : public QLabel
{
private:
    QString key;
    static const QString BASE_STYLE;

public:
    explicit Key(QString key = "", QWidget *parent = nullptr);

    void setLetter(QString letter);
    void setActive(bool active);
    void update();

    bool operator==(const Key &other);
    bool operator==(const QString &string);
    bool operator!=(const Key &other);
    bool operator!=(const QString &string);
};

#endif  // KEY_H