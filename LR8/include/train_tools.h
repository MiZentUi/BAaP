#pragma once

#include <cctype>
#include <cstring>

const char ASCII_RESET[] = "\x1b[0m";
const char ASCII_COLOR_RED[] = "\x1b[0;31m";
const char ASCII_COLOR_GREEN[] = "\x1b[0;32m";
const char ASCII_COLOR_YELLOW[] = "\x1b[0;33m";

const char INDENT[] = "    ";

const int MAX_STRING_SIZE = 128;

union Color
{
    unsigned hex = 0;
    struct
    {
        unsigned B:8;
        unsigned G:8;
        unsigned R:8;
        unsigned A:8;
    } 
    primary;
};

struct Train
{
    char destination[MAX_STRING_SIZE];
    char departure_time[MAX_STRING_SIZE];
    char arrival_time[MAX_STRING_SIZE];
    int available_seats_count = 0;
    union Color color;
};

typedef struct Train train_t;

extern void input(train_t *&trains, int &size, bool add = false);

extern void print(train_t *&trains, int size);

extern void search(train_t *trains, int size);

extern void delete_student(train_t *&trains, int &size, int index);

extern void replace(train_t *&trains, int &size, int index);

extern void sort(train_t *&trains, int size);

extern void save(train_t *trains, int size);

extern void load(train_t *&trains, int &size);

extern void file_replace(int index);