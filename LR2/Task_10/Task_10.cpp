#include <iostream>

double sqrt(double x)
{
    double s = x;
    while ((s - x / s) > 0.00001) s = (s + x / s) / 2;
    return s;
}

int main(int argc, char const *argv[])
{
    int x1, y1, r1, x2, y2, r2;
    std::cout << "(x1 y1 r1 x2 y2 r2): ";
    std::cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    double d = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    bool console_out = false;
    if (r2 - r1 > d) std::cout << "Yes" << std::endl;
    else if (r1 - r2 == d && !d) std::cout << "Yes, but the opposite is true for the two figures" << std::endl;
    else if (r1 + r2 >= d) std::cout << "Figures intersect" << std::endl;
    else std::cout << "Not a single condition has been met" << std::endl;
    return 0;
}