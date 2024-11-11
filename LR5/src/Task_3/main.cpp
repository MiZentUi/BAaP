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
    long long n, k, m;
    if (!get_long_long("Write n: ", n)) return;
    if (!get_long_long("Write k: ", k)) return;
    long long **a = new long long *[n];
    for (long long i = 0; i < n; i++)
        a[i] = new long long[k];
    if (n && k && !get_long_long_matrix("Write matrix elments: \n", a, n, k)) return;
    long long *b = nullptr;
    get_even_array(a, n, k, b, m);
    long long product = get_array_product(b, m);
    std::cout << ASCII_COLOR_GREEN"[*] Array: ";
    for (long long i = 0; i < m; i++)
        std::cout << b[i] << " ";
    if (n && k)
        std::cout << "\n[*] Product: " << product << ASCII_RESET;
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
    // TODO: change description
    std::cout << ASCII_COLOR_YELLOW"\n\tWelcome to Task 3!\n\n\tBy Skrobot Denis\n\n\tThis program outputs an array of elements located on the main diagonal of the matrix and having an even value and their product\n" << std::endl;
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