#include "../include/string.h"

String::String() : _capacity(15), _size(0), _data(new CharT[_capacity + 1]{}) {}

String::String(const String &str)
    : _capacity(str._capacity),
      _size(str._size),
      _data(new CharT[_capacity + 1]{})
{
    memcpy(_data.get(), str._data.get(), _size * sizeof(CharT));
}

String::String(String &&str) noexcept
    : _capacity(str._capacity), _size(str._size), _data(std::move(str._data))
{
    str = String();
}

String::String(size_type size, CharT chr)
    : _capacity(size > 15 ? size : 15),
      _size(size),
      _data(new CharT[_capacity + 1]{})
{
    for (size_type i = 0; i < _size; i++)
    {
        _data[i] = chr;
    }
}

String::String(const CharT *cstr)
    : _capacity(strlen(cstr) > 15 ? strlen(cstr) : 15),
      _size(strlen(cstr)),
      _data(new CharT[_capacity]{})
{
    memcpy(_data.get(), cstr, strlen(cstr) * sizeof(CharT));
}

String::String(const CharT *cstr, size_type count)
    : _capacity(count > 15 ? count : 15),
      _size(count),
      _data(new CharT[_capacity]{})
{
    memcpy(_data.get(), cstr, count);
}

String::String(const String &other, size_type pos)
    : _capacity(other._size - pos > 15 ? other._size - pos : 15),
      _size(other._size - pos),
      _data(new CharT[_capacity]{})
{
    memcpy(_data.get() + pos, other._data.get() + pos, other._size - pos);
}

String::String(const String &other, size_type pos, size_type count)
    : _capacity(count > 15 ? count : 15),
      _size(count),
      _data(new CharT[_capacity]{})
{
    memcpy(_data.get(), other._data.get() + pos, count);
}

String::~String()
{
    _capacity = 0;
    _size = 0;
    _data.reset();
}

String &String::assign(const String &str)
{
    *this = String(str);
    return *this;
}

String &String::assign(String &&str) noexcept
{
    *this = std::move(str);
    return *this;
}

String &String::assign(size_type size, CharT chr)
{
    *this = String(size, chr);
    return *this;
}

String &String::assign(const CharT *cstr)
{
    *this = String(cstr);
    return *this;
}

String &String::assign(const CharT *cstr, size_type count)
{
    *this = String(cstr, count);
    return *this;
}

String &String::assign(const String &str, size_type pos, size_type count)
{
    *this = count == npos ? String(str, pos) : String(str, pos, count);
    return *this;
}

String &String::append(size_type count, CharT chr)
{
    while (_size + count > _capacity)
    {
        reserve(_capacity * 2);
    }
    for (size_type i = _size; i < _size + count; i++)
    {
        _data[i] = chr;
    }
    _size += count;
    return *this;
}

String &String::append(const CharT *cstr) { return append(cstr, strlen(cstr)); }

String &String::append(const CharT *cstr, size_type count)
{
    while (_size + count > _capacity)
    {
        reserve(_capacity * 2);
    }
    memcpy(_data.get() + _size, cstr, count);
    _size += count;
    return *this;
}

String &String::append(const String &str) { return append(str, 0, str.size()); }

String &String::append(const String &str, size_type pos, size_type count)
{
    if (count == npos)
    {
        count = str._size - pos;
    }
    while (_size + count > _capacity)
    {
        reserve(_capacity * 2);
    }
    memcpy(_data.get() + _size, str._data.get() + pos, count);
    _size += count;
    return *this;
}

String &String::erase(size_type index, size_type count)
{
    if (count == npos)
    {
        count = 1;
    }
    memcpy(_data.get() + index, _data.get() + index + count,
           (_size - index - count) * sizeof(CharT));
    _size -= count;
    memset(_data.get() + _size, 0, _capacity - _size + 1);
    return *this;
}

String &String::insert(size_type index, size_type count, CharT chr)
{
    while (_size + count > _capacity)
    {
        reserve(_capacity * 2);
    }
    memmove(_data.get() + index + count, _data.get() + index,
            (_size - index) * sizeof(CharT));
    for (size_type i = index; i < count; i++)
    {
        _data[i] = chr;
    }
    _size += count;
    return *this;
}

String &String::insert(size_type index, const CharT *cstr)
{
    return insert(index, cstr, strlen(cstr));
}

