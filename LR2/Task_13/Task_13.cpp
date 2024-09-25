#include <iostream>

int main(int argc, char const *argv[])
{
    int a, b;
    std::cout << "\t   a: " << a << "\t" << "b: " << b << std::endl;
    std::cout << "    (a b): ";
    std::cin >> a >> b;
    std::cout << "\t   a: " << a << "\t" << "b: " << b << std::endl;
    for (int i = 0; a && b; i++)
    {
        if (a > b) a %= b;
        else b %= a;
        std::cout << "\t" << i << ") " << "a: " << a << "   \t" << "b: " << b << std::endl;
    }
    std::cout << "\t   gcf: " << a + b << std::endl;
    return 0;
}