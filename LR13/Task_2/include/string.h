#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <memory>

#include "iterator.h"
#include "reverseiterator.h"

class String
{
public:
    using size_type = unsigned long long;
    using CharT = char;
    using iterator = Iterator<CharT>;
    using const_iterator = Iterator<const CharT>;
    using reverse_iterator = ReverseIterator<CharT>;
    using const_reverse_iterator = ReverseIterator<const CharT>;

    static constexpr size_type npos = -1;

private:
    size_type _capacity;
    size_type _size;
    std::unique_ptr<CharT[]> _data;

    template <typename E>
    void swap(E &first, E &second);

public:
    String();
    String(const String &str);
    String(String &&str) noexcept;
    String(size_type size, CharT chr);
    String(const CharT *cstr);
    String(const CharT *cstr, size_type count);
    String(const String &other, size_type pos);
    String(const String &other, size_type pos, size_type count);
    constexpr String(String &&other, size_type pos);
    constexpr String(String &&other, size_type pos, size_type count);
    template <typename InputIt>
    String(InputIt first, InputIt last);
    ~String();

    String &assign(const String &str);
    String &assign(String &&str) noexcept;
    String &assign(size_type size, CharT chr);
    String &assign(const CharT *cstr);
    String &assign(const CharT *cstr, size_type count);
    String &assign(const String &str, size_type pos, size_type count = npos);
    template <class InputIt>
    String &assign(InputIt first, InputIt last);
    String &append(size_type count, CharT chr);
    String &append(const CharT *cstr);
    String &append(const CharT *cstr, size_type count);
    String &append(const String &str);
    String &append(const String &str, size_type pos, size_type count = npos);
    template <class InputIt>
    String &append(InputIt first, InputIt last);
    String &erase(size_type index, size_type count = npos);
    String &insert(size_type index, size_type count, CharT chr);
    String &insert(size_type index, const CharT *cstr);
    String &insert(size_type index, const CharT *cstr, size_type count);
    String &insert(size_type index, const String &str);
    String &insert(size_type index, const String &str, size_type s_index,
                   size_type count = npos);
    String &replace(size_type pos, size_type count, const String &str);
    String &replace(const_iterator first, const_iterator last,
                    const String &str);
    String &replace(size_type pos, size_type count, const String &str,
                    size_type pos2, size_type count2 = npos);
    String &replace(size_type pos, size_type count, const CharT *cstr,
                    size_type count2);
    String &replace(const_iterator first, const_iterator last,
                    const CharT *cstr, size_type count2);
    String &replace(size_type pos, size_type count, const CharT *cstr);
    String &replace(const_iterator first, const_iterator last,
                    const CharT *cstr);
    String &replace(size_type pos, size_type count, size_type count2,
                    CharT chr);
    String &replace(const_iterator first, const_iterator last, size_type count2,
                    CharT chr);
    template <class InputIt>
    String &replace(const_iterator first, const_iterator last, InputIt first2,
                    InputIt last2);
    [[nodiscard]]
    String substr(size_type pos = 0, size_type count = npos) const;
    void clear();
    void pop_back();
    void push_back(CharT chr);
    void reserve(size_type new_cap = 0);
    void resize(size_type size);
    void resize(size_type size, CharT chr);
    void swap(String &other) noexcept;
    void shrink_to_fit();
    [[nodiscard]]
    bool empty() const;
    [[nodiscard]]
    constexpr bool starts_with(CharT chr) const noexcept;
    constexpr bool starts_with(const CharT *cstr) const;
    [[nodiscard]]
    constexpr bool ends_with(CharT chr) const noexcept;
    constexpr bool ends_with(const CharT *cstr) const;
    [[nodiscard]]
    constexpr bool contains(CharT chr) const noexcept;
    constexpr bool contains(const CharT *cstr) const;
    [[nodiscard]]
    int compare(const String &str) const;
    [[nodiscard]]
    int compare(size_type pos1, size_type count1, const String &str) const;
    [[nodiscard]]
    int compare(size_type pos1, size_type count1, const String &str,
                size_type pos2, size_type count2 = npos) const;
    int compare(const CharT *cstr) const;
    int compare(size_type pos1, size_type count1, const CharT *cstr) const;
    int compare(size_type pos1, size_type count1, const CharT *cstr,
                size_type count2) const;
    CharT &at(size_type pos);
    CharT &back();
    CharT &front();
    CharT *data() noexcept;
    [[nodiscard]]
    const CharT &at(size_type pos) const;
    [[nodiscard]]
    const CharT &back() const;
    [[nodiscard]]
    const CharT &front() const;
    [[nodiscard]]
    const CharT *data() const;
    [[nodiscard]]
    const CharT *c_str() const;
    [[nodiscard]]
    size_type capacity() const;
    [[nodiscard]]
    size_type size() const;
    [[nodiscard]]
    size_type length() const;
    [[nodiscard]]
    size_type max_size() const;
    size_type copy(CharT *dest, size_type count, size_type pos = 0) const;
    [[nodiscard]]
    size_type find(const String &str, size_type pos = 0) const;
    size_type find(const CharT *cstr, size_type pos, size_type count) const;
    size_type find(const CharT *cstr, size_type pos = 0) const;
    [[nodiscard]]
    size_type find(CharT chr, size_type pos = 0) const;
    [[nodiscard]]
    size_type rfind(const String &str, size_type pos = npos) const;
    size_type rfind(const CharT *cstr, size_type pos, size_type count) const;
    size_type rfind(const CharT *cstr, size_type pos = npos) const;
    [[nodiscard]]
    size_type rfind(CharT chr, size_type pos = npos) const;
    [[nodiscard]]
    size_type find_first_of(const String &str, size_type pos = 0) const;
    size_type find_first_of(const CharT *cstr, size_type pos,
                            size_type count) const;
    size_type find_first_of(const CharT *cstr, size_type pos = 0) const;
    [[nodiscard]]
    size_type find_first_of(CharT chr, size_type pos = 0) const;
    [[nodiscard]]
    size_type find_first_not_of(const String &str, size_type pos = 0) const;
    size_type find_first_not_of(const CharT *cstr, size_type pos,
                                size_type count) const;
    size_type find_first_not_of(const CharT *cstr, size_type pos = 0) const;
    [[nodiscard]]
    size_type find_first_not_of(CharT chr, size_type pos = 0) const;
    [[nodiscard]]
    size_type find_last_of(const String &str, size_type pos = npos) const;
    size_type find_last_of(const CharT *cstr, size_type pos,
                           size_type count) const;
    size_type find_last_of(const CharT *cstr, size_type pos = npos) const;
    [[nodiscard]]
    size_type find_last_of(CharT chr, size_type pos = npos) const;
    [[nodiscard]]
    size_type find_last_not_of(const String &str, size_type pos = npos) const;
    size_type find_last_not_of(const CharT *cstr, size_type pos,
                               size_type count) const;
    size_type find_last_not_of(const CharT *cstr, size_type pos = npos) const;
    [[nodiscard]]
    size_type find_last_not_of(CharT chr, size_type pos = npos) const;
    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
    iterator insert(const_iterator pos, CharT chr);
    iterator insert(const_iterator pos, size_type count, CharT chr);
    template <class InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last);
    iterator begin();
    iterator end();
    [[nodiscard]]
    const_iterator begin() const;
    [[nodiscard]]
    const_iterator cbegin() const noexcept;
    [[nodiscard]]
    const_iterator end() const;
    [[nodiscard]]
    const_iterator cend() const noexcept;
    reverse_iterator rbegin();
    reverse_iterator rend();
    [[nodiscard]]
    const_reverse_iterator rbegin() const;
    [[nodiscard]]
    const_reverse_iterator crbegin() const noexcept;
    [[nodiscard]]
    const_reverse_iterator crend() const noexcept;

    String &operator=(const String &string);
    String &operator=(String &&string) noexcept;
    String &operator=(const CharT *cstr);
    String &operator=(CharT chr);
    String operator+=(const String &str);
    String operator+=(CharT chr);
    String operator+=(const CharT *cstr);
    bool operator==(const String &str) const;
    bool operator==(const CharT *cstr) const;
    bool operator!=(const String &str) const;
    bool operator!=(const CharT *cstr) const;
    CharT &operator[](size_type pos);
    const CharT &operator[](size_type pos) const;
};