String &String::insert(size_type index, const CharT *cstr, size_type count)
{
    while (_size + count > _capacity)
    {
        reserve(_capacity * 2);
    }  // qwttert
    memmove(_data.get() + index + count, _data.get() + index,
            (_size - index) * sizeof(CharT));
    memcpy(_data.get() + index, cstr, count);
    _size += count;
    return *this;
}

String &String::insert(size_type index, const String &str)
{
    return insert(index, str._data.get(), str._size);
}

String &String::insert(size_type index, const String &str, size_type s_index,
                       size_type count)
{
    if (count == npos)
    {
        count = str._size - s_index;
    }
    return insert(index, str._data.get() + s_index, count);
}

String &String::replace(size_type pos, size_type count, const String &str)
{
    erase(pos, count > _size - pos ? _size - pos : count);
    insert(pos, str);
    return *this;
}

String &String::replace(const_iterator first, const_iterator last,
                        const String &str)
{
    erase(first - cbegin(), last - first);
    insert(first - cbegin(), str);
    return *this;
}

String &String::replace(size_type pos, size_type count, const String &str,
                        size_type pos2, size_type count2)
{
    erase(pos, count);
    insert(pos, str, pos2, count2);
    return *this;
}

String &String::replace(size_type pos, size_type count, const CharT *cstr,
                        size_type count2)
{
    erase(pos, count);
    insert(pos, cstr, count2);
    return *this;
}

String &String::replace(const_iterator first, const_iterator last,
                        const CharT *cstr, size_type count2)
{
    erase(first - cbegin(), last - first);
    insert(first - cbegin(), cstr, count2);
    return *this;
}

String &String::replace(size_type pos, size_type count, const CharT *cstr)
{
    erase(pos, count);
    insert(pos, cstr);
    return *this;
}

String &String::replace(const_iterator first, const_iterator last,
                        const CharT *cstr)
{
    erase(first - cbegin(), last - first);
    insert(first - cbegin(), cstr);
    return *this;
}

String &String::replace(size_type pos, size_type count, size_type count2,
                        CharT chr)
{
    erase(pos, count);
    insert(pos, count2, chr);
    return *this;
}

String &String::replace(const_iterator first, const_iterator last,
                        size_type count2, CharT chr)
{
    erase(first - cbegin(), last - first);
    insert(first, count2, chr);
    return *this;
}

String String::substr(size_type pos, size_type count) const
{
    return {*this, pos, count};
}

void String::clear() { erase(begin(), end()); }

void String::pop_back() { erase(end() - 1); }

void String::push_back(CharT chr)
{
    while (_size > _capacity)
    {
        reserve(_capacity * 2);
    }
    _data[_size] = chr;
    _size++;
}

void String::reserve(size_type new_cap)
{
    if (new_cap > _capacity)
    {
        auto *new_data = new CharT[new_cap + 1]{};
        for (size_type i = 0; i < _size; i++)
        {
            new_data[i] = _data[i];
        }
        _data.reset(new_data);
        _capacity = new_cap;
    }
}

void String::resize(size_type size) { resize(size, CharT()); }

void String::resize(size_type size, CharT chr)
{
    while (_size > _capacity)
    {
        reserve(_capacity * 2);
    }
    for (size_type i = _size; i < size; i++)
    {
        _data[i] = chr;
    }
    _data[size] = 0;
    _size = size;
}

void String::swap(String &other) noexcept
{
    swap(_capacity, other._capacity);
    swap(_size, other._size);
    CharT *temp = _data.get();
    _data.reset(other._data.get());
    other._data.reset(temp);
}

void String::shrink_to_fit()
{
    auto *new_data = new CharT[_size + 1]{};
    for (size_type i = 0; i < _size; i++)
    {
        new_data[i] = _data[i];
    }
    _data.reset(new_data);
    _capacity = _size;
}

bool String::empty() const { return begin() == end(); }

int String::compare(const String &str) const
{
    return compare(0, _size, str, 0);
}

int String::compare(size_type pos1, size_type count1, const String &str) const
{
    return compare(pos1, count1, str, str._size);
}

