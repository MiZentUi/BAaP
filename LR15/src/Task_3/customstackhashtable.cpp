#include "customstackhashtable.h"

#include <qchar.h>

CustomStackHashTable::CustomStackHashTable()
    : StackHashTable<long long, QString>()
{}

void CustomStackHashTable::randomFill(std::size_t count)
{
    srand(time(0));
    for (std::size_t i = 0; i < count; i++)
    {
        (*this)[rand()] = "value_" + QString::number(i);
    }
}

std::pair<long long, QString> CustomStackHashTable::getPairByMaxKey()
{
    if (!empty())
    {
        std::pair<long long, QString> maxPair = {INT64_MIN, ""};
        for (std::size_t i = 0; i < 8; i++)
        {
            for (std::pair<long long, QString> &pair : _stacks[i])
            {
                if (pair.first >= maxPair.first)
                {
                    maxPair = pair;
                }
            }
        }
        return maxPair;
    }
    return {0, ""};
}

QString CustomStackHashTable::toQString()
{
    QString result;
    for (std::size_t i = 0; i < 8; i++)
    {
        result += '[' + QString::number(i) + "]: ";
        for (std::pair<long long, QString> &pair : _stacks[i])
        {
            result +=
                '{' + QString::number(pair.first) + ", " + pair.second + "} ";
        }
        result += '\n';
    }
    return result;
}