#include "trainroute.h"

TrainRoute::TrainRoute() {}

TrainRoute::TrainRoute(std::string date, std::string time, std::string route, 
    std::string destination, std::string seats, std::string freeSeats)
    : date(date), time(time), route(route), destination(destination), 
    seats(seats), freeSeats(freeSeats) {}

std::string TrainRoute::getSearchString()
{
    return date + time + route + destination + seats + freeSeats;
}

std::string TrainRoute::getSortString()
{
    std::string result;
    try
    {
        QStringList dateList = QString::fromStdString(date).split(".");
        for (int i = 0; i < dateList.size(); i++)
            result += dateList.at(dateList.size() - i - 1).toStdString();
    }
    catch(const std::exception& e) {}
    return result + time + route + destination + seats + freeSeats;
}

std::string &TrainRoute::operator[](unsigned int index)
{
    switch (index)
    {
    case 0:
        return date;
    case 1:
        return time;
    case 2:
        return route;
    case 3:
        return destination;
    case 4:
        return seats;
    case 5:
        return freeSeats;
    default:
        throw std::out_of_range("TrainRoute: Index out of range: " + std::to_string(index));
        break;
    }
}

std::string &TrainRoute::operator[](std::string field)
{
    if (field == "date")
        return date;
    if (field == "time")
        return time;
    if (field == "route")
        return route;
    if (field == "destination")
        return destination;
    if (field == "seats")
    return seats;
    if (field == "free_seats")
    return freeSeats;
    else
    throw std::out_of_range("TrainRoute: Field out of range: " + field);
}