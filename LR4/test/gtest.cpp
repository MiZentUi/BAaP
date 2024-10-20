#include <gtest/gtest.h>
#include "tools.h"

TEST(Task_1, test_1)
{
    long long n = 10;
    long double a[n] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(5, get_larger_count(a, n));
}

TEST(Task_1, test_2)
{
    long long n = 5;
    long double a[n] = {1, 2, 3, 4, 5};
    ASSERT_EQ(2, get_larger_count(a, n));
}

TEST(Task_1, test_3)
{
    long long n = 10;
    long double a[n] = {2.2, 4.3, 5.8, 11.3, -2.4, 0, 75.1, -30, 0.01, 1};
    ASSERT_EQ(2, get_larger_count(a, n));
}

TEST(Task_2, test_1)
{
    long long n = 1, m = 1;
    long double a[n][m] = {{1}};
    ASSERT_EQ(1, get_even_rows_sum(*a, n, m));
}

TEST(Task_2, test_2)
{
    long long n = 2, m = 2;
    long double a[n][m] = {{1, 2}, {3, 4}};
    ASSERT_EQ(3, get_even_rows_sum(*a, n, m));
}

TEST(Task_2, test_3)
{
    long long n = 3, m = 3;
    long double a[n][m] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    ASSERT_EQ(30, get_even_rows_sum(*a, n, m));
}

TEST(Task_3, test_1)
{
    long long n = 1;
    long double **a = new long double *[n];
    for (long long i = 0; i < n; i++)
        a[i] = new long double[n]{i + 1.0};
    long double result[2];
    get_shaded_matrix_values(a, n, result);
    ASSERT_EQ(1, result[0]);
    ASSERT_EQ(1, result[1]);
}

TEST(Task_3, test_2)
{
    long long n = 3;
    long double **a = new long double *[n];
    for (long long i = 0; i < n; i++)
        a[i] = new long double[n]{i * n + 1.0, i * n + 2.0, i * n + 3.0};
    long double result[2];
    get_shaded_matrix_values(a, n, result);
    std::cout << result[0] << " " << result[1] << std::endl;
    ASSERT_EQ(35, result[0]);
    ASSERT_EQ(15120, result[1]);
}

TEST(Task_3, test_3)
{
    long long n = 5;
    long double **a = new long double *[n];
    for (long long i = 0; i < n; i++)
        a[i] = new long double[n]{i * n + 1.0, i * n + 2.0, i * n + 3.0, i * n + 4.0, i * n + 5.0};
    long double result[2];
    get_shaded_matrix_values(a, n, result);
    ASSERT_EQ(221, result[0]);
    ASSERT_EQ(1.0 * 2 * 3 * 4 * 5 * 7 * 8 * 9 * 13 * 17 * 18 * 19 * 21 * 22 * 23 * 24 * 25, result[1]);
}

TEST(Task_4, test_1)
{
    long long n = 1;
    long double ***a = (long double ***)malloc(n * sizeof(long double **));
    for (long long i = 0; i < n; i++)
    {
        a[i] = (long double **)malloc(n * sizeof(long double *));
        for (long long j = 0; j < n; j++)
        {
            a[i][j] = (long double *)malloc(n * sizeof(long double));
            for (long long k = 0; k < n; k++)
                a[i][j][k] = i * n * n + j * n + k + 1;
        }
    }
    ASSERT_EQ(1, get_max_diagonal(a, n));
}

TEST(Task_4, test_2)
{
    long long n = 2;
    long double ***a = (long double ***)malloc(n * sizeof(long double **));
    for (long long i = 0; i < n; i++)
    {
        a[i] = (long double **)malloc(n * sizeof(long double *));
        for (long long j = 0; j < n; j++)
        {
            a[i][j] = (long double *)malloc(n * sizeof(long double));
            for (long long k = 0; k < n; k++)
                a[i][j][k] = i * n * n + j * n + k + 1;
        }
    }
    ASSERT_EQ(9, get_max_diagonal(a, n));
}

