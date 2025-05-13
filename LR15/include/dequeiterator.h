#ifndef DEQUEITERATOR_H
#define DEQUEITERATOR_H

#include <cmath>
#include <cstddef>

template <typename T, std::size_t BLOCK_SIZE>
class DequeIterator
{
public:
    using size_type = std::size_t;

private:
    size_type map_size;
    size_type _block_index;

    T **map;
    T *_begin;
    T *current;
    T *_end;

    void set_block(size_type index);

public:
    DequeIterator(T **map, size_type map_size);
    DequeIterator(T **map, size_type map_size, T *current);
    DequeIterator(T **map, size_type map_size, T *_begin, T *current, T *_end);
    DequeIterator(const DequeIterator &other) = default;
    DequeIterator(DequeIterator &&) = default;
    ~DequeIterator() = default;

    [[nodiscard]]
    size_type block_index() const;
    T *begin() const;
    T *base() const;
    T *end() const;

    DequeIterator<T, BLOCK_SIZE> &operator=(const DequeIterator &other);
    DequeIterator<T, BLOCK_SIZE> &operator=(DequeIterator &&other) = default;
    DequeIterator<T, BLOCK_SIZE> &operator++();
    DequeIterator<T, BLOCK_SIZE> operator++(int);
    DequeIterator<T, BLOCK_SIZE> &operator+=(long long value);
    DequeIterator<T, BLOCK_SIZE> operator+(long long value);
    DequeIterator<T, BLOCK_SIZE> &operator--();
    DequeIterator<T, BLOCK_SIZE> operator--(int);
    DequeIterator<T, BLOCK_SIZE> &operator-=(long long value);
    DequeIterator<T, BLOCK_SIZE> operator-(long long value);
    T &operator*();
    T *operator->();
    T &operator[](size_type index);
    bool operator==(const DequeIterator &other);
    bool operator!=(const DequeIterator &other);
    bool operator<(const DequeIterator &other);
    bool operator>(const DequeIterator &other);
    bool operator<=(const DequeIterator &other);
    bool operator>=(const DequeIterator &other);
};

template <typename T, std::size_t BLOCK_SIZE>
void DequeIterator<T, BLOCK_SIZE>::set_block(size_type index)
{
    _block_index = index;
    _begin = map[_block_index];
    _end = _begin + BLOCK_SIZE;
}

template <typename T, std::size_t BLOCK_SIZE>
DequeIterator<T, BLOCK_SIZE>::DequeIterator(T **map, size_type map_size)
    : map(map), map_size(map_size), _block_index(0)
{
    set_block(_block_index);
    current = _begin;
}

template <typename T, std::size_t BLOCK_SIZE>
DequeIterator<T, BLOCK_SIZE>::DequeIterator(T **map, size_type map_size,
                                            T *current)
    : map(map), map_size(map_size), current(current), _block_index(0)
{
    set_block(_block_index);
}

template <typename T, std::size_t BLOCK_SIZE>
DequeIterator<T, BLOCK_SIZE>::DequeIterator(T **map, size_type map_size,
                                            T *_begin, T *current, T *_end)
    : map(map),
      map_size(map_size),
      _begin(_begin),
      current(current),
      _end(_end),
      _block_index(0)
{}

template <typename T, std::size_t BLOCK_SIZE>
typename DequeIterator<T, BLOCK_SIZE>::size_type
DequeIterator<T, BLOCK_SIZE>::block_index() const
{
    return _block_index;
}

template <typename T, std::size_t BLOCK_SIZE>
T *DequeIterator<T, BLOCK_SIZE>::begin() const
{
    return _begin;
}

template <typename T, std::size_t BLOCK_SIZE>
T *DequeIterator<T, BLOCK_SIZE>::base() const
{
    return current;
}

template <typename T, std::size_t BLOCK_SIZE>
T *DequeIterator<T, BLOCK_SIZE>::end() const
{
    return _end;
}

template <typename T, std::size_t BLOCK_SIZE>
DequeIterator<T, BLOCK_SIZE> &DequeIterator<T, BLOCK_SIZE>::operator=(
    const DequeIterator &other)
{
    if (this != &other)
    {
        map_size = other.map_size;
        _block_index = other._block_index;
        map = other.map;
        _begin = other._begin;
        current = other.current;
        _end = other._end;
    }
    return *this;
}

template <typename T, std::size_t BLOCK_SIZE>
T &DequeIterator<T, BLOCK_SIZE>::operator*()
{
    return *current;
}

template <typename T, std::size_t BLOCK_SIZE>
T *DequeIterator<T, BLOCK_SIZE>::operator->()
{
    return current;
}

template <typename T, std::size_t BLOCK_SIZE>
bool DequeIterator<T, BLOCK_SIZE>::operator==(const DequeIterator &other)
{
    return map_size == other.map_size && _block_index == other._block_index &&
           map == other.map && _begin == other._begin &&
           current == other.current && _end == other._end;
}

