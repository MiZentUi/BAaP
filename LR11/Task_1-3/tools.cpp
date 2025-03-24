#include "tools.h"

#include <cmath>
#include <string>

std::string dec_to_bin(long double n)
{
    long double int_ = 0;
    const long double frac = std::modf(std::abs(n), &int_);
    const std::string bin_i = int_to_bin(std::floor(int_));
    const std::string bin_f = frac_to_bin(frac * 2);
    return (n < 0 ? "-" : "") +
           (bin_i.empty() && !bin_f.empty() ? "0" : bin_i) +
           (bin_f.empty() ? "" : '.' + bin_f);
}

std::string int_to_bin(long double n)
{
    if (n < 1)
        return "";
    return int_to_bin(std::floor(n / 2)) +
           (std::fabs(std::fmod(n, 2)) > 0.001 ? '1' : '0');
}

std::string frac_to_bin(long double n, int iter)
{
    if (std::fabs(n) < 0.001 || iter > 20)
        return "";
    return (n >= 1 ? "1" : "0") +
           frac_to_bin((n >= 1 ? n - 1 : n) * 2, iter + 1);
}

long long ackermann(long long first, long long second, int iter)
{
    if (first == 0 || iter > 50)
        return second + 1;
    if (first > 0 && second == 0)
        return ackermann(first - 1, 1, iter + 1);
    if (first > 0 && second > 0)
        return ackermann(first - 1, ackermann(first, second - 1, iter + 1),
                         iter + 1);
    return 0;
}

long long reverse(long long n, int iter)
{
    if (n < 10)
        return ((iter * 10L) + n);
    return reverse(n / 10, (10 * iter) + (int)(n % 10));
}