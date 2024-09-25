#include <iostream>

void cout_max(double &max) { std::cout << "Max: " << max << std::endl; }

int main(int argc, char const *argv[])
{
    double x, y;
    std::cout << "(x y): ";
    std::cin >> x >> y;
    bool condition = x > y;
    condition ? cout_max(x) : cout_max(y);
    return 0;
}