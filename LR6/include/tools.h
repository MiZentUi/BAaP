#pragma once

#include <ostream>

struct Pair
{
    int key;
    int value;
};

class PairList
{
private:
    int len = 0;
    Pair *pair_list = nullptr;

public:
    PairList();

    ~PairList();

    void add_pair(int key, int value);

    bool check_pair_exist(int key, int value);

    int count_by_key(int key);

    int size();

    Pair &operator[](const int index);
};

class IntList
{
private:
    int len = 0;
    int list[128]{};

public:
    IntList();

    ~IntList();

    void add(int value);

    int size();

    int &operator[](const int index);
};

class IntListList
{
private:
    int len = 0;
    IntList *list = nullptr;

public:
    IntListList();

    ~IntListList();

    void add(IntList value);

    int size();

    IntList &operator[](const int index);
};

void dfs(int vertex, int vertex_count, PairList &pair_list, IntListList &paths_list, bool *visited, int index);

void get_all_paths(char **words, int words_count, IntListList &paths_list);

void get_max_path(IntListList &paths_list, IntList &max_path);

class String
{
private:
    static const int max_size = 128;
    char *s = new char[max_size]{};

public:
    String();

    explicit String(const char *);

    ~String();

    int size();

    char *c_str();

    int get_max_size();

    void trim();

    void operator=(const char *s);

    char &operator[](const int index);

    friend std::ostream &operator<<(std::ostream &os, const String &s);

    void read();

    void split(char **items, int count, const char *delimeter);

    void get_max_word(int &serial, int &index);

    void get_chars(String &chars);

    void get_sorted_line(String &result);
};