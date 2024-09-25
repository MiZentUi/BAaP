#include <iostream>

int main(int argc, char const *argv[])
{
    long double x, y, z;
    std::cout << "(x y z)   : ";
    std::cin >> x >> y >> z;
    x + y > z ? x + z > y ? y + z > z ? std::cout << "YES\n" : std::cout << "NO\n" : std::cout << "NO\n" : std::cout << "NO\n";
    return 0;
}