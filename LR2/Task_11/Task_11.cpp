#include <iostream>

int main(int argc, char const *argv[])
{
    int h1, min1, h2, min2, hr, minr;
    std::cout << "(h1:min1 h2:min2): ";
    scanf("%i:%i %i:%i", &h1, &min1, &h2, &min2);
    if (h2 >= h1) hr = h2 - h1;
    else hr = 24 - h1 + h2;
    if (min2 >= min1) minr = min2 - min1;
    else
    {
        minr = 60 - min1 + min2;
        hr--;
    }
    std::cout << hr << ":" << minr << std::endl;
    return 0;
}
