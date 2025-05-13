#include "mainwindow.h"

#include <chrono>
#include <cstddef>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      plot(new QCustomPlot()),
      timer(new QTimer())
{
    ui->setupUi(this);

    this->setWindowTitle("Task 4");
    this->setStyleSheet(
        "background-color: #181818;"
        "color: white;");

    plot->setFont(QFont("Noto Sans Mono", 12));
    plot->setBackground(QColor("#1f1f1f"));
    plot->xAxis->setTickLabelColor(Qt::white);
    plot->xAxis->setLabelColor(Qt::white);
    plot->xAxis->setBasePen(QPen(Qt::white));
    plot->yAxis->setTickLabelColor(Qt::white);
    plot->yAxis->setLabelColor(Qt::white);
    plot->yAxis->setBasePen(QPen(Qt::white));
    plot->legend->setBrush(QColor("#1f1f1f"));
    plot->legend->setTextColor(Qt::white);
    plot->legend->setVisible(true);
    plot->axisRect()->insetLayout()->setInsetAlignment(
        0, Qt::AlignLeft | Qt::AlignTop);

    plot->addGraph();
    plot->addGraph();
    plot->addGraph();
    plot->addGraph();

    plot->graph(0)->setName("HashTable 16");
    plot->graph(1)->setName("HashTable 64");
    plot->graph(2)->setName("HashTable 128");
    plot->graph(3)->setName("HashTable 2048");

    plot->graph(0)->setPen(QPen(Qt::red));
    plot->graph(1)->setPen(QPen(Qt::green));
    plot->graph(2)->setPen(QPen(Qt::blue));
    plot->graph(3)->setPen(QPen(Qt::white));

    plot->xAxis->setLabel("Size");
    plot->yAxis->setLabel("Time, ns");

    connect(timer, &QTimer::timeout, this, &MainWindow::updateGraphs);

    setCentralWidget(plot);

    timer->start(100);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::updateGraphs()
{
    std::size_t full_time_ms = 10000;
    std::size_t timeout_ms = 100;
    std::size_t max_size = 5000000;
    std::size_t search_key = rand();
    srand(time(nullptr));

    auto begin = std::chrono::high_resolution_clock::now();
    hashTable16[search_key];
    auto end = std::chrono::high_resolution_clock::now();
    std::size_t time =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
            .count();
    std::size_t max_time = time;
    plot->graph(0)->addData(hashTable16.size(), time);

    begin = std::chrono::high_resolution_clock::now();
    hashTable64[search_key];
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
               .count();
    if (time > max_time)
    {
        max_time = time;
    }
    plot->graph(1)->addData(hashTable64.size(), time);

    begin = std::chrono::high_resolution_clock::now();
    hashTable128[search_key];
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
               .count();
    if (time > max_time)
    {
        max_time = time;
    }
    plot->graph(2)->addData(hashTable128.size(), time);

    begin = std::chrono::high_resolution_clock::now();
    hashTable2048[search_key];
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
               .count();
    if (time > max_time)
    {
        max_time = time;
    }
    plot->graph(3)->addData(hashTable2048.size(), time);

    plot->rescaleAxes();
    plot->replot();

    for (std::size_t i = 0; i < max_size / (full_time_ms / timeout_ms); i++)
    {
        std::size_t key = rand();
        while (hashTable16.contains(key))
        {
            key = rand();
        }
        hashTable16[key] = "value_" + QString::number(key);
        key = rand();
        while (hashTable64.contains(key))
        {
            key = rand();
        }
        hashTable64[key] = "value_" + QString::number(key);
        key = rand();
        while (hashTable128.contains(key))
        {
            key = rand();
        }
        hashTable128[key] = "value_" + QString::number(key);
        key = rand();
        while (hashTable2048.contains(key))
        {
            key = rand();
        }
        hashTable2048[key] = "value_" + QString::number(key);
    }
    if (hashTable16.size() >= max_size)
    {
        timer->stop();
    }
}