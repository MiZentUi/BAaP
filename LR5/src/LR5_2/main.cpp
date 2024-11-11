#include <iostream>
#include <string>
#include <Windows.h>

#define ASCII_RESET "\x1b[0m" 
#define ASCII_COLOR_RED "\x1b[0;31m"
#define ASCII_COLOR_GREEN "\x1b[0;32m" 
#define ASCII_COLOR_YELLOW "\x1b[0;33m" 

bool get_long_long(std::string prompt, long long& n)
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

bool get_long_double_array(std::string prompt, long double* a, long long n)
{
    std::string s;
    std::cout << prompt;
    for (long long i = 0; i < n; i++)
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
    if (!get_long_long("Write N: ", n)) return;
    if (n > 0)
    {
        long double* a = new long double[n];
        if (!get_long_double_array("Write array elments: \n", a, n)) return;
        HINSTANCE dll = LoadLibrary(L"LR5_DynamicLib.dll");
        typedef bool (*Check)(long double*, long long, long long);
        Check check;
        if (dll)
        {
            check = (Check)GetProcAddress(dll, "check");
            bool result = check(a, 0, n - 1);
            std::cout << ASCII_COLOR_GREEN"[*] Result: ";
            if (result)
                std::cout << "true";
            else
                std::cout << "false";
            std::cout << ASCII_RESET << std::endl;
            FreeLibrary(dll);
        }
        delete[] a;
        a = nullptr;
    }
}

void help()
{
    std::cout << ASCII_COLOR_YELLOW"\n\tcalc\tcalulate" << std::endl;
    std::cout << "\thelp\tcommands info" << std::endl;
    std::cout << "\texit\texit from program\n" ASCII_RESET << std::endl;
}

int main(int argc, char const* argv[])
{
    std::cout << ASCII_COLOR_YELLOW"\n\tWelcome to Task 1 Option 13!\n\n\tBy Skrobot Denis\n\n\tThis program for a given one-dimensional array A of N elements, check that there is at least one element Ai for which the condition A =< i^2 is satisfied\n" << std::endl;
    std::cout << "[*] Write \"calc\" for calculate, write \"help\" for more info\n" ASCII_RESET << std::endl;
    while (true)
    {
        std::string command;
        std::cout << ASCII_COLOR_GREEN"\r~$ \x1b[0m" ASCII_RESET;
        getline(std::cin, command);
        command.erase(command.find_last_not_of(' ') + 1);
        if (command == "")
        {
            continue;
        }
        else if (command == "calc")
        {
            calculate();
        }
        else if (command == "help")
            help();
        else if (command == "exit" || command == "quit" || command == "q")
            return 0;
        else
            std::cout << ASCII_COLOR_RED"[*] Command \"" << command << "\" not found! Write \"help\" for more info" ASCII_RESET << std::endl;
    }
    return 0;
}