#include "keyboard.h"

Keyboard::Keyboard(Layout layout, QWidget *parent)
    : layout(layout), QVBoxLayout(parent)
{
    for (auto row : layouts[layout])
    {
        auto *row_layout = new QHBoxLayout();
        row_layout->setSpacing(5);
        row_layout->addStretch(1);
        for (auto key_string : row)
        {
            auto *key = new Key(key_string);
            key->setFont(QFont("Noto Sans Mono"));
            row_layout->addWidget(key, 1);
            keys.push_back(key);
        }
        row_layout->addStretch(1);
        addLayout(row_layout, 1);
    }
}

Keyboard::~Keyboard()
{
    for (Key *&key : keys)
    {
        key->~Key();
    }
}

const QMap<Layout, QVector<QVector<QString>>> Keyboard::layouts = {
    {English,
     {{"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]"},
      {"A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'"},
      {"Z", "X", "C", "V", "B", "N", "M", ",", ".", "/"},
      {" "}}},
    {Russian,
     {{"Й", "Ц", "У", "К", "Е", "Н", "Г", "Ш", "Щ", "З", "Х", "Ъ"},
      {"Ф", "Ы", "В", "А", "П", "Р", "О", "Л", "Д", "Ж", "Э"},
      {"Я", "Ч", "С", "М", "И", "Т", "Ь", "Б", "Ю", "."},
      {" "}}},
    {German,
     {{"Q", "W", "E", "R", "T", "Z", "U", "I", "O", "P", "Ü", "+"},
      {"A", "S", "D", "F", "G", "H", "J", "K", "L", "Ö", "Ä"},
      {"Y", "X", "C", "V", "B", "N", "M", ",", ".", "-"},
      {" "}}},
    {French,
     {{"A", "Z", "E", "R", "T", "Y", "U", "I", "O", "P", "^", "$"},
      {"Q", "S", "D", "F", "G", "H", "J", "K", "L", "M", "ù"},
      {"W", "X", "C", "V", "B", "N", ",", ";", ":", "!"},
      {" "}}},
    {Arabic,
     {{"ض", "ص", "ث", "ق", "ف", "غ", "ع", "`", "خ", "ح", "ج", "د"},
      {"ش", "س", "ي", "ب", "ل", "ا", "ت", "ن", "م", "ك", "ط"},
      {"ئ", "ء", "ؤ", "ر", "ﻻ", "ى", "ة", "و", "ز", "ظ"},
      {" "}}},
    {Chinese,
     {{"手", "拉", "水", "口", "廿", "卜", "山", "戈", "人", "心", "[", "]"},
      {"日", "尸", "木", "火", "土", "竹", "十", "大", "中", ";", "'"},
      {"重", "難", "金", "女", "月", "弓", "一", ",", ".", "/"},
      {" "}}},
    {Belarusian,
     {{"Й", "Ц", "У", "К", "Е", "Н", "Г", "Ш", "Ў", "З", "Х", "'"},
      {"Ф", "Ы", "В", "А", "П", "Р", "О", "Л", "Д", "Ж", "Э"},
      {"Я", "Ч", "С", "М", "І", "Т", "Ь", "Б", "Ю", "."},
      {" "}}},
    {Hebrew,
     {{"/", "'", "ק", "ר", "א", "ט", "ו", "ן", "ם", "פ", "]", "["},
      {"ש", "ד", "ג", "כ", "ע", "י", "ח", "ל", "ך", "ף", ","},
      {"ז", "ס", "ב", "ה", "נ", "מ", "צ", "ת", "ץ", "."},
      {" "}}}};

void Keyboard::setLayout(Layout layout)
{
    this->layout = layout;
    update();
}

void Keyboard::setActive(QString key_string)
{
    for (Key *key : keys)
    {
        if (*key == key_string)
        {
            key->setActive(true);
        }
        else
        {
            key->setActive(false);
        }
    }
}

void Keyboard::update()
{
    int index = 0;
    for (auto row : layouts[layout])
    {
        for (auto key_string : row)
        {
            keys[index++]->setLetter(key_string);
        }
    }
}