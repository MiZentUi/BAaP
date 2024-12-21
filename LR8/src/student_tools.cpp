#include "student_tools.h"

#include <cctype>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

student_t * reallocation(student_t *array, int size, int new_size)
{
    if (new_size != size)
    {
        student_t *new_array = new student_t[new_size];
        if (new_size < size)
            std::memcpy(new_array, array, new_size * sizeof(student_t));
        else
            std::memcpy(new_array, array, size * sizeof(student_t));
        delete[] array;
        array = new_array;
    }
    return array;
}

student_t get_student()
{
    student_t student;
    std::string s;
    std::cout << INDENT << "Full name: ";
    std::getline(std::cin, s);
    if (!s.empty())
        std::strncpy(student.full_name, s.c_str(), MAX_STRING_SIZE);
    std::cout << INDENT << "Group: ";
    std::getline(std::cin, s);
    if (!s.empty())
        std::strncpy(student.group.full, s.c_str(), MAX_GROUP_SIZE);
    std::cout << INDENT << "Rating: ";
    std::getline(std::cin, s);
    if (std::isdigit(s[0]))
        student.rating = std::stod(s);
    std::cout << INDENT << "Income: ";
    std::getline(std::cin, s);
    if (std::isdigit(s[0]))
        student.income = std::stoi(s);
    return student;
}

void input(student_t *&students, int &size, bool add)
{
    int current_size = size > 0 ? size : 0;
    std::cout << ASCII_COLOR_GREEN << "Write students count: " << ASCII_RESET;
    std::cin >> size;
    std::cin.ignore(100, '\n');
    if (size < 1)
        return;
    if (!add)
    {
        current_size = 0;
        students = new student_t[size];
    }
    else
    {
        size += current_size;
        students = reallocation(students, current_size, size);
    }
    for (int i = current_size; true; i++)
    {
        std::cout << ASCII_COLOR_GREEN << "Student " << i + 1 << ASCII_RESET << std::endl;
        student_t student = get_student();
        if (!std::strlen(student.full_name) && !std::strlen(student.group.full) && student.rating == 0 && !student.income)
        {
            std::cout << ASCII_COLOR_YELLOW << "You write empty student, do you want to continue? [y/N] " << ASCII_RESET;
            std::string s;
            std::getline(std::cin, s);
            if (std::tolower(s[0]) != 'y')
                break;
        }
        students[i] = student;
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
                std::cout << ASCII_COLOR_GREEN << "Write students count: " << ASCII_RESET;
                std::getline(std::cin, s);
                std::stringstream ss(s);
                ss >> new_size;
                new_size += size;
                students = reallocation(students, size, new_size);
                size = new_size;
            }
        }
    }
}

void print_student(student_t student)
{
    std::cout << INDENT << "Full name: " << student.full_name << std::endl;
    std::cout << INDENT << "Group: " << std::endl;
    std::cout << INDENT << INDENT << "Year: " << student.group.codes.year << std::endl; 
    std::cout << INDENT << INDENT << "Faculty: " << student.group.codes.faculty << std::endl; 
    std::cout << INDENT << INDENT << "Speciality: " << student.group.codes.speciality[0] << student.group.codes.speciality[1] << std::endl; 
    std::cout << INDENT << INDENT << "Education form: " << student.group.codes.eduction_form << std::endl; 
    std::cout << INDENT << INDENT << "Serial number: " << student.group.codes.serial_num << std::endl; 
    std::cout << INDENT << "Rating: " << student.rating << std::endl;
    std::cout << INDENT << "Income: " << student.income << std::endl;
}

void print(student_t *&students, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        std::cout << ASCII_COLOR_GREEN << "Student " << i + 1 << ":" << ASCII_RESET << std::endl;
        print_student(students[i]);
    }
    if (!i)
        std::cout << ASCII_COLOR_YELLOW << "[*] Students list is empty!" << ASCII_RESET << std::endl;
}

void add(student_t *students, int &size)
{
    int new_size;
    std::cout << "Write students count: ";
    std::cin >> new_size;
    students = reallocation(students, size, new_size);
    size = new_size;
}

std::string to_lowercase(std::string s)
{
    for (char &c : s)
        if (std::isupper(c))
            c = std::tolower(c);
    return s;
}

