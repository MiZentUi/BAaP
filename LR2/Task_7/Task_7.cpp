#include <iostream>

int main(int argc, char const *argv[])
{
    int n;
    double a, b, c, y;
    std::cout << "(a b c N): ";
    std::cin >> a >> b >> c >> n;
    switch (n)
    {
    case 2:
        y = b * c - a * a;
        break;
    case 56:
        y = b * c;
        break;
    case 7:
        y = a * a + c;
        break;
    case 3:
        y = a - b * c;
        break;
    default:
        y = 1;
        for (int i = 0; i < 3; i++) y *= (a + b);
        break;
    }
    std::cout << "Y: " << y << std::endl;
    return 0;
}