#define M_PI 3.14159265359

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

    double pow(double x, int n)
    {
        double r = 1;
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

    double sin(double x)
    {
        double result = 0;
        for (int n = 0; n < 1000; n++)
            result += pow(-1, n) * pow(x, 2 * n + 1) / factorial(2 * n + 1);
        return result;
    }

    double cos(double x)
    {
        return sqrt(1 - std::pow(sin(x), 2));
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
            result += pow(-1, n - 1) * pow(x - 1, n) / n;
        return result;
    }
}