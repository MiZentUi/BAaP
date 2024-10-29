long long get_larger_count(long double *a, long long size)
{
    long double sum = 0, count = 0;
    for (long long i = 0; i < size; i++)
        sum += a[i];
    long long middle = sum / size;
    for (long long i = 0; i < size; i++)
        if (a[i] > middle)
            count++;
    return count;
}

long double get_even_rows_sum(long double *a, long long n, long long m)
{
    long double sum = 0;
    for (long long i = 0; i < n; i += 2)
        for (long long j = 0; j < m; j++)
            sum += a[i * m + j];
    return sum;
}

void get_shaded_matrix_values(long double **a, long long n, long double *r)
{
    long double sum = 0, product = 1;
    for (long long i = 0; i < n; i++)
    {
        if (n / 2 > i)
            for (long long j = i; j < n - i; j++)
            {
                sum += a[i][j];
                product *= a[i][j];
            }
        else
            for (long long j = n - i - 1; j < i + 1; j++)
            {
                sum += a[i][j];
                product *= a[i][j];
            }
    }
    r[0] = sum;
    r[1] = product;
}

long double get_max_diagonal(long double ***a, long long n)
{
    long double max_diagonal, sums[4] = {};
    for (long long i = 0; i < n; i++)
    {
        sums[0] += a[i][i][i];
        sums[1] += a[n - i - 1][i][i];
        sums[2] += a[i][n - i - 1][i];
        sums[3] += a[i][i][n - i - 1];
    }
    max_diagonal = sums[0];
    for (int i = 1; i < 4; i++)
        if (sums[i] > max_diagonal)
            max_diagonal = sums[i];
    return max_diagonal;
}

void minesweeper(char **a, long long n, long long m)
{
    for (long long i = 0; i < n; i++)
    {
        for (long long j = 0; j < m; j++)
        {
            if (a[i][j] == '.')
            {
                int count = 0;
                if (i > 0 && a[i - 1][j] == '*') 
                    count++;
                if (i < n - 1 && a[i + 1][j] == '*') 
                    count++;
                if (j > 0 && a[i][j - 1] == '*') 
                    count++;
                if (j < m - 1 && a[i][j + 1] == '*') 
                    count++;
                if (i > 0 && j > 0 && a[i - 1][j - 1] == '*') 
                    count++;
                if (i < n - 1 && j < m - 1 && a[i + 1][j + 1] == '*') 
                    count++;
                if (i > 0 && j < m - 1 && a[i - 1][j + 1] == '*') 
                    count++;
                if (i < n - 1 && j > 0 && a[i + 1][j - 1] == '*') 
                    count++;
                if (count > 0)
                    a[i][j] = count + '0';
            }
        }
    }
}

void get_odd_magic_square(unsigned **a, unsigned n)
{
    unsigned i, j, n_square = n * n;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            a[i][j] = 0;
    i = n / 2, j = n - 1;
    a[i][j] = 1;
    for (unsigned counter = 2; counter <= n_square; counter++)
    {
        if (a[(i - 1 + n) % n][(j + 1) % n] == 0)
        {
            i = (i - 1 + n) % n;
            j = (j + 1) % n;
        }
        else
        {
            j = (j - 1 + n) % n;
        }
        a[i][j] = counter;
    }
}
void get_double_even_magic_square(unsigned **a, unsigned n)
{
    unsigned i, j, n_half_half = n / 4;
    unsigned n_3_half_half = 3 * n_half_half;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            a[i][j] = (n * i) + j + 1;
    for (i = 0; i < n_half_half; i++)
        for (j = 0; j < n_half_half; j++)
            a[i][j] = (n * n + 1) - a[i][j];
    for (i = 0; i < n_half_half; i++)
        for (j = n_3_half_half; j < n; j++)
            a[i][j] = (n * n + 1) - a[i][j];
    for (i = n_3_half_half; i < n; i++)
        for (j = 0; j < n_half_half; j++)
            a[i][j] = (n * n + 1) - a[i][j];
    for (i = n_3_half_half; i < n; i++)
        for (j = n_3_half_half; j < n; j++)
            a[i][j] = (n * n + 1) - a[i][j];
    for (i = n_half_half; i < n_3_half_half; i++)
        for (j = n_half_half; j < n_3_half_half; j++)
            a[i][j] = (n * n + 1) - a[i][j];
}
void get_single_even_magic_square(unsigned **a, unsigned n)
{
    unsigned size = n * n, n_half = n / 2, i, j;
    unsigned sub_magic_square_size = size / 4;
    unsigned **sub_magic_square = (unsigned **)malloc(n * sizeof(unsigned *));
    for (i = 0; i < n; i++)
        sub_magic_square[i] = (unsigned *)malloc(n * sizeof(unsigned));
    get_odd_magic_square(sub_magic_square, n_half);
    unsigned square_factors[] = {0, 2, 3, 1};
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            a[i][j] = sub_magic_square[i % n_half][j % n_half];
            a[i][j] += square_factors[(i / n_half) * 2 + (j / n_half)] * sub_magic_square_size;
        }
    for (i = 0; i < n; i++)
        free(sub_magic_square[i]);
    free(sub_magic_square);
    sub_magic_square = NULL;
    unsigned j_left = n_half / 2;
    unsigned j_right = j_left - 1;
    for (i = 0; i < n_half; i++)
        for (j = 0; j < n; j++)
            if (j < j_left || j >= n - j_right || (j == j_left && i == j_left))
            {
                if (j == 0 && i == j_left)
                    continue;
                unsigned temp = a[i][j];
                a[i][j] = a[i + n_half][j];
                a[i + n_half][j] = temp;
            }
}
bool get_magical_square(unsigned **a, unsigned n)
{
    if (n % 2)
        get_odd_magic_square(a, n);
    else if (!(n % 4))
        get_double_even_magic_square(a, n);
    else if (n == 2)
        return false;
    else
        get_single_even_magic_square(a, n);
    return true;
}