int String::compare(size_type pos1, size_type count1, const String &str,
                    size_type pos2, size_type count2) const
{
    if (count1 > _size + pos1)
    {
        count1 = _size;
    }
    if (count2 > str._size + pos2)
    {
        count2 = str._size;
    }
    size_type rlen = count1 > count2 ? count2 : count1;
    for (size_type i = 0; i < rlen; i++)
    {
        if (_data[pos1 + i] < str[i])
        {
            return -1;
        }
        if (_data[pos1 + i] < str[i])
        {
            return 1;
        }
    }
    if (count1 < count2)
    {
        return -1;
    }
    if (count1 > count2)
    {
        return 1;
    }
    return 0;
}

int String::compare(const CharT *cstr) const
{
    return compare(0, _size, cstr, strlen(cstr));
}

int String::compare(size_type pos1, size_type count1, const CharT *cstr) const
{
    return compare(pos1, count1, cstr, strlen(cstr));
}

int String::compare(size_type pos1, size_type count1, const CharT *cstr,
                    size_type count2) const
{
    if (count1 > _size + pos1)
    {
        count1 = _size;
    }
    size_type rlen = count1 > count2 ? count2 : count1;
    for (size_type i = 0; i < rlen; i++)
    {
        if (_data[pos1 + i] < cstr[i])
        {
            return -1;
        }
        if (_data[pos1 + i] < cstr[i])
        {
            return 1;
        }
    }
    if (count1 < count2)
    {
        return -1;
    }
    if (count1 > count2)
    {
        return 1;
    }
    return 0;
}

String::CharT &String::at(size_type pos) { return _data[pos]; }

String::CharT &String::back() { return _data[_size - 1]; }

String::CharT &String::front() { return _data[0]; }

String::CharT *String::data() noexcept { return _data.get(); }

const String::CharT &String::at(size_type pos) const { return _data[pos]; }

const String::CharT &String::back() const { return _data[_size - 1]; }

const String::CharT &String::front() const { return _data[0]; }

const String::CharT *String::data() const { return _data.get(); }

const String::CharT *String::c_str() const { return _data.get(); }

String::size_type String::capacity() const { return _capacity; }

String::size_type String::size() const { return _size; }

String::size_type String::length() const { return _size; }

String::size_type String::max_size() const { return npos / sizeof(CharT); }

String::size_type String::copy(CharT *dest, size_type count,
                               size_type pos) const
{
    if (pos > _size)
    {
        return 0;
    }
    if (count > npos)
    {
        count = _size;
    }
    for (size_type i = 0; i < count; i++)
    {
        dest[i] = _data[pos + i];
    }
    return count;
}

String::size_type String::find(const String &str, size_type pos) const
{
    if (pos <= _size + str._size && (str.empty() || pos < _size))
    {
        if (str.empty() && pos <= _size)
        {
            return pos;
        }
        size_type index = -1;
        while ((index = find(str._data[0])) < _size - str._size)
        {
            if (compare(index, str._size, str) == 0)
            {
                return index;
            }
        }
    }
    return npos;
}

String::size_type String::find(const CharT *cstr, size_type pos,
                               size_type count) const
{
    if (pos <= _size + count && (count == 0 || pos < _size))
    {
        if (count == 0 && pos <= _size)
        {
            return pos;
        }
        size_type index = -1;
        while ((index = find(cstr[0])) < _size - count)
        {
            if (compare(index, count, cstr) == 0)
            {
                return index;
            }
        }
    }
    return npos;
}

String::size_type String::find(const CharT *cstr, size_type pos) const
{
    return find(cstr, pos, strlen(cstr));
}

String::size_type String::find(CharT chr, size_type pos) const
{
    if (pos <= _size + 1)
    {
        while (pos < _size)
        {
            if (_data[pos++] == chr)
            {
                return pos - 1;
            }
        }
    }
    return npos;
}

String::size_type String::rfind(const String &str, size_type pos) const
{
    if (!empty())
    {
        if (str.empty())
        {
            if (pos < _size)
            {
                return pos;
            }
            return _size;
        }
        if (pos >= _size)
        {
            pos = _size - 1;
        }
        size_type index = -1;
        while ((index = rfind(str._data[0], pos)) >= 0 && index < _size)
        {
            if (compare(index, str._size, str) == 0)
            {
                return index;
            }
        }
    }
    return npos;
}