String operator+(const String &lhs, const String &rhs);
String operator+(const String &lhs, const String::CharT *rhs);
String operator+(const String &lhs, String::CharT rhs);
String operator+(const String::CharT *lhs, const String &rhs);
String operator+(String::CharT lhs, const String &rhs);
String operator+(String &&lhs, String &&rhs);
String operator+(String &&lhs, const String &rhs);
String operator+(String &&lhs, const String::CharT *rhs);
String operator+(String &&lhs, String::CharT rhs);
String operator+(const String &lhs, String &&rhs);
String operator+(const String::CharT *lhs, String &&rhs);
String operator+(String::CharT lhs, String &&rhs);
String operator""_s(const char *cstr, size_t len);
std::ostream &operator<<(std::ostream &os, const String &str);
std::istream &operator>>(std::istream &is, String &str);

extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memmove(void *dest, const void *src, size_t count);
extern void *memset(void *dest, int chr, size_t count);
extern char *strcpy(char *dest, const char *src);
extern char *strncpy(char *dest, const char *src, size_t count);
extern char *strcat(char *dest, const char *src);
extern char *strncat(char *dest, const char *src, size_t count);
extern char *strtok(char *str, const char *delim);
extern char *strerror(int errnum);
extern int memcmp(const void *lhs, const void *rhs, size_t count);
extern int strcmp(const char *lhs, const char *rhs);
extern int strncmp(const char *lhs, const char *rhs, size_t count);
extern int strcoll(const char *lhs, const char *rhs);
extern size_t strxfrm(char *dest, const char *src, size_t count);
extern size_t strlen(const char *str);
extern size_t strspn(const char *dest, const char *src);
extern size_t strcspn(const char *dest, const char *src);

