#include <iostream>
#include <string>
#include "tools.h"

#define ASCII_RESET "\e[0m" 
#define ASCII_COLOR_RED "\e[0;31m"
#define ASCII_COLOR_GREEN "\e[0;32m" 
#define ASCII_COLOR_YELLOW "\e[0;33m" 

bool get_long_long(std::string prompt, long long &n)
{
    std::string s;
    std::cout << prompt;
    std::cin >> s;
    std::cin.ignore();
    if (s == "exit" || s == "quit" || s == "q") return false;
    bool isdigit = true;
    for (char c : s) 
    {
        if (!std::isdigit(c) && c != 'e' && c != '.' && c != '-') isdigit = false;
    }
    if (isdigit && (std::isdigit(s[0]) || s[0] == '-') && std::isdigit(s[s.size() - 1]))
    {
        n = std::stoll(s);
        return true;
    }
    else
    {
        std::cout << ASCII_COLOR_RED"[*] \"" << s << "\" not a number!" ASCII_RESET << std::endl;
        return false;
    }
}

bool get_long_double_array(std::string prompt, long double *a, long long size)
{
    std::string s, current_string;
    std::cout << prompt;
    for (long long i = 0; i < size; i++)
    {
        std::cin >> s;
        std::cin.ignore();
        if (s == "exit" || s == "quit" || s == "q") return false;
        bool isdigit = true;
        for (char c : s) 
        {
            if (!std::isdigit(c) && c != 'e' && c != '.' && c != '-') isdigit = false;
        }
        if (isdigit && (std::isdigit(s[0]) || s[0] == '-') && std::isdigit(s[s.size() - 1]))
        {
            a[i] = std::stold(s);
        }
        else
        {
            std::cout << ASCII_COLOR_RED"[*] \"" << s << "\" not a number!" ASCII_RESET << std::endl;
            return false;
        }
    }
    return true;
}

void calculate()
{
    long long n;
    if (!get_long_long("Write array size: ", n)) return;
    long double a[n];
    if (!get_long_double_array("Write array elments: ", a, n)) return;
    std::cout << "[*] Size: " << n << "\tArray: ";
    for (long long i : a) std::cout << i << " ";
    std::cout << std::endl;
    std::cout << ASCII_COLOR_GREEN"[*] Result: " << get_larger_count(a, n) << ASCII_RESET << std::endl;
}

void help()
{
    std::cout << ASCII_COLOR_YELLOW"\n\tcalc\tcalulate" << std::endl;
    std::cout << "\thelp\tcommands info" << std::endl;
    std::cout << "\texit\texit from program\n" ASCII_RESET << std::endl;
}

int main(int argc, char const *argv[])
{
    std::cout << ASCII_COLOR_YELLOW"\n\tWelcome to Task 1 Option 13!\n\n\tBy Skrobot Denis\n\n\tThis program determine the number of elements whose value is greater the average value of all array elements\n" << std::endl;
    std::cout << "[*] Write \"calc\" for calculate, write \"help\" for more info\n" ASCII_RESET << std::endl;
    while (true)
    {
        std::string command;
        std::cout << ASCII_COLOR_GREEN"~$ \x1b[0m" ASCII_RESET;
        getline(std::cin, command);
        if (command == "")
            continue;
        else if (command == "calc")
            calculate();
        else if (command == "help")
            help();
        else if (command == "exit" || command == "quit" || command == "q")
            return 0;
        else
            std::cout << ASCII_COLOR_RED"[*] Command \"" << command << "\" not found! Write \"help\" for more info" ASCII_RESET << std::endl;
    }
    return 0;
}