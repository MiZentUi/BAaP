#include <iostream>
#include <string>
#include <cmath>

#define ASCII_RESET "\e[0m" 
#define ASCII_COLOR_RED "\e[0;31m" 
#define ASCII_COLOR_GREEN "\e[0;32m" 
#define ASCII_COLOR_YELLOW "\e[0;33m" 

bool get_num(std::string prompt, long long &n)
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

void calculate()
{
    long long a0, d, n, sum = 0;
    if (!get_num("Write a₀: ", a0)) return;
    if (!get_num("Write d: ", d)) return;
    if (!get_num("Write n: ", n)) return;
    for (long long i = 1; i <= n; i++)
    {
        long long a = a0 + d * (i - 1);
        sum += std::pow(2, i - 1) * std::pow(-1, i - 1) * a;
    }
    std::cout << ASCII_COLOR_GREEN"[*] Result: " << sum << ASCII_RESET << std::endl;
}

void help()
{
    std::cout << ASCII_COLOR_YELLOW"\n\tcalc\tcalulate by formula" << std::endl;
    std::cout << "\thelp\tcommands info" << std::endl;
    std::cout << "\texit\texit from program\n" ASCII_RESET << std::endl;
}

int main(int argc, char const *argv[])
{
    std::cout << ASCII_COLOR_YELLOW"\n\tWelcome to Task 8!\n\n\tBy Skrobot Denis\n\n\tThis program calculates a₀ - 2a₁ + 4a₂ - 8a₃ + ... + 2ⁿ⁻¹(-1)ⁿ⁻¹aₙ₋₁\n" << std::endl;
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