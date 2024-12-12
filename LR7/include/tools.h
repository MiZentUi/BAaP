#pragma once

#include <string>

unsigned short * string_to_array(std::string str);

void twos_to_trivial(unsigned short *array, size_t size);

void bin_add(unsigned short *&a_array, size_t a_size, unsigned short *&b_array, size_t b_size, unsigned short *&c_array, size_t &c_size);

void trivial_to_twos(unsigned short *&array, size_t &size);

void dec_to_bin(long long n, unsigned short *&array, size_t &size);

long long bin_to_dec(const unsigned short *array, size_t size);

std::string string_notation_addition(std::string str1, std::string str2, int base);

std::string string_notation_substract(std::string str1, std::string str2, int base);

bool is_divide(long long num, long long divider);