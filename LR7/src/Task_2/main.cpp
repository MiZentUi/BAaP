#include <cstddef>
#include <iostream>

#include "tools.h"

int main()
{
    long long a_num = 0;
    long long b_num = 0;
    std::cout << "First binary in natural form: \t";
    std::cin >> a_num;
    std::cout << "Second binary in natural form: \t";
    std::cin >> b_num;
    unsigned short *a_bin = nullptr;
    unsigned short *b_bin = nullptr;
    unsigned short *c_bin = nullptr;
    size_t a_size = 0;
    size_t b_size = 0;
    size_t c_size = 0;
    dec_to_bin(a_num, a_bin, a_size);
    dec_to_bin(b_num, b_bin, b_size);
    trivial_to_twos(a_bin, a_size);
    trivial_to_twos(b_bin, b_size);
    bin_add(a_bin, a_size, b_bin, b_size, c_bin, c_size);
    twos_to_trivial(c_bin, c_size);
    std::cout << "Result binary in natural form: \t" << bin_to_dec(c_bin, c_size) << std::endl;
    delete[] a_bin;
    a_bin = nullptr;
    delete[] b_bin;
    b_bin = nullptr;
    delete[] c_bin;
    c_bin = nullptr;
    return 0;
}