String::size_type String::rfind(const CharT *cstr, size_type pos,
                                size_type count) const
{
    if (!empty())
    {
        if (strlen(cstr) == 0 || count == 0)
        {
            if (pos < _size)
            {
                return pos;
            }
            return _size;
        }
        if (pos >= _size)
        {
            pos = _size - 1;
        }
        size_type index = -1;
        while ((index = rfind(cstr[0], pos)) >= 0 && index < _size)
        {
            if (compare(index, count, cstr) == 0)
            {
                return index;
            }
        }
    }
    return npos;
}

String::size_type String::rfind(const CharT *cstr, size_type pos) const
{
    return rfind(cstr, pos, strlen(cstr));
}

String::size_type String::rfind(CharT chr, size_type pos) const
{
    if (pos >= _size)
    {
        pos = empty() ? _size : _size - 1;
    }
    while (pos > 0)
    {
        if (_data[pos--] == chr)
        {
            return pos + 1;
        }
    }
    if (_data[0] == chr)
    {
        return 0;
    }
    return npos;
}

String::size_type String::find_first_of(const String &str, size_type pos) const
{
    while (pos < _size)
    {
        if (str.contains(_data[pos++]))
        {
            return pos - 1;
        }
    }
    return npos;
}

String::size_type String::find_first_of(const CharT *cstr, size_type pos,
                                        size_type count) const
{
    String scstr(cstr);
    for (size_type i = pos; i < pos + count; i++)
    {
        if (scstr.contains(_data[i]))
        {
            return i;
        }
    }
    return npos;
}

String::size_type String::find_first_of(const CharT *cstr, size_type pos) const
{
    return find_first_of(cstr, pos, strlen(cstr));
}

String::size_type String::find_first_of(CharT chr, size_type pos) const
{
    return find(chr, pos);
}

String::size_type String::find_first_not_of(const String &str,
                                            size_type pos) const
{
    while (pos < _size)
    {
        if (!str.contains(_data[pos++]))
        {
            return pos - 1;
        }
    }
    return npos;
}

String::size_type String::find_first_not_of(const CharT *cstr, size_type pos,
                                            size_type count) const
{
    String scstr(cstr);
    for (size_type i = pos; i < pos + count; i++)
    {
        if (!scstr.contains(_data[i]))
        {
            return i;
        }
    }
    return npos;
}

String::size_type String::find_first_not_of(const CharT *cstr,
                                            size_type pos) const
{
    return find_first_not_of(cstr, pos, strlen(cstr));
}

String::size_type String::find_first_not_of(CharT chr, size_type pos) const
{
    while (pos < _size)
    {
        if (_data[pos++] != chr)
        {
            return pos - 1;
        }
    }
    return npos;
}

String::size_type String::find_last_of(const String &str, size_type pos) const
{
    if (pos == npos)
    {
        pos = _size - 1;
    }
    while (pos > 0)
    {
        if (str.contains(_data[pos--]))
        {
            return pos + 1;
        }
    }
    if (str.contains(_data[0]))
    {
        return 0;
    }
    return npos;
}

String::size_type String::find_last_of(const CharT *cstr, size_type pos,
                                       size_type count) const
{
    String scstr(cstr);
    for (size_type i = pos + count; i > 0; i--)
    {
        if (scstr.contains(_data[i]))
        {
            return i;
        }
    }
    if (scstr.contains(_data[0]))
    {
        return 0;
    }
    return npos;
}

String::size_type String::find_last_of(const CharT *cstr, size_type pos) const
{
    return find_last_of(cstr, pos, strlen(cstr));
}

String::size_type String::find_last_of(CharT chr, size_type pos) const
{
    if (pos == npos)
    {
        pos = _size - 1;
    }
    while (pos > 0)
    {
        if (_data[pos--] == chr)
        {
            return pos + 1;
        }
    }
    if (_data[0] == chr)
    {
        return 0;
    }
    return npos;
}

String::size_type String::find_last_not_of(const String &str,
                                           size_type pos) const
{
    if (pos == npos)
    {
        pos = _size - 1;
    }
    while (pos > 0)
    {
        if (!str.contains(_data[pos--]))
        {
            return pos + 1;
        }
    }
    if (!str.contains(_data[0]))
    {
        return 0;
    }
    return npos;
}

String::size_type String::find_last_not_of(const CharT *cstr, size_type pos,
                                           size_type count) const
{
    String scstr(cstr);
    for (size_type i = pos + count; i > 0; i--)
    {
        if (scstr.contains(_data[i]))
        {
            return i;
        }
    }
    if (scstr.contains(_data[0]))
    {
        return 0;
    }
    return npos;
}

