#include <iostream>
#include <string>
#include "cmath.h"

#define ASCII_RESET "\e[0m" 
#define ASCII_COLOR_RED "\e[0;31m" 
#define ASCII_COLOR_GREEN "\e[0;32m" 
#define ASCII_COLOR_YELLOW "\e[0;33m" 

void calculate()
{
    std::string s;
    std::cout << "Write x: ";
    std::cin >> s;
    std::cin.ignore();
    double x;
    if (s == "exit" || s == "quit" || s == "q") return;
    bool isdigit = true;
    for (char c : s) 
    {
        if (!std::isdigit(c) && c != 'e' && c != '.' && c != '-') isdigit = false;
    }
    if (isdigit && (std::isdigit(s[0]) || s[0] == '-')&& std::isdigit(s[s.size() - 1]))
        x = std::stod(s);
    else
    {
        std::cout << ASCII_COLOR_RED"[*] \"" << s << "\" not a number!" ASCII_RESET << std::endl;
        return;
    }
    double a = std::sin(x), b = std::cos(x), c = std::ln(abs(x));
    double min = a < b ? (a < c ? a : c) : (b < c ? b : c);
    std::cout << ASCII_COLOR_GREEN"[*] Result: " << min << ASCII_RESET << std::endl;
}

void help()
{
    std::cout << ASCII_COLOR_YELLOW"\n\tcalc\tcalulate by formula" << std::endl;
    std::cout << "\thelp\tcommands info" << std::endl;
    std::cout << "\texit\texit from program\n" ASCII_RESET << std::endl;
}

int main(int argc, char const *argv[])
{
    std::cout << ASCII_COLOR_YELLOW"\n\tWelcome to Task 6!\n\n\tBy Skrobot Denis\n\n\tThis program calculates min of a = sinx, b = cosx, c = ln|x|\n" << std::endl; 
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