void search(student_t *students, int size)
{
    std::string search_string;
    std::cout << ASCII_COLOR_GREEN << "Search: " << ASCII_RESET;
    std::getline(std::cin, search_string);
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        std::stringstream ss;
        ss << students[i].full_name << ' ' << students[i].group.full << ' ' << students[i].rating << ' ' << students[i].income;
        if (to_lowercase(ss.str()).find(search_string) != std::string::npos)
        {
            std::cout << ASCII_COLOR_GREEN << "Student " << i + 1 << ":" << ASCII_RESET << std::endl;
            print_student(students[i]);
            count++;
        }
    }
    if (!count)
        std::cout << ASCII_COLOR_YELLOW << "[*] Students not found!" << ASCII_RESET << std::endl;
}

void delete_student(student_t *&students, int &size, int index)
{
    if (size > 1)
    {
        student_t *new_students = new student_t[size - 1];
        if (index > 0)
            std::memcpy(new_students, students, index * sizeof(student_t));
        if (size - index - 1 > 0)
            std::memcpy(new_students + index, students + index + 1, (size - index - 1) * sizeof(student_t));
        if (students != nullptr)
            delete[] students;
        students = new_students;
        size--;
    }
    else
    {
        if (students != nullptr)
        {
            delete[] students;
            students = nullptr;
        }
        size = 0;
    }
}

void replace(student_t *&students, int &size, int index)
{
    std::cout << ASCII_COLOR_GREEN << "Student " << index + 1 << ":" << ASCII_RESET << std::endl;
    students[index] = get_student();
}

bool more_comparator(student_t student_1, student_t student_2, int min_income)
{
    if (student_1.income < 2 * min_income && student_2.income >= 2 * min_income)
        return false;
    if (student_1.income >= 2 * min_income && student_2.income < 2 * min_income)
        return true;
    return student_1.income > student_2.income;
}

void sort(student_t *&students, int size)
{
    int min_income = 0;
    std::string s;
    std::cout << "Min income: ";
    std::getline(std::cin, s);
    if (std::isdigit(s[0]))
        min_income = std::stoi(s);
    for (int i = 1; i < size; i++)
        for (int j = size - i - 1; j < size - 1 && more_comparator(students[j], students[j + 1], min_income); j++)
            std::swap(students[j], students[j + 1]);
}

std::string replace(std::string s, char replaceable, char replacer)
{
    for (char &c : s)
        if (c == replaceable)
            c = replacer;
    return s;
}

void save(student_t *students, int size)
{
    std::fstream file;
    file.open("students.txt", std::ios::out);
    for (int i = 0; i < size; i++)
    {
        std::stringstream ss;
        ss << replace(students[i].full_name, ' ', '_') << ' ' << students[i].group.full << ' ' << students[i].rating << ' ' << students[i].income;
        file << std::setw(MAX_STRING_SIZE * 2) << std::setfill(' ') << std::left << ss.str() << std::endl;
    }
    file.close();
}

void load(student_t *&students, int &size)
{
    std::fstream file;
    file.open("students.txt", std::ios::in);
    if (file.good())
    {
        size = 0;
        std::string line;
        while (std::getline(file, line))
            size++;
        file.clear();
        file.seekg(0, file.beg);
        students = new student_t[size];
        for (int i = 0; i < size; i++)
        {
            std::string full_name, group;
            file >> full_name >> group >> students[i].rating >> students[i].income;
            full_name = replace(full_name, '_', ' ');
            std::strncpy(students[i].full_name, full_name.c_str(), MAX_STRING_SIZE);
            std::strncpy(students[i].group.full, group.c_str(), MAX_GROUP_SIZE);
        }
        file.close();
    }
    else 
        std::cout << ASCII_COLOR_RED << "[*] Save not found!" << ASCII_RESET << std::endl;
}

void file_replace(int index)
{
    std::fstream file;
    file.open("students.txt", std::ios::in | std::ios::out);
    if (file.good())
    {
        int size = 0;
        std::string line;
        while (std::getline(file, line))
            size++;
        file.clear();
        file.seekg(0, file.beg);
        if (0 <= index && index < size)
        {
            std::cout << ASCII_COLOR_GREEN << "Student " << index + 1 << ":" << ASCII_RESET << std::endl;
            student_t student = get_student();
            std::stringstream ss;
            std::stringstream line;
            ss << replace(student.full_name, ' ', '_') << ' ' << student.group.full << ' ' << student.rating << ' ' << student.income;
            line << std::setw(MAX_STRING_SIZE * 2) << std::setfill(' ') << std::left << ss.str() << std::endl;
            file.seekp(index * line.str().size(), file.beg);
            file.write(line.str().c_str(), line.str().size());
        }
        else 
            std::cout << ASCII_COLOR_RED << "[*] Quantity is out!" << ASCII_RESET << std::endl;
        file.close();
    }
    else 
        std::cout << ASCII_COLOR_RED << "[*] Save not found!" << ASCII_RESET << std::endl;
}