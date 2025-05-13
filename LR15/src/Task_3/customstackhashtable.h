#ifndef CUSTOMSTACKHASHTABLE_H
#define CUSTOMSTACKHASHTABLE_H

#include <QString>
#include <utility>

#include "stackhashtable.h"

class CustomStackHashTable : public StackHashTable<long long, QString>
{
public:
    using StackHashTable<long long, QString>::operator[];

    CustomStackHashTable();

    void randomFill(std::size_t count);
    std::pair<long long, QString> getPairByMaxKey();
    QString toQString();
};

#endif  // CUSTOMSTACKHASHTABLE_H
