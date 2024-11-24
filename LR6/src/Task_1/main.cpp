#include <iostream>
#include <string>
#include "tools.h"

#define ASCII_RESET "\x1b[0m"
#define ASCII_COLOR_RED "\x1b[0;31m"
#define ASCII_COLOR_GREEN "\x1b[0;32m"
#define ASCII_COLOR_YELLOW "\x1b[0;33m"

void calculate()
{
    int max_word_serial, max_word_index;
    String s;
    std::cout << "Write string line: ";
    s.read();
    s.get_max_word(max_word_serial, max_word_index);
    std::cout << ASCII_COLOR_GREEN "[*] Max word serial: " << max_word_serial << "\n[*] Max word index: " << max_word_index << ASCII_RESET << std::endl;
}

void help()
{
    std::cout << ASCII_COLOR_YELLOW "\n\tcalc\tcalulate" << std::endl;
    std::cout << "\thelp\tcommands info" << std::endl;
    std::cout << "\texit\texit from program\n" ASCII_RESET << std::endl;
}

int main()
{
    std::cout << ASCII_COLOR_YELLOW "\n\tWelcome to Task 1 Option 13!\n\n\tBy Skrobot Denis\n\n\tThis program find the ordinal number of the word of maximum length and the position number of the line from which it begins.\n"
              << std::endl;
    std::cout << "[*] Write \"calc\" for calculate, write \"help\" for more info\n" ASCII_RESET << std::endl;
    while (true)
    {
        std::string command;
        std::cout << ASCII_COLOR_GREEN "~$ " ASCII_RESET;
        std::cin >> command;
        std::cin.ignore();
        if (command == "")
            continue;
        else if (command == "calc")
            calculate();
        else if (command == "help")
            help();
        else if (command == "exit" || command == "quit" || command == "q")
            return 0;
        else
            std::cout << ASCII_COLOR_RED "[*] Command \"" << command << "\" not found! Write \"help\" for more info" ASCII_RESET << std::endl;
    }
    return 0;
}