#include <iostream>
#include <string>
#include <cmath>
#include <csignal>

#define ASCII_RESET "\e[0m" 
#define ASCII_COLOR_RED "\e[0;31m" 
#define ASCII_COLOR_GREEN "\e[0;32m" 
#define ASCII_COLOR_YELLOW "\e[0;33m" 

class bouble
{
    private:
        long long exponent = 0;
        long long mantis;

    public:
        bouble () {}

        bouble (const long long n)
        {
            mantis = n;
        }

        bouble (const std::string sin)
        {
            std::string s = "";
            bool fractional = false;
            for (size_t i = 0; i < sin.size(); i++)
            {
                if (sin[i] == 'e')
                {
                    std::string exponentional(sin.begin() + i + 1, sin.end());
                    exponent += std::stoll(exponentional);
                    break;
                }
                if (sin[i] == '.')
                {
                    fractional = true;
                }
                else 
                {
                    if (fractional) exponent--;
                    s += sin[i];
                }
            }
            mantis = std::stoll(s);
        }

        long long get_mantis() { return mantis; }
        long long get_exponent() { return exponent; }

        friend std::ostream &operator << (std::ostream &os, const bouble &b)
        {
            std::string s = "", s_mantis = std::to_string(llabs(b.mantis));
            if (b.mantis < 0) s += '-';
            if (s_mantis.size() <= -b.exponent)
            {
                for (int i = 0; i < -b.exponent - (long long)s_mantis.size() + 1; i++)
                    // std::cout << -b.exponent << " " << s_mantis.size() << " " << -b.exponent - (long long)s_mantis.size() + 1 << std::endl;
                    s += "0";
            }
            s += s_mantis;
            if (b.exponent > 0)
            {
                for (int i = 0; i < b.exponent; i++)
                {
                    s += "0";
                }
            }
            if (b.exponent < 0) s.insert(s.size() + b.exponent, 1, '.');
            os << s;
            return os;   
        }

        bouble operator + (const bouble &b)
        {
            bouble a = *this;
            if (a.exponent > b.exponent)
            {
                if (std::llabs(a.exponent - b.exponent) <= 18) 
                {
                    for (int i = 0; i < a.exponent - b.exponent; i++) a.mantis *= 10;
                    a.exponent = b.exponent;
                    a.mantis += b.mantis;
                } 
            }
            else if (a.exponent < b.exponent)
            {
                if (std::llabs(a.exponent - b.exponent) > 18)
                    a = b;
                else
                {
                    long long power = 1;
                    for (int i = 0; i < b.exponent - a.exponent; i++) power *= 10;
                    a.mantis += b.mantis * power;
                }
            }
            else
                a.mantis += b.mantis;
            return a;
        }

        bouble operator - (const bouble &b)
        {
            bouble negative = b;
            negative.mantis = -negative.mantis;
            return *this + negative;
        }
        
        bouble operator * (const bouble &b)
        {
            bouble a = *this;
            a.mantis *= b.mantis;
            a.exponent += b.exponent;
            return a;
        }

        bouble operator += (const bouble &n)
        {
            return *this = (*this + n);
        }
};

bool get_bouble(std::string prompt, bouble &n)
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
        n = bouble(s);
        return true;
    }
    else
    {
        std::cout << ASCII_COLOR_RED"[*] \"" << s << "\" not a number!" ASCII_RESET << std::endl;
        return false;
    }
}

bool get_ll(std::string prompt, long long &n)
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

bool stop = false;

void signal_handler(int s) 
{
    std::cout << std::endl;
    if (stop) exit(0);
    stop = true;
}

void calculate()
{
    stop = false;
    signal(SIGINT, signal_handler);
    long long n;
    bouble a0, d, sum("0");
    if (!get_bouble("Write a₀: ", a0)) return;
    if (!get_bouble("Write d: ", d)) return;
    if (!get_ll("Write n: ", n)) return;
    for (long long i = 1; i <= n; i++)
    {
        if (stop) break;
        bouble a = a0 + d * bouble(i - 1);
        // std::cout << sum << std::endl;
        sum += bouble(std::pow(2, i - 1) * std::pow(-1, i - 1)) * a;
    }
    if (!stop) std::cout << ASCII_COLOR_GREEN"[*] Result: " << sum << ASCII_RESET << std::endl;
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
        stop = true;
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
    // std::cout << sizeof(long long) << " " << std::endl;
    // bouble b1("0.5"), b2(1);
    // // std::cout << b.get_mantis() << "e" << b.get_exponent() << std::endl;
    // b2 += bouble(2);
    // std::cout << b1 << " " << b2 << " " << b1 * b2 << std::endl;
    bouble b1("1e30");
    b1 += bouble(2);
    std::cout << b1 << std::endl;
    return 0;
}