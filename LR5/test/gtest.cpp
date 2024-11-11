#include <gtest/gtest.h>
#include "tools.h"
#include "LR5_StaticLib1.h"
#include <Windows.h>

HINSTANCE dll = LoadLibrary("LR5_DynamicLib.dll");
typedef bool (*Check)(long double*, long long, long long);
Check check = check = (Check)GetProcAddress(dll, "check");

TEST(Task_1, test_1)
{
    long long n = 1;
    long double** a = new long double* [n];
    long double** b = new long double* [n];
    long double** c = new long double* [n];
    for (long long i = 0; i < n; i++)
    {
        a[i] = new long double[n];
        b[i] = new long double[n]{1};
        c[i] = new long double[n]{1};
    }
    calculate_matrix(a, b, c, n);
    ASSERT_EQ(1, a[0][0]);
    delete[] a;
    a = nullptr;
}

TEST(Task_1, test_2)
{
    long long n = 2;
    long double** a = new long double* [n];
    long double** b = new long double* [n];
    long double** c = new long double* [n];
    for (long long i = 0; i < n; i++)
    {
        a[i] = new long double[n];
        b[i] = new long double[n]{0, 0};
        c[i] = new long double[n]{0, 0};
    }
    calculate_matrix(a, b, c, n);
    bool equal = true;
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < n; j++)
            if (a[i][j])
                equal = false;
    ASSERT_TRUE(equal);
    delete[] a;
    a = nullptr;
}

TEST(Task_1, test_3)
{
    const long long n = 2;
    long double** a = new long double* [n];
    long double** b = new long double* [n];
    long double** c = new long double* [n];
    for (long long i = 0; i < n; i++)
    {
        a[i] = new long double[n];
        b[i] = new long double[n]{i * n + 1.0, i * n + 2.0};
        c[i] = new long double[n]{(long double)(n * n) - i, n * n - i - 1.0};
    }
    calculate_matrix(a, b, c, n);
    long double d[n][n] = {4, 3, 3, 4};
    for (long long i = 0; i < n; i++)
    {
        std::cout << "\t";
        for (long long j = 0; j < n; j++)
            std::cout << a[i][j] << " ";
        std::cout << std::endl;
    }
    bool equal = true;
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < n; j++)
            if (a[i][j] != d[i][j])
                equal = false;
    ASSERT_TRUE(equal);
    delete[] a;
    a = nullptr;
}

TEST(Task_2, test_1)
{
    long long n = 1;
    if (n > 0)
    {
        long double* a = new long double[n]{1};
        ASSERT_FALSE(check(a, 0, n - 1));
        delete[] a;
        a = nullptr;
    }
}

TEST(Task_2, test_2)
{
    long long n = 1;
    if (n > 0)
    {
        long double* a = new long double[n]{0};
        ASSERT_TRUE(check(a, 0, n - 1));
        delete[] a;
        a = nullptr;
    }
}

TEST(Task_2, test_3)
{
    long long n = 3;
    if (n > 0)
    {
        long double* a = new long double[n]{1, 2, 3};
        ASSERT_TRUE(check(a, 0, n - 1));
        delete[] a;
        a = nullptr;
    }
    FreeLibrary(dll);
    dll = nullptr;
}

TEST(Task_3, test_1)
{
    long long n = 0, k = 0, m;
    long long **a = new long long *[n];
    for (long long i = 0; i < n; i++)
        a[i] = new long long[k];
    long long *b = nullptr;
    get_even_array(a, n, k, b, m);
    long long product = get_array_product(b, m);
    for (long long i = 0; i < n; i++)
        delete[] a[i];
    delete[] a, b;
    a = nullptr, b = nullptr;
    ASSERT_EQ(1, product);
}

TEST(Task_3, test_2)
{
    long long n = 1, k = 1, m;
    long long **a = new long long *[n];
    for (long long i = 0; i < n; i++)
        a[i] = new long long[k];
    long long *b = nullptr;
    a[0][0] = 10;
    get_even_array(a, n, k, b, m);
    long long product = get_array_product(b, m);
    ASSERT_EQ(10, b[0]);
    ASSERT_EQ(10, product);
    for (long long i = 0; i < n; i++)
        delete[] a[i];
    delete[] a, b;
    a = nullptr, b = nullptr;
}

