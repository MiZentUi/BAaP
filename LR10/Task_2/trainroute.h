#ifndef TRAINROUTE_H
#define TRAINROUTE_H

#include <string>
#include <stdexcept>

#include <QString>
#include <QStringList>

class TrainRoute
{
private:
    std::string date;
    std::string time;
    std::string route;
    std::string destination;
    std::string seats;
    std::string freeSeats;

public:
    TrainRoute();
    TrainRoute(std::string date, std::string time, std::string route, 
               std::string destination, std::string seats, std::string freeSeats);

    static const int FIELDS_COUNT = 6;

    std::string getSearchString();
    std::string getSortString();

    std::string &operator[](unsigned int index);
    std::string &operator[](std::string string);
};

#endif // TRAINROUTE_H