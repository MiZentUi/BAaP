#include ".h"

extern "C" __declspec(dllexport) bool check(long double* a, long long i, long long n)
{
    if (n == i)
    {
        return a[i] <= i * i;
    }
    else
    {
        int mid = i + (n - i) / 2;
        return check(a, i, mid) || check(a, mid + 1, n);
    }
}