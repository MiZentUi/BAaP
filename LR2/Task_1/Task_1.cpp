#include <iostream>

int main(int argc, char const *argv[])
{
    int x;
    std::cout << "x: ";
    std::cin >> x;
    int x2 = x * x;
    int v1 = x * (23 * x + 32);
    int v2 = 69 * x2 + 8;
    std::cout << v1 + v2 << std::endl << v2 - v1 << std::endl;
    return 0;
}