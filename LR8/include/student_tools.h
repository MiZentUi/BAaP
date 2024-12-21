#pragma once

#include <cctype>
#include <cstring>

const char ASCII_RESET[] = "\x1b[0m";
const char ASCII_COLOR_RED[] = "\x1b[0;31m";
const char ASCII_COLOR_GREEN[] = "\x1b[0;32m";
const char ASCII_COLOR_YELLOW[] = "\x1b[0;33m";

const char INDENT[] = "    ";

const int MAX_STRING_SIZE = 128;
const int MAX_GROUP_SIZE = 8;

union Group
{
    char full[MAX_GROUP_SIZE]{};
    struct
    {
        char year;
        char faculty;
        char speciality[2];
        char eduction_form;
        char serial_num;
    } 
    codes;
};

struct Student
{
    char full_name[MAX_STRING_SIZE] = " ";
    union Group group;
    double rating;
    int income;
};

typedef struct Student student_t;

extern void input(student_t *&students, int &size, bool add = false);

extern void print(student_t *&students, int size);

extern void search(student_t *students, int size);

extern void delete_student(student_t *&students, int &size, int index);

extern void replace(student_t *&students, int &size, int index);

extern void sort(student_t *&students, int size);

extern void save(student_t *students, int size);

extern void load(student_t *&students, int &size);

extern void file_replace(int index);