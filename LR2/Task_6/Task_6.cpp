#include <iostream>
#include <cmath>

int main(int argc, char const *argv[])
{
    double x, d;
    std::cout << "(x d): ";
    std::cin >> x >> d;
    double b = x + d, a = d * x / b;
    double s = (std::pow(a, 2) + b * std::cos(x)) / (std::pow(d, 3) + (a + d - b));
    std::cout << "S: " << s << std::endl;
    return 0;
}