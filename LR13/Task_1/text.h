#ifndef TEXT_H
#define TEXT_H

#include <QGridLayout>
#include <QMap>

#include "layout.h"
#include "letter.h"

class Text : public QWidget
{
    Q_OBJECT
private:
    QGridLayout *layout;
    QString text;
    QString hint;
    int offset;
    QVector<QVector<Letter *>> letters;
    Layout keyboardLayout;
    QMap<QString, QString> converter;
    static const int COLUMN_COUNT = 100;
    static const int ROW_COUNT = 3;

    QString generate();
    void generateConverter();
    void keyPressEvent(QKeyEvent *event) override;

public:
    explicit Text(QWidget *parent = nullptr);
    ~Text();

    void setHint(QString hint);
    void setText(QString text);
    void setKeyboardLayout(Layout layout);
    int getTypedWordsCount();
    void restart();
    void update();

signals:
    void startTyping();
    void stopTyping();
    void reset();
    void setActive(QString key);
    void openFile();
};

#endif  // TEXT_H