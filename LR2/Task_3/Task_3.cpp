#include <iostream>

int main(int argc, char const *argv[])
{
    double n = 25, q = 1 / (n - 1), b1;
    std::cout << "b1: ";
    std::cin >> b1;
    std::cout << "S: " << b1 / (1 - q) << std::endl;
    return 0;
}