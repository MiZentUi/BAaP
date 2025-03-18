#ifndef DATE_H
#define DATE_H

#include <QString>
#include <QStringList>

class Date
{
public:
    explicit Date(int year, int month, int day);
    explicit Date(QString dateString);
    explicit Date();
    Date nextDay() const;
    Date previousDay() const;
    bool isLeap() const;
    int duration(Date date) const;
    short dayOfWeek();
    short weekNumber() const;
    int daysTillYourBithday(Date bithdayDate) const;
    bool isValid() const;
    void fromString(QString dateString);
    QString toString() const;

private:
    int year;
    int month;
    int day;
    bool valid;

    int dateToJDN() const;
};

#endif // DATE_H