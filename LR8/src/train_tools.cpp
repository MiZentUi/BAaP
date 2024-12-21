#include "train_tools.h"

#include <cctype>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

train_t * reallocation(train_t *array, int size, int new_size)
{
    if (new_size != size)
    {
        train_t *new_array = new train_t[new_size];
        if (size > 0)
        {
            if (new_size < size)
                std::memcpy(new_array, array, new_size * sizeof(train_t));
            else
                std::memcpy(new_array, array, size * sizeof(train_t));
            if (array != nullptr)
                delete[] array;
        }
        array = new_array;
    }
    return array;
}

train_t get_train()
{
    train_t train;
    std::string s;
    std::cout << INDENT << "Destination: ";
    std::getline(std::cin, s);
    std::strncpy(train.destination, s.c_str(), MAX_STRING_SIZE);
    std::cout << INDENT << "Departure time: ";
    std::getline(std::cin, s);
    std::strncpy(train.departure_time, s.c_str(), MAX_STRING_SIZE);
    std::cout << INDENT << "Arrival_time: ";
    std::getline(std::cin, s);
    std::strncpy(train.arrival_time, s.c_str(), MAX_STRING_SIZE);
    std::cout << INDENT << "Available seats count: ";
    std::getline(std::cin, s);
    if (std::isdigit(s[0]))
        train.available_seats_count = std::stoi(s);
    std::cout << INDENT << "Train color in hex format: ";
    std::getline(std::cin, s);
    char c = std::tolower(s[0]);
    if (std::isdigit(c) || c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f')
        train.color.hex = std::stoi(s, NULL, 16);
    return train;
}

void input(train_t *&trains, int &size, bool add)
{
    int current_size = size > 0 ? size : 0;
    std::cout << ASCII_COLOR_GREEN << "Write trains count: " << ASCII_RESET;
    std::cin >> size;
    std::cin.ignore(100, '\n');
    if (size < 1)
        return;
    if (!add)
    {
        current_size = 0;
        trains = new train_t[size];
    }
    else
    {
        size += current_size;
        trains = reallocation(trains, current_size, size);
    }
    for (int i = current_size; true; i++)
    {
        std::cout << ASCII_COLOR_GREEN << "Train " << i + 1 << ASCII_RESET << std::endl;
        train_t train = get_train();
        if (!std::strlen(train.destination) && !std::strlen(train.departure_time) && !std::strlen(train.arrival_time) && !train.available_seats_count && !train.color.hex)
        {
            std::cout << ASCII_COLOR_YELLOW << "You write empty train, do you want to continue? [y/N] " << ASCII_RESET;
            std::string s;
            std::getline(std::cin, s);
            if (std::tolower(s[0]) != 'y')
                break;
        }
        trains[i] = train;
        if (i == size - 1)
        {
            std::cout << ASCII_COLOR_YELLOW << "Quantity is out, do you want to continue? [y/N] " << ASCII_RESET;
            std::string s;
            std::getline(std::cin, s);
            if (std::tolower(s[0]) != 'y')
                break;
            else
            {
                int new_size;
                std::cout << ASCII_COLOR_GREEN << "Write trains count: " << ASCII_RESET;
                std::getline(std::cin, s);
                std::stringstream ss(s);
                ss >> new_size;
                if (new_size < 1)
                    break;
                new_size += size;
                trains = reallocation(trains, size, new_size);
                size = new_size;
            }
        }
    }
}

void print_train(train_t train)
{
    std::cout << INDENT << "Destination: " << train.destination << std::endl;
    std::cout << INDENT << "Departure time: " << train.departure_time << std::endl;
    std::cout << INDENT << "Arrival_time: " << train.arrival_time << std::endl;
    std::cout << INDENT << "Available seats count: " << train.available_seats_count << std::endl;
    std::cout << INDENT << "Train color: \x1b[48;2;" << train.color.primary.R << ";" << train.color.primary.G << ";" << train.color.primary.B << "m    " << ASCII_RESET << std::endl;
}

void print(train_t *&trains, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        std::cout << ASCII_COLOR_GREEN << "Train " << i + 1 << ":" << ASCII_RESET << std::endl;
        print_train(trains[i]);
    }
    if (!i)
        std::cout << ASCII_COLOR_YELLOW << "[*] Trains list is empty!" << ASCII_RESET << std::endl;
}