String::size_type String::find_last_not_of(const CharT *cstr,
                                           size_type pos) const
{
    return find_last_not_of(cstr, pos, strlen(cstr));
}

String::size_type String::find_last_not_of(CharT chr, size_type pos) const
{
    if (pos == npos)
    {
        pos = _size - 1;
    }
    while (pos > 0)
    {
        if (_data[pos--] != chr)
        {
            return pos + 1;
        }
    }
    if (_data[0] != chr)
    {
        return 0;
    }
    return npos;
}

String::iterator String::erase(iterator position)
{
    return erase(position, position + 1);
}

String::iterator String::erase(iterator first, iterator last)
{
    if (begin() <= first && first <= end() && first < last && last <= end())
    {
        _size -= last - first;
        while (last < end())
        {
            new (first.base()) CharT(*last);
            *first.base() = *last;
            first++;
            last++;
        }
    }
    memset(_data.get() + _size, 0, _capacity - _size + 1);
    return last;
}

String::iterator String::insert(const_iterator pos, CharT chr)
{
    return insert(pos, 1, chr);
}

String::iterator String::insert(const_iterator pos, size_type count, CharT chr)
{
    _size += count;
    size_type index = pos - cbegin();
    while (_size + count > _capacity)
    {
        reserve(_capacity * 2);
    }
    memmove((void *)(_data.get() + index + count), _data.get() + index,
            (_size - count - index) * sizeof(CharT));
    for (size_type i = index; i < index + count; i++)
    {
        _data[i] = chr;
    }
    return {_data.get() + index};
}

String::iterator String::begin() { return {_data.get()}; }

String::iterator String::end() { return {_data.get() + _size}; }

String::const_iterator String::begin() const { return {_data.get()}; }

String::const_iterator String::cbegin() const noexcept { return {_data.get()}; }

String::const_iterator String::end() const { return {_data.get() + _size}; }

String::const_iterator String::cend() const noexcept
{
    return {_data.get() + _size};
}

String::reverse_iterator String::rbegin() { return {_data.get() + _size}; }

String::reverse_iterator String::rend() { return {_data.get()}; }

String::const_reverse_iterator String::rbegin() const { return crbegin(); }

String::const_reverse_iterator String::crbegin() const noexcept
{
    return {_data.get() + _size};
}

String::const_reverse_iterator String::crend() const noexcept
{
    return {_data.get()};
}

String &String::operator=(const String &string)
{
    if (this != &string)
    {
        clear();
        _size = string._size;
        while (_size > _capacity)
        {
            reserve(_capacity * 2);
        }
        memcpy(_data.get(), string._data.get(), _size * sizeof(CharT));
    }
    return *this;
}

String &String::operator=(String &&string) noexcept
{
    if (this != &string)
    {
        clear();
        _data.reset(string._data.get());
        _capacity = string._capacity;
        _size = string._size;
        while (_size > _capacity)
        {
            reserve(_capacity * 2);
        }
        string.clear();
        string._capacity = 15;
        string._data.reset(new (std::nothrow) CharT[string._capacity + 1]);
    }
    return *this;
}

String &String::operator=(const CharT *cstr)
{
    clear();
    _size = strlen(cstr);
    while (_size > _capacity)
    {
        reserve(_capacity * 2);
    }
    memcpy(_data.get(), cstr, strlen(cstr) * sizeof(CharT));
    return *this;
}

String &String::operator=(CharT chr)
{
    clear();
    _size = 1;
    _data[0] = chr;
    return *this;
}

String String::operator+=(const String &str) { return append(str); }

String String::operator+=(CharT chr)
{
    push_back(chr);
    return *this;
}

String String::operator+=(const CharT *cstr) { return append(cstr); }

bool String::operator==(const String &str) const { return compare(str) == 0; }

bool String::operator==(const CharT *cstr) const { return compare(cstr) == 0; }

bool String::operator!=(const String &str) const { return !(*this == str); }

bool String::operator!=(const CharT *cstr) const { return !(*this == cstr); }

String::CharT &String::operator[](size_type pos) { return _data[pos]; }

const String::CharT &String::operator[](size_type pos) const
{
    return _data[pos];
}

