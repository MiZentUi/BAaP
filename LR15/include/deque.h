#ifndef DEQUE_H
#define DEQUE_H

#include <cstddef>

#include "dequeiterator.h"

template <typename T, std::size_t BLOCK_SIZE = 8>
class Deque
{
public:
    using size_type = std::size_t;
    using iterator = DequeIterator<T, BLOCK_SIZE>;
    using const_iterator = DequeIterator<const T, BLOCK_SIZE>;

private:
    size_type _map_size = 0;
    size_type _size = 0;
    T **_map;

    iterator _begin;
    iterator _end;

    void grow();

public:
    Deque();
    Deque(const Deque &other) = default;
    Deque(Deque &&) = default;
    ~Deque();

    size_type size() noexcept;
    [[nodiscard]]
    bool empty() const;
    void clear();
    void resize(size_type count);
    void resize(size_type count, const T &value);
    void push_back(const T &value);
    void push_front(const T &value);
    void pop_back();
    void pop_front();
    T &front();
    T &back();
    const T &front() const;
    const T &back() const;

    iterator begin();
    iterator end();
    [[nodiscard]]
    const_iterator begin() const;
    [[nodiscard]]
    const_iterator end() const;
    [[nodiscard]]
    const_iterator cbegin() const noexcept;
    [[nodiscard]]
    const_iterator cend() const noexcept;

    Deque<T, BLOCK_SIZE> &operator=(const Deque &other) = default;
    Deque<T, BLOCK_SIZE> &operator=(Deque &&other) = default;
    T &operator[](size_type pos);
    const T &operator[](size_type pos) const;
};

template <typename T, std::size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::grow()
{
    auto new_map = new T *[_map_size * 2] {};
    for (size_type i = 0; i < _size; i++)
    {
        if (i % BLOCK_SIZE == 0)
        {
            new_map[i / BLOCK_SIZE] = new T[BLOCK_SIZE]{};
        }
        new (new_map[i / BLOCK_SIZE] + i % BLOCK_SIZE) T(*(_begin + i));
    }
    for (size_type i = 0; i < _map_size; i++)
    {
        delete[] _map[i];
    }
    delete[] _map;
    _map = new_map;
    _map_size *= 2;
    _begin = iterator(_map, _map_size);
    _end = iterator(_begin + _size);
}

template <typename T, std::size_t BLOCK_SIZE>
Deque<T, BLOCK_SIZE>::Deque()
    : _map_size(8),
      _map(new T *[_map_size] {}),
      _begin(iterator(_map, _map_size)),
      _end(iterator(_begin))
{
    _map[0] = new T[BLOCK_SIZE]{};
    _begin = iterator(_map, _map_size);
    _end = iterator(_begin);
}

template <typename T, std::size_t BLOCK_SIZE>
Deque<T, BLOCK_SIZE>::~Deque()
{
    for (size_type i = 0; i < _map_size; i++)
    {
        delete[] _map[i];
        _map[i] = nullptr;
    }
    delete[] _map;
    _map = nullptr;
}

template <typename T, std::size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::size_type Deque<T, BLOCK_SIZE>::size() noexcept
{
    return _size;
}

template <typename T, std::size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::empty() const
{
    return _size == 0;
}

template <typename T, std::size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::clear()
{
    while (_size > 0)
    {
        pop_back();
    }
}

template <typename T, std::size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::resize(size_type count)
{
    resize(count, T());
}

template <typename T, std::size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::resize(size_type count, const T &value)
{
    if (count < _size)
    {
        while (count < _size)
        {
            pop_back();
        }
    }
    else if (count > _size)
    {
        while (count > _size)
        {
            push_back(value);
        }
    }
}

template <typename T, std::size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::push_back(const T &value)
{
    if (_size + 1 >= _map_size * BLOCK_SIZE)
    {
        grow();
    }
    if (_end.base() == _end.end() - 1)
    {
        _map[(_end.block_index() + 1) % _map_size] = new T[BLOCK_SIZE]{};
    }
    new (_end.base()) T(value);
    _end++;
    _size++;
}

template <typename T, std::size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::push_front(const T &value)
{
    if (_size + 1 >= _map_size * BLOCK_SIZE)
    {
        grow();
    }
    if (_begin.base() == _begin.begin())
    {
        if (_begin.block_index() == 0)
        {
            _map[_map_size - 1] = new T[BLOCK_SIZE]{};
        }
        else
        {
            _map[(_begin.block_index() - 1) % _map_size] = new T[BLOCK_SIZE]{};
        }
    }
    _begin--;
    new (_begin.base()) T(value);
    _size++;
}

template <typename T, std::size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::pop_back()
{
    if (_size > 0)
    {
        _end--;
        (*_end).~T();
        _size--;
    }
}

template <typename T, std::size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::pop_front()
{
    if (_size > 0)
    {
        (*_begin).~T();
        _begin++;
        _size--;
    }
}

template <typename T, std::size_t BLOCK_SIZE>
T &Deque<T, BLOCK_SIZE>::front()
{
    return *_begin;
}

template <typename T, std::size_t BLOCK_SIZE>
T &Deque<T, BLOCK_SIZE>::back()
{
    return *(_end - 1);
}

template <typename T, std::size_t BLOCK_SIZE>
const T &Deque<T, BLOCK_SIZE>::front() const
{
    return *_begin;
}

template <typename T, std::size_t BLOCK_SIZE>
const T &Deque<T, BLOCK_SIZE>::back() const
{
    return *(_end - 1);
}

template <typename T, std::size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator Deque<T, BLOCK_SIZE>::begin()
{
    return _begin;
}

template <typename T, std::size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator Deque<T, BLOCK_SIZE>::end()
{
    return _end;
}

template <typename T, std::size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator Deque<T, BLOCK_SIZE>::begin()
    const
{
    return _begin;
}

template <typename T, std::size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator Deque<T, BLOCK_SIZE>::end() const
{
    return _end;
}

template <typename T, std::size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator Deque<T, BLOCK_SIZE>::cbegin()
    const noexcept
{
    return _begin;
}

template <typename T, std::size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator Deque<T, BLOCK_SIZE>::cend()
    const noexcept
{
    return _end;
}

template <typename T, std::size_t BLOCK_SIZE>
T &Deque<T, BLOCK_SIZE>::operator[](size_type pos)
{
    return *(_begin + pos);
}

template <typename T, std::size_t BLOCK_SIZE>
const T &Deque<T, BLOCK_SIZE>::operator[](size_type pos) const
{
    return *(_begin + pos);
}

#endif  // DEQUE_H
