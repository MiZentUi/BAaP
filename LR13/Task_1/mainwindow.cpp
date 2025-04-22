#include "mainwindow.h"

#include <qnamespace.h>

#include <QComboBox>
#include <QFileDialog>
#include <QTextStream>
#include <QTimer>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      text(new Text()),
      keyboard(new Keyboard()),
      timer(new QTimer()),
      timerLabel(new QLabel()),
      wordsPerMinute(new QLabel()),
      seconds(0)
{
    ui->setupUi(this);

    this->setWindowTitle("BlindTyping");
    this->setStyleSheet(
        "background-color: #181818;"
        "color: white;");

    auto *vLayout = new QVBoxLayout();
    auto *gridLayout = new QGridLayout();
    auto *hLayout = new QHBoxLayout();
    auto *language = new QComboBox();

    language->setFont(QFont("Noto Sans Mono", 12));
    language->addItems({"English", "Русский", "Deutsch", "Français", "اَلْعَرَبِيَّةُ",
                        "汉语", "Беларуская", "עִבְרִית"});

    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 5px;"
        "padding: 5px;");
    timerLabel->setText("00:00");
    timerLabel->setFont(QFont("Noto Sans Mono", 12));
    timerLabel->setMaximumHeight(30);

    wordsPerMinute->setAlignment(Qt::AlignCenter);
    wordsPerMinute->setStyleSheet(
        "background-color: #1f1f1f;"
        "border-color: #2b2b2b;"
        "border-radius: 5px;"
        "padding: 5px;");
    wordsPerMinute->setText("0 WPM");
    wordsPerMinute->setFont(QFont("Noto Sans Mono", 12));
    wordsPerMinute->setMaximumHeight(30);

    hLayout->addWidget(language);
    hLayout->addWidget(timerLabel);
    hLayout->addWidget(wordsPerMinute);
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 2);
    gridLayout->setColumnStretch(2, 1);
    gridLayout->addWidget(text, 0, 1);
    gridLayout->addLayout(hLayout, 1, 1);
    vLayout->addLayout(gridLayout);
    vLayout->addLayout(keyboard);
    centralWidget()->setLayout(vLayout);

    connect(text, &Text::setActive, keyboard, &Keyboard::setActive);
    connect(language, &QComboBox::currentTextChanged, this,
            &MainWindow::changeLanguage);
    connect(timer, &QTimer::timeout, this, &MainWindow::statusUpdate);
    connect(text, &Text::startTyping, [this] { timer->start(0); });
    connect(text, &Text::stopTyping, [this] { timer->stop(); });
    connect(text, &Text::reset,
            [this]
            {
                seconds = 0;
                timer->stop();
                timerLabel->setText("00:00");
                wordsPerMinute->setText("0 WPM");
            });
    connect(text, &Text::openFile, this, &MainWindow::openFile);

    text->update();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete text;
    delete keyboard;
    delete timer;
    delete timerLabel;
    delete wordsPerMinute;
}

void MainWindow::changeLanguage(const QString &item)
{
    QMap<QString, Layout> stringToLayout{
        {"english", English},       {"русский", Russian}, {"deutsch", German},
        {"français", French},       {"اَلْعَرَبِيَّةُ", Arabic},  {"汉语", Chinese},
        {"беларуская", Belarusian}, {"עִבְרִית", Hebrew}};
    keyboard->setLayout(stringToLayout[item.toLower()]);
    text->setKeyboardLayout(stringToLayout[item.toLower()]);
}

void MainWindow::statusUpdate()
{
    timerLabel->setText(QString::number(seconds / 60).rightJustified(2, '0') +
                        ":" +
                        QString::number(seconds % 60).rightJustified(2, '0'));
    if (seconds > 0)
    {
        wordsPerMinute->setText(
            QString::number(
                (int)((double)text->getTypedWordsCount() / seconds * 60)) +
            " WPM");
    }
    else
    {
        wordsPerMinute->setText("0 WPM");
    }
    seconds++;
    timer->start(1000);
}

void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName(
        this, "Open Text File", "/home", "Text Files (*.txt)");
    if (!filename.isEmpty())
    {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream input(&file);
            text->setHint(input.readAll());
        }
    }
}