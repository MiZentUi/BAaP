void get_even_array(long long **a, long long n, long long k, long long *&b, long long &m)
{
    long long even_count = 0;
    for (long long i = 0; i < n && i < k; i++)
        if (!(a[i][i] % 2))
        {
            even_count++;
        }
    b = new long long[even_count];
    m = even_count;
    for (long long i = 0, j = 0; i < n && i < k && j < even_count; i++)
        if (!(a[i][i] % 2))
        {
            b[j] = a[i][i];
            j++;
        }
}

long long get_array_product(long long *&a, long long n)
{
    long double product = 1;
    for (long long i = 0; i < n; i++)
        product *= a[i];
    return product;
}

void get_zeroes(long double *&a, long long n, long long *&b, long long &m)
{
    long long zeroes_count = 0;
    for (long long i = 0; i < n; i++)
        if (!a[i])
            zeroes_count++;
    b = new long long[zeroes_count];
    m = zeroes_count;
    for (long long i = 0, j = 0; i < n && j < zeroes_count; i++)
        if (!a[i])
        {
            b[j] = i;
            j++;
        }
}

long double * reverse_array(long double *a, long long n)
{
    long double *b = new long double[n];
    for (int i = 0; i < n; i++)
        b[i] = a[n - i - 1];
    return b;
}

void get_even_odd_array(long long **a, long long n, long long m, long long *&b, long long &p)
{
    p = 0;
    for (long long i = 0; i < n; i++)
        for (long long j = 1; j < m; j += 2)
            if (a[i][j] % 2)
                p++;
    b = new long long[p];
    for (long long i = 0, i_b = 0; i < n; i++)
        for (long long j = 1; j < m; j += 2)
            if (a[i][j] % 2)
            {
                b[i_b] = a[i][j];
                i_b++;
            }
}

long double arithmetic_mean(long long *a, long long n)
{
    long double sum = 0;
    for (long long i = 0; i < n; i++)
        sum += a[i];
    return sum / n;
}