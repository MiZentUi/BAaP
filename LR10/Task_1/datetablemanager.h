#ifndef DATETABLEMANAGER_H
#define DATETABLEMANAGER_H

#include <QTableWidget>
#include <QVector>
#include <QTableWidgetItem>

#include "date.h"

class DateTableManager
{
public:
    explicit DateTableManager(QTableWidget *table);

    void setDates(QVector<Date> dates, QVector<QString> strings);
    QVector<Date> getDates();
    void setBithDayDate(Date *date);
    void fillTable();
    
    private:
    QTableWidget *table;
    QVector<Date> dates;
    QVector<QString> strings;
    Date *bithdayDate = nullptr;
    
    void fillToday();
};

#endif // DATETABLEMANAGER_H