#define M_PI 3.14159265359

namespace std
{
    double sqrt(double x)
    {
        double s = x;
        while ((s - x / s) > 0.00001) s = (s + x / s) / 2;
        return s;
    }

    double pow(double x, int n) 
    {
        double r = 1;
        for (int i = 0; i < n; i++) r *= x;
        return r;
    }

    double acos(double x)
    {
        double r = x;
        for (int i = 1; i <= 1000 * 2; i += 2)
        {
            double f = 1;
            for (int j = i; j + 1 > 0; j -= 2) f *= (double)j / (j + 1);
            r += f * pow(x, i + 2) / (i + 2);
        }
        return M_PI / 2 - r;
    }
}