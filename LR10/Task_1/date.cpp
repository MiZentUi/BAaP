#include "date.h"

#include <cmath>
#include <stdexcept>
#include <string>
#include <format>

Date::Date(int year, int month, int day)
{
    (year >= 0 && year < 10000) ? this->year = year : throw std::invalid_argument("Invalid year: " + std::to_string(year));
    (1 <= month && month <= 12) ? this->month = month : throw std::invalid_argument("Invalid month: " + std::to_string(month));
    (0 < day && day <= 31) ? this->day = day : throw std::invalid_argument("Invalid day: " + std::to_string(day));
    switch (month)
    {
        case 4: case 6: case 9: case 11:    
            (0 < day && day <= 30) ? this->day = day : throw std::invalid_argument("Invalid day of month: \n\tmonth: " + std::to_string(month) + "\n\tday: " + std::to_string(day));
            break;
        case 2:
            if (isLeap())
                 (0 < day && day <= 29) ? this->day = day : throw std::invalid_argument("Invalid day of month: \n\tmonth: " + std::to_string(month) + "\n\tday: " + std::to_string(day));
            else
                (0 < day && day <= 28) ? this->day = day : throw std::invalid_argument("Invalid day of month: \n\tmonth: " + std::to_string(month) + "\n\tday: " + std::to_string(day));
            break;
        default:
            (0 < day && day <= 31) ? this->day = day : throw std::invalid_argument("Invalid day of month: \n\tmonth: " + std::to_string(month) + "\n\tday: " + std::to_string(day));
            break;
    }
    valid = true;
}

Date::Date(QString dateString)
{
    fromString(dateString);
    valid = true;
}

Date::Date()
{
    valid = false;
}

bool Date::isValid() const
{
    return valid;
}

Date Date::nextDay() const
{
    int next_year = year, next_month = month, next_day = day;
    switch (next_month)
    {
    case 4: case 6: case 9: case 11:    
        if (day == 30)
        {
            next_day = 1;
            next_month++;
        }
        else
            next_day++;
        break;
    case 2:
        if (isLeap())
        {
            if (day == 29)
            {
                next_day = 1;
                next_month++;
            }
            else
                next_day++;
        }
        else
        {
            if (day == 28)
            {
                next_day = 1;
                next_month++;
            }
            else
                next_day++;
        }
        break;
    default:
        if (day == 31)
        {
            next_day = 1;
            next_month++;
        }
        else
            next_day++;
        break;
    }
    if (next_month > 12)
    {
        next_month = 1;
        next_year++;
    }
    return Date(next_year, next_month, next_day);
}

Date Date::previousDay() const
{
    int previous_year = year, previous_month = month, previous_day = day;
    if (previous_day == 1)
    {
        switch (month)
        {
        case 5: case 7: case 10: case 12:    
            previous_day = 30;
            break;
        case 3:
            if (isLeap())
                previous_day = 29;
            else
                previous_day = 28;
            break;
        default:
            previous_day = 31;
            break;
        }
        previous_month--;
        if (previous_month <= 0)
        {
            previous_month = 12;
            previous_year--;
        }
    }
    else
        previous_day--;
    return Date(previous_year, previous_month, previous_day);
}

bool Date::isLeap() const
{
    if (!(year % 4))
    {
        if (!(year % 100))
        {
            if (!(year % 400))
                return true;
        }
        else
            return true;
    }
    return false;
}

short Date::dayOfWeek()
{
    return dateToJDN() % 7;
}

int Date::dateToJDN() const
{
    return (1461 * (year + 4800 + (month - 14) / 12)) / 4 + (367 * (month - 2 - (12 * ((month - 14) / 12)))) / 12 - (3 * ((year + 4900 + (month - 14) / 12) / 100)) / 4 + day - 32075; 
}

short Date::weekNumber() const
{
    return (duration(Date(year, 1, 1)) + Date(year, 1, 1).dayOfWeek()) / 7 + 1;
}

int Date::duration(Date date) const
{
    return std::abs(date.dateToJDN() - dateToJDN());
}

int Date::daysTillYourBithday(Date bithdayDate) const
{
    int nextBirthDayYear = year;
    if (Date(year, bithdayDate.month, bithdayDate.day).dateToJDN() < dateToJDN())
        nextBirthDayYear++;
    return Date(nextBirthDayYear, bithdayDate.month, bithdayDate.day).dateToJDN() - dateToJDN();
}

void Date::fromString(QString dateString)
{
    int current_year, current_month, current_day;
    try
    {
        QStringList dateData = dateString.split(".");
        if (dateData.size() == 3)
        {
            current_day = dateData.at(0).toInt();
            current_month = dateData.at(1).toInt();
            current_year = dateData.at(2).toInt();
            (current_year >= 0 && current_year < 10000) ? this->year = current_year : throw std::invalid_argument("Invalid year: " + std::to_string(current_year));
            (1 <= current_month && current_month <= 12) ? this->month = current_month : throw std::invalid_argument("Invalid month: " + std::to_string(current_month));
            (0 < current_day && current_day <= 31) ? this->day = current_day : throw std::invalid_argument("Invalid day: " + std::to_string(current_day));
            switch (current_month)
            {
                case 4: case 6: case 9: case 11:    
                    (0 < current_day && current_day <= 30) ? this->day = current_day : throw std::invalid_argument("Invalid day of month: \n\tmonth: " + std::to_string(current_month) + "\n\tday: " + std::to_string(current_day));
                    break;
                case 2:
                    if (isLeap())
                        (0 < current_day && current_day <= 29) ? this->day = current_day : throw std::invalid_argument("Invalid day of month: \n\tmonth: " + std::to_string(current_month) + "\n\tday: " + std::to_string(current_day));
                    else
                        (0 < current_day && current_day <= 28) ? this->day = current_day : throw std::invalid_argument("Invalid day of month: \n\tmonth: " + std::to_string(current_month) + "\n\tday: " + std::to_string(current_day));
                    break;
                default:
                    (0 < current_day && current_day <= 31) ? this->day = current_day : throw std::invalid_argument("Invalid day of month: \n\tmonth: " + std::to_string(current_month) + "\n\tday: " + std::to_string(current_day));
                    break;
            }
        }
        else
            throw std::invalid_argument("Invalid string: " + dateString.toStdString());
    }
    catch(const std::exception& e)
    {
        throw std::invalid_argument("Invalid string: " + dateString.toStdString());
    }
}

QString Date::toString() const
{
    return QString::fromStdString(std::format("{:02d}.{:02d}.{:04d}", day, month, year));
}