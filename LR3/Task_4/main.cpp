#include <iostream>
#include <string>
#include <cmath>

#define ASCII_RESET "\e[0m" 
#define ASCII_COLOR_RED "\e[0;31m" 
#define ASCII_COLOR_GREEN "\e[0;32m" 
#define ASCII_COLOR_YELLOW "\e[0;33m" 

bool get_double(std::string prompt, long double &n)
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
        n = std::stod(s);
        return true;
    }   
    else
    {
        std::cout << ASCII_COLOR_RED"[*] \"" << s << "\" not a number!" ASCII_RESET << std::endl;
        return false;
    }
}

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

long double series(long double x, long long n)
{
    long double sum = 0;
    for (long long i = 1; i <= n; i++)
        sum += std::pow(-1, i) * std::pow(1 + x, 2 * i) / i;
    return sum;
}

void calculate()
{
    long long n, count;
    if (!get_long_long("Write n: ", n)) return;
    if (!get_long_long("Write count of x: ", count)) return;
    long double xs[count];
    for (long long i = 0; i < count; i++)
    {
        long double x;
        if (!get_double("Write x: ", x)) return;
        xs[i] = x;
    }
    for (long long i = 0; i < count; i++)
    {
        long double s = series(xs[i], n);
        long double y = std::log(1 / (2 + 2 * xs[i] + std::pow(xs[i], 2)));
        std::cout << ASCII_COLOR_GREEN"[*] S(" << xs[i] << "): " << s << "\tY(" << xs[i] << "): " << y << ASCII_RESET << std::endl;
    }
}

void help()
{
    std::cout << ASCII_COLOR_YELLOW"\n\tcalc\tcalulate by formula" << std::endl;
    std::cout << "\thelp\tcommands info" << std::endl;
    std::cout << "\texit\texit from program\n" ASCII_RESET << std::endl;
}

int main(int argc, char const *argv[])
{
    std::cout << ASCII_COLOR_YELLOW"\n\tWelcome to Task 4 Option 13!\n\n\tBy Skrobot Denis\n\n\tThis program calculates S(x) and Y(x), where" << std::endl;
    std::cout << "\tS(x) = ᵢ₌₁∑ⁿ (-1) * (1 + x)²ⁿ / n" << std::endl;
    std::cout << "\tY(x) = ln(1 / (2 * 2x * x²))\n" << std::endl;
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