#include <iostream>
#include <string>
#include "tools.h"

#define ASCII_RESET "\x1b[0m" 
#define ASCII_COLOR_RED "\x1b[0;31m"
#define ASCII_COLOR_GREEN "\x1b[0;32m" 
#define ASCII_COLOR_YELLOW "\x1b[0;33m" 

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

bool get_long_long_matrix(std::string prompt, long long **a, long long n, long long k)
{
    std::string s;
    std::cout << prompt;
    for (long long i = 0; i < n; i++)
    {
        for (long long j = 0; j < k; j++)
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
                a[i][j] = std::stoll(s);
            }
            else
            {
                std::cout << ASCII_COLOR_RED"[*] \"" << s << "\" not a number!" ASCII_RESET << std::endl;
                return false;
            }
        }
    }
    return true;
}

void calculate()
{
    long long n, m, p;
    if (!get_long_long("Write n: ", n)) return;
    if (!get_long_long("Write m: ", m)) return;
    long long **a = new long long *[n];
    for (long long i = 0; i < n; i++)
        a[i] = new long long[m];
    if (n && m && !get_long_long_matrix("Write matrix elments: \n", a, n, m)) return;
    long long *b = nullptr;
    get_even_odd_array(a, n, m, b, p);
    long long mean;
    if (p)
        mean = arithmetic_mean(b, p);
    std::cout << ASCII_COLOR_GREEN"[*] Array: ";
    for (long long i = 0; i < p; i++)
        std::cout << b[i] << " ";
    if (n && m && p)
        std::cout << "\n[*] Anithmetic mean: " << mean << ASCII_RESET;
    std::cout << std::endl;
    for (long long i = 0; i < n; i++)
        delete[] a[i];
    delete[] a, b;
    a = nullptr, b = nullptr;
}

void help()
{
    std::cout << ASCII_COLOR_YELLOW"\n\tcalc\tcalulate" << std::endl;
    std::cout << "\thelp\tcommands info" << std::endl;
    std::cout << "\texit\texit from program\n" ASCII_RESET << std::endl;
}

int main(int argc, char const *argv[])
{
    std::cout << ASCII_COLOR_YELLOW"\n\tWelcome to Task 5!\n\n\tBy Skrobot Denis\n\n\tThis program creates a dynamic array from elements located in even columns of the given array and having an odd value and calculates the arithmetic mean of the elements of the dynamic array\n" << std::endl;
    std::cout << "[*] Write \"calc\" for calculate, write \"help\" for more info\n" ASCII_RESET << std::endl;
    while (true)
    {
        std::string command;
        std::cout << ASCII_COLOR_GREEN"\r~$ \x1b[0m" ASCII_RESET;
        getline(std::cin, command);
        command.erase(command.find_last_not_of(' ') + 1);
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