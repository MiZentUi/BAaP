#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "star.h"
#include "polygon.h"
#include "QDebug"

#include <QInputDialog>
#include <QTimer>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Paint");
    this->setStyleSheet("background-color: #181818;"
                        "color: white;");

    scene = new Scene();

    ui->gridLayoutMenu->setAlignment(Qt::AlignLeft);
    ui->gridLayoutMenu->setAlignment(Qt::AlignTop);

    ui->statusGridLayout->setAlignment(Qt::AlignLeft);
    ui->statusGridLayout->setAlignment(Qt::AlignTop);

    ui->graphicsView->setStyleSheet("background-color: #1f1f1f;"
                                    "border-color: #2b2b2b;"
                                    "border-radius: 10px;");
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->penColorPushButton->setStyleSheet("background-color: #FFA500;");

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::timerSlot);
    timer->start(50);

    statusTimer = new QTimer();
    connect(statusTimer, &QTimer::timeout, this, &MainWindow::updateStatus);
    statusTimer->start(50);

    scene->setPenColor(QColor(QStringLiteral("#FFA500")));
    ui->penWidthPushButton->setText("1.0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    timer->start(50);
    QMainWindow::resizeEvent(event);
}

void MainWindow::timerSlot()
{
    timer->stop();
    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
}

void MainWindow::on_trianglePushButton_clicked()
{
    scene->setFigureType(FigureType::triangle);
    scene->un_select();
}

void MainWindow::on_circlePushButton_clicked()
{
    scene->setFigureType(FigureType::circle);
    scene->un_select();
}

void MainWindow::on_rhombusPushButton_clicked()
{
    scene->setFigureType(FigureType::rhombus);
    scene->un_select();
}

void MainWindow::on_squarePushButton_clicked()
{
    scene->setFigureType(FigureType::square);
    scene->un_select();
}

void MainWindow::on_rectanglePushButton_clicked()
{
    scene->setFigureType(FigureType::rectangle);
    scene->un_select();
}

void MainWindow::on_starPushButton_clicked()
{
    bool ok;
    int pointsCount = QInputDialog::getInt(this, "", "Points count", Star::getPointsCount(), 2, 10000, 1, &ok);
    if (ok)
    {
        Star::setPointsCount(pointsCount);
        scene->setFigureType(FigureType::star);
    }
    scene->un_select();
}

void MainWindow::on_polygonPushButton_clicked()
{
    bool ok;
    int pointsCount = QInputDialog::getInt(this, "", "Points count", Polygon::getPointsCount(), 2, 10000, 1, &ok);
    if (ok)
    {
        Polygon::setPointsCount(pointsCount);
        scene->setFigureType(FigureType::polygon);
    }
    scene->un_select();
}

void MainWindow::on_trapezoidPushButton_clicked()
{
    scene->setFigureType(FigureType::trapezoid);
    scene->un_select();
}

void MainWindow::on_penColorPushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    ui->penColorPushButton->setStyleSheet("background-color: " + color.name() + ";");
    scene->setPenColor(color);
    scene->un_select();
}

void MainWindow::on_brushColorPushButton_clicked()
{
    QColorDialog colorDialog;
    colorDialog.setCustomColor(0, QColor(QStringLiteral("#1f1f1f")));
    QColor color = colorDialog.getColor(Qt::white, this);
    ui->brushColorPushButton->setStyleSheet("background-color: " + color.name() + ";");
    scene->setBrushColor(color);
    scene->un_select();
}

void MainWindow::on_penWidthPushButton_clicked()
{
    bool ok;
    qreal penWidth = QInputDialog::getDouble(this, "", "Pen width", scene->getPenWidth(), 0.1, 999, 1, &ok);
    if (ok)
    {
        ui->penWidthPushButton->setText(QString::number(penWidth));
        scene->setPenWidth(penWidth);
    }
    scene->un_select();
}

void MainWindow::on_erasePushButton_clicked()
{
    scene->removeAllItems();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Delete)
        scene->deleteSelectedFigure();
    if (event->key() == Qt::Key_Escape)
        scene->un_select();
    if (event->key() == Qt::Key_C)
        scene->removeAllItems();
}

void MainWindow::updateStatus()
{
    statusTimer->start(50);
    bool perimeter_ok;
    qreal perimeter = scene->getSelectedFigurePerimeter(perimeter_ok);
    if (perimeter_ok)
        ui->perimterLabel->setText(QString::number(perimeter));
    else
        ui->perimterLabel->setText("Perimeter");
    bool square_ok;
    qreal square = scene->getSelectedFigureSquare(square_ok);
    if (square_ok)
        ui->squareLabel->setText(QString::number(square));
    else
        ui->squareLabel->setText("Square");
}
