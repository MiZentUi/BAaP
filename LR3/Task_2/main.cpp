#include <iostream>
#include <string>
#include <cmath>

#define ASCII_RESET "\e[0m" 
#define ASCII_COLOR_RED "\e[0;31m" 
#define ASCII_COLOR_GREEN "\e[0;32m" 
#define ASCII_COLOR_YELLOW "\e[0;33m" 

void calculate()
{
    double n = 0, i = 1, d;
    double sum = 0;
    do
    {
        d = 1 / std::pow(2.0, i) + 1 / std::pow(3.0, i);
        sum += d;
        i++;
    } while (d >= 0.001);
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
    std::cout << ASCII_COLOR_YELLOW"\n\tWelcome to Task 2!\n\n\tBy Skrobot Denis\n\n\tThis program calculates ᵢ₌₀∑ⁿ (1 / 2ⁿ + 1 / 3ⁿ)\n" << std::endl;
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