TEST(Task_3, test_3)
{
    long long n = 3, k = 3, m;
    long long **a = new long long *[n];
    for (long long i = 0; i < n; i++)
    {
        a[i] = new long long[k];
        for (long long j = 0; j < k; j++)
            a[i][j] = 2;
    }
    long long *b = nullptr;
    get_even_array(a, n, k, b, m);
    long long product = get_array_product(b, m);
    bool equal = true;
    for (long long i = 0; i < m; i++)
        if (b[i] != 2)
            equal = false;
    ASSERT_EQ(3, m);
    ASSERT_TRUE(equal);
    ASSERT_EQ(8, product);
    for (long long i = 0; i < n; i++)
        delete[] a[i];
    delete[] a, b;
    a = nullptr, b = nullptr;
}

TEST(Task_4, test_1)
{
    long long n = 0;
    long double *a = new long double[n];
    long long *zeroes = nullptr;
    long long zeroes_count;
    get_zeroes(a, n, zeroes, zeroes_count);
    long double *b = nullptr;
    b = reverse_array(a, n);
    ASSERT_EQ(0, zeroes_count);
    delete[] a, b, zeroes;
    a = nullptr, b = nullptr, zeroes = nullptr;
}

TEST(Task_4, test_2)
{
    long long n = 1;
    long double *a = new long double[n];
    a[0] = 1;
    long long *zeroes = nullptr;
    long long zeroes_count;
    get_zeroes(a, n, zeroes, zeroes_count);
    long double *b = nullptr;
    b = reverse_array(a, n);
    ASSERT_EQ(0, zeroes_count);
    ASSERT_EQ(1, b[0]);
    delete[] a, b, zeroes;
    a = nullptr, b = nullptr, zeroes = nullptr;
}

TEST(Task_4, test_3)
{
    long long n = 3;
    long double *a = new long double[n]{1, 0, 3};
    long long *zeroes = nullptr;
    long long zeroes_count;
    get_zeroes(a, n, zeroes, zeroes_count);
    long double *b = nullptr;
    b = reverse_array(a, n);
    bool equal = true;
    for (long long i = 0; i < n; i++)
        if (a[i] != b[n - i - 1])
            equal = false;
    ASSERT_EQ(1, zeroes_count);
    ASSERT_TRUE(equal);
    ASSERT_EQ(1, zeroes[0]);
    delete[] a, b, zeroes;
    a = nullptr, b = nullptr, zeroes = nullptr;
}

TEST(Task_5, test_1)
{
    long long n = 1, m = 1, p;
    long long **a = new long long *[n];
    for (long long i = 0; i < n; i++)
        a[i] = new long long[m]{1};
    long long *b = nullptr;
    get_even_odd_array(a, n, m, b, p);
    if (p)
        long long mean = arithmetic_mean(b, p);
    ASSERT_EQ(0, p);
    for (long long i = 0; i < n; i++)
        delete[] a[i];
    delete[] a, b;
    a = nullptr, b = nullptr;
}

TEST(Task_5, test_2)
{
    long long n = 2, m = 2, p;
    long long **a = new long long *[n];
    for (long long i = 0; i < n; i++)
        a[i] = new long long[m]{1, 1};
    long long *b = nullptr;
    get_even_odd_array(a, n, m, b, p);
    long long mean;
    if (p)
        mean = arithmetic_mean(b, p);
    ASSERT_EQ(2, p);
    bool equal = true;
    for (long long i = 0; i < p; i++)
        if (b[i] != 1)
            equal = false;
    ASSERT_TRUE(equal);
    ASSERT_EQ(1, mean);
    for (long long i = 0; i < n; i++)
        delete[] a[i];
    delete[] a, b;
    a = nullptr, b = nullptr;
}

TEST(Task_5, test_3)
{
    long long n = 3, m = 3, p;
    long long **a = new long long *[n];
    for (long long i = 0; i < n; i++)
        a[i] = new long long[m]{i * 3 + 1, i * 3 + 2, i * 3 + 3};
    long long *b = nullptr;
    get_even_odd_array(a, n, m, b, p);
    long long mean;
    if (p)
        mean = arithmetic_mean(b, p);
    ASSERT_EQ(1, p);
    bool equal = true;
    for (long long i = 0; i < p; i++)
        if (b[i] != 5)
            equal = false;
    ASSERT_TRUE(equal);
    ASSERT_EQ(5, mean);
    for (long long i = 0; i < n; i++)
        delete[] a[i];
    delete[] a, b;
    a = nullptr, b = nullptr;
}