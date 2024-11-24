#include "tools.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <ostream>
#include <stdexcept>

PairList::PairList() {}

PairList::~PairList()
{
    delete[] pair_list;
    pair_list = nullptr;
}

void PairList::add_pair(int key, int value)
{
    Pair *new_pair_list = new Pair[len + 1];
    for (int i = 0; i < len; i++)
        new_pair_list[i] = pair_list[i];
    Pair pair;
    pair.key = key;
    pair.value = value;
    new_pair_list[len] = pair;
    if (pair_list != nullptr)
        delete[] pair_list;
    pair_list = new_pair_list;
    len++;
}

bool PairList::check_pair_exist(int key, int value)
{
    for (int i = 0; i < len; i++)
        if (pair_list[i].key == key && pair_list[i].value == value)
            return true;
    return false;
}

int PairList::count_by_key(int key)
{
    int count = 0;
    for (int i = 0; i < len; i++)
        if (pair_list[i].key == key)
            count++;
    return count;
}

int PairList::size() { return len; }

Pair &PairList::operator[](const int index) { return pair_list[index]; }

IntList::IntList() {}

IntList::~IntList() {}

void IntList::add(int value)
{
    list[len] = value;
    len++;
}

int IntList::size() { return len; }

int &IntList::operator[](const int index) { return list[index]; }

IntListList::IntListList() {}

IntListList::~IntListList()
{
    for (int i = 0; i < len; i++)
        list[i].~IntList();
    delete[] list;
    list = nullptr;
}

void IntListList::add(IntList value)
{
    IntList *new_list = new IntList[len + 1];
    for (int i = 0; i < len; i++)
        new_list[i] = list[i];
    for (int i = 0; i < value.size(); i++)
    {
        new_list[len].add(value[i]);
    }
    if (list != nullptr)
        delete[] list;
    list = new_list;
    len++;
}

int IntListList::size() { return len; }

IntList &IntListList::operator[](const int index)
{
    if (index >= len)
        throw std::out_of_range("");
    return list[index];
}

void dfs(int vertex, int vertex_count, PairList &pair_list, IntListList &paths_list, bool *visited, int index = 0)
{
    if (visited[vertex])
        return;
    if (index > paths_list.size() - 1)
        paths_list.add(IntList());
    paths_list[index].add(vertex);
    int count = pair_list.count_by_key(vertex);
    if (count > 1)
        for (int i = 0; i < count - 1; i++)
            paths_list.add(paths_list[index]);
    visited[vertex] = true;
    int current_index = index;
    for (int i = 0; i < pair_list.size(); i++)
        if (pair_list[i].key == vertex)
            dfs(pair_list[i].value, vertex_count, pair_list, paths_list, visited, current_index++);
}

void get_all_paths(char **words, int words_count, IntListList &paths_list)
{
    PairList pair_list;
    for (int i = 0; i < words_count; i++)
        for (int j = 0; j < words_count; j++)
            if (i != j && tolower(words[i][strlen(words[i]) - 1]) == tolower(words[j][0]) && !pair_list.check_pair_exist(i, j))
                pair_list.add_pair(i, j);
    bool *visited = new bool[words_count]{};
    for (int i = 0; i < words_count; i++)
    {
        dfs(i, words_count, pair_list, paths_list, visited, paths_list.size());
        memset(visited, 0, words_count);
    }
    delete[] visited;
    visited = nullptr;
}

void get_max_path(IntListList &paths_list, IntList &max_path)
{
    int max_path_index = 0, max_path_len = 0;
    for (int i = 0; i < paths_list.size(); i++)
    {
        if (paths_list[i].size() > max_path_len)
        {
            max_path_len = paths_list[i].size();
            max_path_index = i;
        }
    }
    IntList path = paths_list[max_path_index];
    for (int i = 0; i < path.size(); i++)
        max_path.add(path[i]);
}

String::String() {}

String::String(const char *s) { strlcpy(this->s, s, max_size); }

String::~String()
{
    delete[] s;
    s = nullptr;
}

int String::size() { return strlen(s); }

char *String::c_str() { return s; }

int String::get_max_size() { return max_size; }

void String::trim()
{
    for (int i = strlen(s) - 1; s[0] != '\0' && isspace(s[i]); i--)
        s[i] = '\0';
}

void String::operator=(const char *s) { strlcpy(this->s, s, max_size); }

char &String::operator[](const int index) { return s[index]; }

std::ostream &operator<<(std::ostream &os, const String &s)
{
    os << s.s;
    return os;
}

void String::read()
{
    char c;
    int i;
    for (i = 0; i < max_size - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        if (!(isspace(c) && !strlen(s)))
            s[i] = c;
        else
            i--;
    s[i] = '\0';
}

void String::split(char **items, int count, const char *delimeter)
{
    char *token = strtok(s, delimeter);
    for (int i = 0; i < count; i++)
    {
        if (token != nullptr)
            strlcpy(items[i], token, max_size);
        token = strtok(NULL, delimeter);
    }
}

void String::get_max_word(int &serial, int &index)
{
    int max_word_size = 0, max_word_serial = 0, max_word_index = 0,
        current_word_size = 0, current_word_serial = 0, current_word_index = 0;
    if (isalnum(s[0]))
        current_word_serial++;
    for (int i = 0; i < max_size && s[i] != '\0'; i++)
    {
        if (isalnum(s[i]))
        {
            if ((i && s[i - 1] == ' ') || (i + 1 < max_size && s[i + 1] == '\0'))
            {
                if ((s[i + 1] == '\0' && !i) || (s[i + 1] == '\0' && s[i - 1] != ' '))
                    current_word_size++;
                if (current_word_size > max_word_size)
                {
                    max_word_size = current_word_size;
                    max_word_serial = current_word_serial;
                    max_word_index = current_word_index;
                }
                current_word_serial++;
                current_word_size = 0;
                current_word_index = i;
            }
            current_word_size++;
        }
    }
    serial = max_word_serial;
    index = max_word_index;
}

void String::get_chars(String &chars)
{
    memset(chars.c_str(), 0, max_size);
    int char_index = 0;
    for (int i = 0; i < max_size && s[i] != '\0'; i++)
    {
        bool exists = false;
        for (int j = 0; j < max_size - 1 && chars[j] != '\0'; j++)
            if (chars[j] == s[i])
                exists = true;
        if (!exists)
        {
            chars[char_index] = s[i];
            char_index++;
        }
    }
}

void String::get_sorted_line(String &result)
{
    if (s[0] == '\0')
    {
        result[0] = '\0';
        return;
    }
    int words_count = std::count(s, s + strlen(s), ' ') + 1;
    char **words = new char *[words_count];
    for (int i = 0; i < words_count; i++)
        words[i] = new char[max_size];
    split(words, words_count, " ");
    IntListList paths_list;
    get_all_paths(words, words_count, paths_list);
    IntList max_path;
    get_max_path(paths_list, max_path);
    result[0] = '\0';
    for (int i = 0; i < max_path.size(); i++)
    {
        strlcat(result.c_str(), words[max_path[i]], max_size);
        if (i + 1 != max_path.size())
            strlcat(result.c_str(), " ", max_size);
    }
    for (int i = 0; i < words_count; i++)
    {
        if (words[i] != nullptr)
        {
            delete[] words[i];
            words[i] = nullptr;
        }
    }
    if (words != nullptr)
    {
        delete[] words;
        words = nullptr;
    }
}