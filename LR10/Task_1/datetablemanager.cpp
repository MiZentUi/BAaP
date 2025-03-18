#include "datetablemanager.h"

#include <QDate>
#include <QApplication>

DateTableManager::DateTableManager(QTableWidget *table)
{
    this->table = table;
}

void DateTableManager::setDates(QVector<Date> dates, QVector<QString> strings)
{
    this->dates = dates;
    this->strings = strings;
}

QVector<Date> DateTableManager::getDates()
{
    return dates;
}

void DateTableManager::setBithDayDate(Date *date)
{
    bithdayDate = date;
}

void DateTableManager::fillToday()
{
    QDate currentDate = QDate::currentDate();
    Date today(currentDate.year(), currentDate.month(), currentDate.day());
    if (table->rowCount() < 2)
        table->setRowCount(2);
    QFont boldFont = QApplication::font();
    boldFont.setBold(true);
    table->setItem(0, 0, new QTableWidgetItem(today.toString()));
    table->setItem(0, 1, new QTableWidgetItem(today.nextDay().toString()));
    table->setItem(0, 2, new QTableWidgetItem(today.previousDay().toString()));
    if (today.isLeap())
        table->setItem(0, 3, new QTableWidgetItem("True"));
    else
        table->setItem(0, 3, new QTableWidgetItem(""));
    table->setItem(0, 4, new QTableWidgetItem(QString::number(today.weekNumber())));
    try
    {
        if (bithdayDate != nullptr)
            table->setItem(0, 5, new QTableWidgetItem(QString::number(today.daysTillYourBithday(*bithdayDate))));
        else
            table->setItem(0, 5, new QTableWidgetItem(""));
    }
    catch(const std::exception& e) 
    {
        table->setItem(0, 5, new QTableWidgetItem(""));
    }
    table->setItem(0, 6, new QTableWidgetItem(""));
    for (int i = 0; i < table->columnCount(); i++)
    {
        table->item(0, i)->setFont(boldFont);
        table->item(0, i)->setFlags(table->item(0, i)->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
    }
}

void DateTableManager::fillTable()
{
    table->setRowCount(dates.size() + 2);
    fillToday();
    for (int i = 0; i < dates.size(); i++)
    {
        if (dates.at(i).isValid())
        {
            table->setItem(i + 1, 0, new QTableWidgetItem(dates.at(i).toString()));
            table->setItem(i + 1, 1, new QTableWidgetItem(dates.at(i).nextDay().toString()));
            table->setItem(i + 1, 2, new QTableWidgetItem(dates.at(i).previousDay().toString()));
            if (dates.at(i).isLeap())
                table->setItem(i + 1, 3, new QTableWidgetItem("True"));
            else
                table->setItem(i + 1, 3, new QTableWidgetItem(""));
            table->setItem(i + 1, 4, new QTableWidgetItem(QString::number(dates.at(i).weekNumber())));
            try
            {
                if (bithdayDate != nullptr)
                    table->setItem(i + 1, 5, new QTableWidgetItem(QString::number(dates.at(i).daysTillYourBithday(*bithdayDate))));
                else
                    table->setItem(i + 1, 5, new QTableWidgetItem(""));
            }
            catch(const std::exception& e) 
            {
                table->setItem(i + 1, 5, new QTableWidgetItem(""));
            }
            if (i == dates.size() - 1)
            {
                if (dates.at(0).isValid())
                    table->setItem(i + 1, 6, new QTableWidgetItem(QString::number(dates.at(i).duration(dates.at(0)))));
                else
                    table->setItem(i + 1, 6, new QTableWidgetItem(""));
            }
            else
            {
                if (dates.at(i + 1).isValid())
                    table->setItem(i + 1, 6, new QTableWidgetItem(QString::number(dates.at(i).duration(dates.at(i + 1)))));
                else
                    table->setItem(i + 1, 6, new QTableWidgetItem(""));
            }
            for (int j = 1; j < table->columnCount(); j++)
                table->item(i + 1, j)->setFlags(table->item(i + 1, j)->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
        }
        else
        {
            table->setItem(i + 1, 0, new QTableWidgetItem(strings.at(i)));
            for (int j = 1; j < table->columnCount(); j++)
            {
                table->setItem(i + 1, j, new QTableWidgetItem(""));
                table->item(i + 1, j)->setFlags(table->item(i + 1, j)->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
            }
        }
    }
}