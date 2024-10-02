#include <iostream>
#include <string>

#define ASCII_RESET "\e[0m" 
#define ASCII_COLOR_RED "\e[0;31m" 
#define ASCII_COLOR_GREEN "\e[0;32m" 
#define ASCII_COLOR_YELLOW "\e[0;33m" 

void calculate()
{
    double sum = 0;
    int i = 1;
    while (i <= 30)
    {
        double a = i % 2 ? i : i / 2.0;
        double b = i % 2 ? i * i : i * i * i;
        sum += (a - b) * (a - b);
        i++;
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
    std::cout << ASCII_COLOR_YELLOW"\n\tWelcome to Task 1!\n\n\tBy Skrobot Denis\n\n\tThis program calculates N = ᵢ₌₁∑³⁰ (aᵢ + bᵢ), where\n" << std::endl; 
    std::cout << "\t     { i, if i even\t\t     { i², if i even\n\taᵢ = {\t\t\t\tbᵢ = {\n\t     { i / 2, if i odd\t\t     { i³, if i odd\n" << std::endl;
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