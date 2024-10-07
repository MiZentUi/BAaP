#define M_PI 3.14159265359

#include <limits>

namespace std
{
    double sqrt(double x)
    {
        double left = 0, right = x + 1, middle;
        for (int i = 0; i < 100; i++)
        {
            middle = (left + right) / 2;
            middle * middle > x ? right = middle : left = middle;
        }
        return middle;
    }

    long double pow(long double x, int n)
    {
        long double r = 1;
        for (int i = 0; i < n; i++)
            r *= x;
        return r;
    }

    double factorial(double x)
    {
        if (!x || x == 1)
            return 1.0;
        else
            return x * factorial(x - 1);
    }

    long double sin(long double x)
    {
        long double result = 0;
        for (int n = 1; n < 1000; n++)
        {
            long double d = pow(-1, n) * pow(x, 2 * n + 1) / factorial(2 * n + 1);
            if (result + d > __DBL_MAX__) break;
            result += d;
        }
        return result;
    }

    long double cos(long double x)
    {
        long double result = 0;
        for (int n = 1; n < 1000; n++)
        {
            long double d = pow(-1, n) * pow(x, 2 * n) / factorial(2 * n);
            if (result + d > __DBL_MAX__) break;
            result += d;
        }
        return result;
    }

    double acos(double x)
    {
        double r = x;
        for (int i = 1; i <= 1000 * 2; i += 2)
        {
            double f = 1;
            for (int j = i; j + 1 > 0; j -= 2)
                f *= (double)j / (j + 1);
            r += f * pow(x, i + 2) / (i + 2);
        }
        return M_PI / 2 - r;
    }

    long double ln(long double x)
    {
        long double result = 0;
        for (int n = 1; n <= 1000; n++)
        {
            long double d = pow(-1, n - 1) * pow(x - 1, n) / n;
            if (result + d > __DBL_MAX__) break;
            result += d;
        }
        return result;
    }
}