template <typename T, std::size_t BLOCK_SIZE>
bool DequeIterator<T, BLOCK_SIZE>::operator!=(const DequeIterator &other)
{
    return !(*this == other);
}

template <typename T, std::size_t BLOCK_SIZE>
T &DequeIterator<T, BLOCK_SIZE>::operator[](size_type index)
{
    return *(*this + index);
}

template <typename T, std::size_t BLOCK_SIZE>
DequeIterator<T, BLOCK_SIZE> &DequeIterator<T, BLOCK_SIZE>::operator++()
{
    current++;
    if (current == _end)
    {
        set_block((_block_index + 1) % map_size);
        while (map[_block_index] == nullptr)
        {
            set_block((_block_index + 1) % map_size);
        }
        current = _begin;
    }
    return *this;
}

template <typename T, std::size_t BLOCK_SIZE>
DequeIterator<T, BLOCK_SIZE> DequeIterator<T, BLOCK_SIZE>::operator++(int)
{
    DequeIterator<T, BLOCK_SIZE> temp(*this);
    ++*this;
    return temp;
}

template <typename T, std::size_t BLOCK_SIZE>
DequeIterator<T, BLOCK_SIZE> &DequeIterator<T, BLOCK_SIZE>::operator+=(
    long long value)
{
    size_type index = current - _begin;
    set_block((_block_index + (index + value) / BLOCK_SIZE) % map_size);
    while (map[_block_index] == nullptr)
    {
        set_block((_block_index + 1) % map_size);
    }
    current = _begin + (index + value) % BLOCK_SIZE;
    return *this;
    // if (value < 0)
    // {
    //     while ((bool)value++)
    //     {
    //         (*this)--;
    //     }
    // }
    // else
    // {
    //     while ((bool)value--)
    //     {
    //         (*this)++;
    //     }
    // }
}

template <typename T, std::size_t BLOCK_SIZE>
DequeIterator<T, BLOCK_SIZE> DequeIterator<T, BLOCK_SIZE>::operator+(
    long long value)
{
    DequeIterator<T, BLOCK_SIZE> temp = *this;
    return temp += value;
}

template <typename T, std::size_t BLOCK_SIZE>
DequeIterator<T, BLOCK_SIZE> &DequeIterator<T, BLOCK_SIZE>::operator--()
{
    if (current == _begin)
    {
        set_block((map_size + _block_index - 1) % map_size);
        while (map[_block_index] == nullptr)
        {
            set_block((map_size + _block_index - 1) % map_size);
        }
        current = _end;
    }
    current--;
    return *this;
}

template <typename T, std::size_t BLOCK_SIZE>
DequeIterator<T, BLOCK_SIZE> DequeIterator<T, BLOCK_SIZE>::operator--(int)
{
    DequeIterator<T, BLOCK_SIZE> temp = *this;
    --(*this);
    return temp;
}

template <typename T, std::size_t BLOCK_SIZE>
DequeIterator<T, BLOCK_SIZE> &DequeIterator<T, BLOCK_SIZE>::operator-=(
    long long value)
{
    size_type index = current - _begin;
    if (index < value)
    {
        set_block((map_size + _block_index -
                   (long long)std::ceil((value - index) / (double)BLOCK_SIZE) %
                       map_size) %
                  map_size);
        while (map[_block_index] == nullptr)
        {
            set_block((map_size + _block_index - 1) % map_size);
        }
        current = _begin + BLOCK_SIZE - (value - index) % BLOCK_SIZE;
    }
    else
    {
        current = _begin + index - value % BLOCK_SIZE;
    }
    return *this;
}

template <typename T, std::size_t BLOCK_SIZE>
DequeIterator<T, BLOCK_SIZE> DequeIterator<T, BLOCK_SIZE>::operator-(
    long long value)
{
    DequeIterator<T, BLOCK_SIZE> temp = *this;
    return temp -= value;
}

template <typename T, std::size_t BLOCK_SIZE>
bool DequeIterator<T, BLOCK_SIZE>::operator<(
    const DequeIterator<T, BLOCK_SIZE> &other)
{
    if (map == other.map)
    {
        return base() < other.base();
    }
    return map < other.map;
}

template <typename T, std::size_t BLOCK_SIZE>
bool DequeIterator<T, BLOCK_SIZE>::operator>(
    const DequeIterator<T, BLOCK_SIZE> &other)
{
    return other < *this;
}

template <typename T, std::size_t BLOCK_SIZE>
bool DequeIterator<T, BLOCK_SIZE>::operator<=(
    const DequeIterator<T, BLOCK_SIZE> &other)
{
    return !(*this > other);
}

template <typename T, std::size_t BLOCK_SIZE>
bool DequeIterator<T, BLOCK_SIZE>::operator>=(
    const DequeIterator<T, BLOCK_SIZE> &other)
{
    return !(*this < other);
}

#endif  // DEQUEITERATOR_H