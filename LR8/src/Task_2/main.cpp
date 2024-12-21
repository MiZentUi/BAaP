#include <iostream>
#include <string>
#include <sstream>

#include "student_tools.h"

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
    student_t *students = nullptr;
    int size = 0;
    std::cout << ASCII_COLOR_YELLOW << "\n\tWelcome to Task 2 Option 13!\n\n\tBy MiZentUi\n\nTo obtain a place in the dormitory, a list of students is formed, which includes full name student, group, average score, income per family member. Dormitory accommodation is primarily provided to those with income per family member less than two minimum wages, then the rest in order of decreasing average score. Display the queue list provision of places in a hostel.\n" << std::endl;
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
            if (students != nullptr)
            {
                delete[] students;
                students = nullptr;
            }
            input(students, size);
        }
        else if (command == "print")
            print(students, size);
        else if (command == "add")
            input(students, size, true);
        else if (command == "search")
            search(students, size);
        else if (command == "delete")
        {
            int index = -1;
            ss >> index;
            index--;
            if (index < size && index >= 0)
                delete_student(students, size, index);
            else 
                std::cout << ASCII_COLOR_RED << "[*] Quantity is out!" << ASCII_RESET << std::endl;
        }
        else if (command == "replace")
        {
            int index = -1;
            ss >> index;
            index--;
            if (0 <= index && index < size)
                replace(students, size, index);
            else 
                std::cout << ASCII_COLOR_RED << "[*] Quantity is out!" << ASCII_RESET << std::endl;
        }
        else if (command == "sort")
            sort(students, size);
        else if (command == "save")
            save(students, size);
        else if (command == "load")
            load(students, size);
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
    if (students != nullptr)
    {
        delete[] students;
        students = nullptr;
    }
    return 0;
}