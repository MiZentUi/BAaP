#ifndef TOOLS_H
#define TOOLS_H

#include <cmath>
#include <string>

extern std::string dec_to_bin(long double n);
extern std::string int_to_bin(long double n);
extern std::string frac_to_bin(long double n, int iter = 0);

extern long long ackermann(long long first, long long second, int i = 0);

extern long long reverse(long long n, int iter = 0);

#endif  // TOOLS_H