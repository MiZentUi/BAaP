#include <iostream>

long long pow(long long x, long long n) 
{
    long long r = 1;
    for (long long i = 0; i < n; i++) r *= x;
    return r;
}

bool check_num(long long n)
{
    long long sum = 0, count = 0, temp = n;
    while (temp > 0)
    {
        count++;
        temp /= 10;
    }
    temp = n;
    while (temp > 0)
    {
        sum += pow(temp % 10, count);
        temp /= 10; 
    }
    if (sum == n) return true;
    else return false;
}

int main(int argc, char const *argv[])
{
    long long n;
    std::cin >> n;
    for (long long i = 1; i < n; i++) if (check_num(i)) std::cout << i << std::endl;
    return 0;
}