const size_t SYS_ERRLIST_SIZE = 500;

template <typename InputIt>
String::String(InputIt first, InputIt last)
    : _capacity(first - last > 15 ? first - labs : 15),
      _size(first - last),
      _data(new CharT[_capacity]{})
{
    for (size_type i = 0; i < _size; i++)
    {
        _data[i] = first + i;
    }
}

template <typename E>
void String::swap(E &first, E &second)
{
    E temp = first;
    first = second;
    second = temp;
}

template <class InputIt>
String &String::assign(InputIt first, InputIt last)
{
    *this = String(first, last);
    return *this;
}

template <class InputIt>
String &String::append(InputIt first, InputIt last)
{
    while (_size + first - last + 1 < _capacity)
    {
        reserve(_capacity * 2);
    }
    for (size_type i = _size; i < _size + first - last; i++)
    {
        _data[i] = first + i;
    }
    _size += first - last;
    return *this;
}

template <class InputIt>
String &String::replace(const_iterator first, const_iterator last,
                        InputIt first2, InputIt last2)
{
    erase(first - cbegin(), last - first);
    insert(first2, last2);
    return *this;
}

constexpr bool String::starts_with(CharT chr) const noexcept
{
    if (empty())
    {
        return false;
    }
    return chr == _data[0];
}

constexpr bool String::starts_with(const CharT *cstr) const
{
    if (strlen(cstr) > _size)
    {
        return false;
    }
    for (size_type i = 0; i < strlen(cstr); i++)
    {
        if (cstr[i] != _data[i])
        {
            return false;
        }
    }
    return true;
}

constexpr bool String::ends_with(CharT chr) const noexcept
{
    if (empty())
    {
        return false;
    }
    return chr == _data[_size - 1];
}

constexpr bool String::ends_with(const CharT *cstr) const
{
    if (strlen(cstr) > _size)
    {
        return false;
    }
    for (size_type i = 0; i < strlen(cstr); i++)
    {
        if (cstr[i] != _data[_size - strlen(cstr) + i])
        {
            return false;
        }
    }
    return true;
}

constexpr bool String::contains(CharT chr) const noexcept
{
    return find(chr) != npos;
}

constexpr bool String::contains(const CharT *cstr) const
{
    return find(cstr) != npos;
}

template <class InputIt>
String::iterator String::insert(const_iterator pos, InputIt first, InputIt last)
{
    while (first < last)
    {
        insert(pos, *first);
        first++;
    }
}

#endif  // STRING_H