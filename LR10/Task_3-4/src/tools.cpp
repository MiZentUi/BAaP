#include "tools.h"

bool check_equals(const Expression *first, const Expression *second)
{
    return (*((size_t *)first) == *((size_t *)second));
}