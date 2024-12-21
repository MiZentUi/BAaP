#include <iostream>
#include <string>
#include <sstream>

#include "train_tools.h"

void help()
{
    std::cout << ASCII_COLOR_YELLOW << std::endl;
    std::cout << "\tinput\t\tinput item" << std::endl;
    std::cout << "\tprint\t\tprint item" << std::endl;
    std::cout << "\tadd\t\tadd item in exists list" << std::endl;
    std::cout << "\treplace <num>\treplace specific item" << std::endl;
    std::cout << "\tdelete <num>\tdelete specific item" << std::endl;
    std::cout << "\tsearch\t\tsearch by string" << std::endl;
    std::cout << "\tsort\t\tsort item list" << std::endl;
    std::cout << "\tsave\t\tsave item list in file" << std::endl;
    std::cout << "\tload\t\tload item list from file" << std::endl;
    std::cout << "\tfreplace\treplace specific item in file" << std::endl;
    std::cout << "\thelp\t\tcommands info" << std::endl;
    std::cout << "\texit\t\texit from program" << std::endl;
    std::cout << ASCII_RESET << std::endl;
}

int main()
{
    train_t *trains = nullptr;
    int size = 0;
    std::cout << ASCII_COLOR_YELLOW << "\n\tWelcome to Task 1 Option 13!\n\n\tBy MiZentUi\n\nThe railway ticket office administrator has information about available seats on trains for the current day in the following form: destination, departure time, number of available seats. Withdraw information about the number of free seats on trains traveling to a given date destination (insertion sort in descending order).\n"
              << std::endl;
    std::cout << "[*] Write \"help\" for more info\n" << ASCII_RESET << std::endl;
    while (true)
    {
        std::string command;
        std::cout << ASCII_COLOR_GREEN << "~$ " << ASCII_RESET;
        std::getline(std::cin, command);
        std::stringstream ss(command);
        if (!command.empty())
        {
            ss >> command;
        }
        if (command.empty())
            continue;
        else if (command == "input")
        {
            if (trains != nullptr)
            {
                delete[] trains;
                trains = nullptr;
            }
            input(trains, size);
        }
        else if (command == "print")
            print(trains, size);
        else if (command == "add")
            input(trains, size, true);
        else if (command == "search")
            search(trains, size);
        else if (command == "delete")
        {
            int index = -1;
            ss >> index;
            index--;
            if (index < size && index >= 0)
                delete_student(trains, size, index);
            else 
                std::cout << ASCII_COLOR_RED << "[*] Quantity is out!" << ASCII_RESET << std::endl;
        }
        else if (command == "replace")
        {
            int index = -1;
            ss >> index;
            index--;
            if (0 <= index && index < size)
                replace(trains, size, index);
            else 
                std::cout << ASCII_COLOR_RED << "[*] Quantity is out!" << ASCII_RESET << std::endl;
        }
        else if (command == "sort")
            sort(trains, size);
        else if (command == "save")
            save(trains, size);
        else if (command == "load")
            load(trains, size);
        else if (command == "freplace")
        {
            int index = -1;
            ss >> index;
            file_replace(index - 1);
        }
        else if (command == "help")
            help();
        else if (command == "exit" || command == "quit" || command == "q")
            break;
        else
            std::cout << ASCII_COLOR_RED << "[*] Command \"" << command << "\" not found! Write \"help\" for more info" << ASCII_RESET << std::endl;
    }
    if (trains != nullptr)
    {
        delete[] trains;
        trains = nullptr;
    }
    return 0;
}