String operator+(const String &lhs, const String &rhs)
{
    String res = lhs;
    res.append(rhs);
    return lhs;
}

String operator+(const String &lhs, const String::CharT *rhs)
{
    String res = lhs;
    res.append(rhs);
    return lhs;
}

String operator+(const String &lhs, String::CharT rhs)
{
    String res = lhs;
    res.push_back(rhs);
    return res;
}

String operator+(const String::CharT *lhs, const String &rhs)
{
    String res = rhs;
    res.insert(0, lhs);
    return res;
}

String operator+(String::CharT lhs, const String &rhs)
{
    String res = rhs;
    res.insert(res.cbegin(), lhs);
    return res;
}

String operator+(String &&lhs, String &&rhs)
{
    lhs.append(std::move(rhs));
    return std::move(lhs);
}

String operator+(String &&lhs, const String &rhs)
{
    lhs.append(rhs);
    return std::move(lhs);
}

String operator+(String &&lhs, const String::CharT *rhs)
{
    lhs.append(rhs);
    return std::move(lhs);
}

String operator+(String &&lhs, String::CharT rhs)
{
    lhs.push_back(rhs);
    return std::move(lhs);
}

String operator+(const String &lhs, String &&rhs)
{
    rhs.insert(0, lhs);
    return std::move(rhs);
}

String operator+(const String::CharT *lhs, String &&rhs)
{
    rhs.insert(0, lhs);
    return std::move(rhs);
}

String operator+(String::CharT lhs, String &&rhs)
{
    rhs.insert(rhs.cbegin(), lhs);
    return std::move(rhs);
}

String operator""_s(const char *cstr, size_t len) { return {cstr, len}; }

std::ostream &operator<<(std::ostream &ost, const String &str)
{
    for (char chr : str)
    {
        ost << chr;
    }
    return ost;
}

std::istream &operator>>(std::istream &ist, String &str)
{
    str.clear();
    String::CharT chr = ' ';
    ist >> chr;
    while (chr == ' ')
    {
        str.append(1, chr);
        ist >> chr;
    }
    return ist;
}

void *memcpy(void *dest, const void *src, size_t count)
{
    auto *c_dest = static_cast<unsigned char *>(dest);
    const auto *c_src = static_cast<const unsigned char *>(src);
    while ((bool)count--)
    {
        *c_dest++ = *c_src++;
    }
    return dest;
}

void *memmove(void *dest, const void *src, size_t count)
{
    auto *c_dest = static_cast<unsigned char *>(dest);
    const auto *c_src = static_cast<const unsigned char *>(src);
    auto *arr = new unsigned char[count];
    for (size_t i = 0; i < count; i++)
    {
        arr[i] = c_src[i];
    }
    for (size_t i = 0; i < count; i++)
    {
        c_dest[i] = arr[i];
    }
    delete[] arr;
    return dest;
}

void *memset(void *dest, int chr, size_t count)
{
    auto *c_dest = static_cast<unsigned char *>(dest);
    auto value = static_cast<unsigned char>(chr);
    while ((bool)count--)
    {
        *c_dest++ = value;
    }
    return dest;
}

char *strcpy(char *dest, const char *src)
{
    return strncpy(dest, src, strlen(src) + 1);
}

char *strncpy(char *dest, const char *src, size_t count)
{
    size_t size = strlen(src) + 1;
    for (size_t i = 0; i < count; i++)
    {
        if (i <= size)
        {
            dest[i] = src[i];
        }
        else
        {
            dest[i] = 0;
        }
    }
    return dest;
}

char *strcat(char *dest, const char *src)
{
    return strncat(dest, src, strlen(src) + 1);
}

char *strncat(char *dest, const char *src, size_t count)
{
    size_t dest_len = strlen(dest);
    size_t src_size = strlen(src) + 1;
    for (size_t i = 0; i < count; i++)
    {
        if (i <= src_size)
        {
            dest[dest_len + i] = src[i];
        }
        else
        {
            dest[i] = 0;
        }
    }
    return dest;
}

char *strtok(char *str, const char *delim)
{
    static char *buffer;
    if (str != nullptr)
    {
        buffer = str;
    }
    buffer += strspn(buffer, delim);
    if (*buffer == '\0')
    {
        return nullptr;
    }
    char *const tokenBegin = buffer;
    buffer += strcspn(buffer, delim);
    if (*buffer != '\0')
    {
        *buffer++ = '\0';
    }
    return tokenBegin;
}