TEST(Task_4, test_3)
{
    long long n = 3;
    long double ***a = (long double ***)malloc(n * sizeof(long double **));
    for (long long i = 0; i < n; i++)
    {
        a[i] = (long double **)malloc(n * sizeof(long double *));
        for (long long j = 0; j < n; j++)
        {
            a[i][j] = (long double *)malloc(n * sizeof(long double));
            for (long long k = 0; k < n; k++)
                a[i][j][k] = i * n * n + j * n + k + 1;
        }
    }
    ASSERT_EQ(42, get_max_diagonal(a, n));
}

TEST(Task_5, test_1)
{
    long long n = 3, m = 3;
    char **a = (char **)malloc(n * sizeof(char *));
    for (long long i = 0; i < n; i++)
        a[i] = (char *)malloc(m * sizeof(char));
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < n; j++)
            a[i][j] = '.';
    minesweeper(a, n, m);
    char b[n][m] = {
        {'.', '.', '.'}, 
        {'.', '.', '.'}, 
        {'.', '.', '.'}
    };
    bool equal = true;
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < m; j++)
            if (a[i][j] != b[i][j])
                equal = false;
    ASSERT_TRUE(equal);
}

TEST(Task_5, test_2)
{
    long long n = 3, m = 3;
    char **a = (char **)malloc(n * sizeof(char *));
    for (long long i = 0; i < n; i++)
        a[i] = (char *)malloc(m * sizeof(char));
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < n; j++)
        {
            if (i == j)
                a[i][j] = '*';
            else
                a[i][j] = '.';
        }
    minesweeper(a, n, m);
    char b[n][m] = {
        {'*', '2', '1'}, 
        {'2', '*', '2'}, 
        {'1', '2', '*'}
    };
    bool equal = true;
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < m; j++)
            if (a[i][j] != b[i][j])
                equal = false;
    ASSERT_TRUE(equal);
}

TEST(Task_5, test_3)
{
    long long n = 5, m = 5;
    char **a = (char **)malloc(n * sizeof(char *));
    for (long long i = 0; i < n; i++)
        a[i] = (char *)malloc(m * sizeof(char));
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < n; j++)
        {
            if (i == j)
                a[i][j] = '*';
            else
                a[i][j] = '.';
        }
    minesweeper(a, n, m);
    char b[n][m] = {
        {'*', '2', '1', '.', '.'},
        {'2', '*', '2', '1', '.'},
        {'1', '2', '*', '2', '1'},
        {'.', '1', '2', '*', '2'},
        {'.', '.', '1', '2', '*'}
    };
    bool equal = true;
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < m; j++)
            if (a[i][j] != b[i][j])
                equal = false;
    ASSERT_TRUE(equal);
}

TEST(Task_6, test_1)
{
    unsigned i, j, n = 1;
    unsigned **a = (unsigned **)malloc(n * sizeof(unsigned *));
    for (i = 0; i < n; i++)
        a[i] = (unsigned *)malloc(n * sizeof(unsigned));
    get_magical_square(a, n);
    unsigned b[n][n] = {{1}};
    bool equal = true;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (a[i][j] != b[i][j])
                equal = false;
    ASSERT_TRUE(equal);
}

TEST(Task_6, test_2)
{
    unsigned i, j, n = 2;
    unsigned **a = (unsigned **)malloc(n * sizeof(unsigned *));
    for (i = 0; i < n; i++)
        a[i] = (unsigned *)malloc(n * sizeof(unsigned));
    ASSERT_FALSE(get_magical_square(a, n));
}

TEST(Task_6, test_3)
{
    unsigned i, j, n = 3;
    unsigned **a = (unsigned **)malloc(n * sizeof(unsigned *));
    for (i = 0; i < n; i++)
        a[i] = (unsigned *)malloc(n * sizeof(unsigned));
    get_magical_square(a, n);
    unsigned b[n][n] = {
        {2, 7, 6},
        {9, 5, 1},
        {4, 3, 8}
    };
    bool equal = true;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (a[i][j] != b[i][j])
                equal = false;
    ASSERT_TRUE(equal);
}