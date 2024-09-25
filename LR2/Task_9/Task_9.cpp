#include <iostream>
#include <cmath>

int main(int argc, char const *argv[])
{
    int mode = 1;
    double z, n, k, m;
    std::cout << "(z n k m): ";
    std::cin >> z >> n >> k >> m;
    std::cout << "1) f(x) = 2x\n2) f(x) = x^3\n3) f(x) = x / 3\nMode: ";
    std::cin >> mode;
    if (z <= 1) z = z * z - 1;
    double x = z, fx = x;
    switch (mode)
    {
    case 1:
        fx *= 2;
        break;
    case 2:
        fx *= x * x;
        break;
    case 3:
        fx /= 3;
        break;
    default:
        break;
    }
    std::cout << "y: " << std::sin((int)(n * fx)) + std::cos(k * x) + std::log(m * x) << std::endl; 
    return 0;
}