const char *sys_errlist[SYS_ERRLIST_SIZE] = {
    [0] = "Operation succeeded",
    [EPERM] = "Operation not permitted",
    [ENOENT] = "No such file or directory",
    [ESRCH] = "No such process",
    [EINTR] = "Interrupted system call",
    [EIO] = "I/O error",
    [ENXIO] = "No such device or address",
    [E2BIG] = "Argument list too long",
    [ENOEXEC] = "Exec format error",
    [EBADF] = "Bad file number",
    [ECHILD] = "No child processes",
    [EAGAIN] = "Try again",
    [ENOMEM] = "Out of memory",
    [EACCES] = "Permission denied",
    [EFAULT] = "Bad address",
    [ENOTBLK] = "Block device required",
    [EBUSY] = "Device or resource busy",
    [EEXIST] = "File exists",
    [EXDEV] = "Cross-device link",
    [ENODEV] = "No such device",
    [ENOTDIR] = "Not a directory",
    [EISDIR] = "Is a directory",
    [EINVAL] = "Invalid argument",
    [ENFILE] = "File table overflow",
    [EMFILE] = "Too many open files",
    [ENOTTY] = "Not a typewriter",
    [ETXTBSY] = "Text file busy",
    [EFBIG] = "File too large",
    [ENOSPC] = "No space left on device",
    [ESPIPE] = "Illegal seek",
    [EROFS] = "Read-only file system",
    [EMLINK] = "Too many links",
    [EPIPE] = "Broken pipe",
    [EDOM] = "Math argument out of domain of func",
    [ERANGE] = "Math result not representable"};

char *strerror(int errnum)
{
    auto *errmsg = new char[100]{};
    if (errnum < SYS_ERRLIST_SIZE && sys_errlist[errnum] != nullptr)
    {
        strcpy(errmsg, sys_errlist[errnum]);
    }
    return errmsg;
}

int memcmp(const void *lhs, const void *rhs, size_t count)
{
    const auto *c_lhs = static_cast<const unsigned char *>(lhs);
    const auto *c_rhs = static_cast<const unsigned char *>(rhs);
    for (size_t i = 0; i < count; i++)
    {
        if (c_lhs[i] < c_rhs[i])
        {
            return -1;
        }
        if (c_lhs[i] < c_rhs[i])
        {
            return 1;
        }
    }
    return 0;
}

int strcmp(const char *lhs, const char *rhs)
{
    return strncmp(lhs, rhs,
                   strlen(lhs) > strlen(rhs) ? strlen(lhs) : strlen(rhs));
}

int strncmp(const char *lhs, const char *rhs, size_t count)
{
    size_t lhs_size = strlen(lhs);
    size_t rhs_size = strlen(rhs);
    for (size_t i = 0; i < count && i < lhs_size && i < rhs_size; i++)
    {
        if (lhs[i] < rhs[i])
        {
            return -1;
        }
        if (lhs[i] < rhs[i])
        {
            return 1;
        }
    }
    return 0;
    if (lhs_size < rhs_size)
    {
        return -1;
    }
    if (lhs_size > rhs_size)
    {
        return 1;
    }
    return 0;
}

int strcoll(const char *lhs, const char *rhs) { return strcmp(lhs, rhs); }

size_t strxfrm(char *dest, const char *src, size_t count)
{
    strncpy(dest, src, count);
    return count;
}

size_t strlen(const char *str)
{
    const char *end = str;
    while (*end != '\0')
    {
        end++;
    }
    return end - str;
}

size_t strspn(const char *dest, const char *src)
{
    char charset[127 * 2 + 2]{};
    for (const auto *chr = src; (bool)*chr; chr++)
    {
        charset[*chr] = 1;
    }
    const auto *start = dest;
    const char *curr = start;
    for (; (bool)charset[*curr] && *curr != '\0'; curr++)
    {
    }
    return curr - start;
}

size_t strcspn(const char *dest, const char *src)
{
    char charset[127 * 2 + 2]{};
    for (const auto *chr = src; (bool)*chr; chr++)
    {
        charset[*chr] = 1;
    }
    const auto *start = dest;
    const char *curr = start;
    for (; (bool)!charset[*curr] && *curr != '\0'; curr++)
    {
    }
    return curr - start;
}