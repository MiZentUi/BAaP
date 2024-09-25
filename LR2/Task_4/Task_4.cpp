#include <iostream>

int main(int argc, char const *argv[])
{
    long long int x, y, k;
    double a, b, c, max;
    std::cout << "(x y a b c k): ";
    std::cin >> x >> y >> a >> b >> c >> k;
    if (x == y) { x = 0; y = 0; }
    else x > y ? y = 0 : x = 0;
    a > b ? (a > c ? max = a : max = c) : (b > c ? max = b : max = c);
    if (a == max) a -= k;
    if (b == max) b -= k;
    if (c == max) c -= k;
    std::cout << "(x y): " << x << " " << y << std::endl << "(a b c): " << a << " " << b << " " << c << std::endl; 
    return 0;
}