void add(train_t *trains, int &size)
{
    int new_size;
    std::cout << "Write trains count: ";
    std::cin >> new_size;
    trains = reallocation(trains, size, new_size);
    size = new_size;
}

std::string to_lowercase(std::string s)
{
    for (char &c : s)
        if (std::isupper(c))
            c = std::tolower(c);
    return s;
}

void search(train_t *trains, int size)
{
    std::string search_string;
    std::cout << ASCII_COLOR_GREEN << "Search: " << ASCII_RESET;
    std::getline(std::cin, search_string);
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        std::stringstream ss;
        ss << trains[i].destination << ' ' << trains[i].departure_time << ' ' << trains[i].arrival_time << ' ' << trains[i].available_seats_count << ' ' << std::hex << trains[i].color.hex;
        if (to_lowercase(ss.str()).find(search_string) != std::string::npos)
        {
            std::cout << ASCII_COLOR_GREEN << "Train " << i + 1 << ":" << ASCII_RESET << std::endl;
            print_train(trains[i]);
            count++;
        }
    }
    if (!count)
        std::cout << ASCII_COLOR_YELLOW << "[*] Trains not found!" << ASCII_RESET << std::endl;
}

void delete_student(train_t *&trains, int &size, int index)
{
    if (size > 1)
    {
        train_t *new_trains = new train_t[size - 1];
        if (index > 0)
            std::memcpy(new_trains, trains, index * sizeof(train_t));
        if (size - index - 1 > 0)
            std::memcpy(new_trains + index, trains + index + 1, (size - index - 1) * sizeof(train_t));
        if (trains != nullptr)
            delete[] trains;
        trains = new_trains;
        size--;
    }
    else
    {
        if (trains != nullptr)
        {
            delete[] trains;
            trains = nullptr;
        }
        size = 0;
    }
}

void replace(train_t *&trains, int &size, int index)
{
    std::cout << ASCII_COLOR_GREEN << "Train " << index + 1 << ":" << ASCII_RESET << std::endl;
    trains[index] = get_train();
}

void sort(train_t *&trains, int size)
{
    for (int i = 1; i < size; i++)
        for (int j = size - i - 1; j < size - 1 && trains[j].available_seats_count < trains[j + 1].available_seats_count; j++)
            std::swap(trains[j], trains[j + 1]);
}

void save(train_t *trains, int size)
{
    std::fstream file;
    file.open("trains", std::ios::out | std::ios::binary);
    file.write((char *)trains, size * sizeof(train_t));
    file.close();
}

void load(train_t *&trains, int &size)
{
    std::fstream file;
    file.open("trains", std::ios::in | std::ios::binary);
    if (file.good())
    {
        file.seekg(0, file.end);
        size = file.tellg() / sizeof(train_t);
        file.seekg(0, file.beg);
        trains = new train_t[size];
        file.read((char *)trains, size * sizeof(train_t));
        file.close();
    }
    else 
        std::cout << ASCII_COLOR_RED << "[*] Save not found!" << ASCII_RESET << std::endl;
}

void file_replace(int index)
{
    std::fstream file;
    file.open("trains", std::ios::in | std::ios::out | std::ios::binary);
    if (file.good())
    {
        file.seekg(0, file.end);
        int size = file.tellg() / sizeof(train_t);
        if (0 <= index && index < size)
        {
            std::cout << ASCII_COLOR_GREEN << "Train " << index + 1 << ":" << ASCII_RESET << std::endl;
            train_t train = get_train();
            file.seekp(index * sizeof(train_t), file.beg);
            file.write((char *)&train, sizeof(train_t));
        }
        else 
            std::cout << ASCII_COLOR_RED << "[*] Quantity is out!" << ASCII_RESET << std::endl;
        file.close();
    }
    else 
        std::cout << ASCII_COLOR_RED << "[*] Save not found!" << ASCII_RESET << std::endl;
}