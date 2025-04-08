#ifndef VECTOR_H
#define VECTOR_H

#include "iterator.h"
#include "reverseiterator.h"

template <typename T>
class Vector
{
public:
    using size_type = unsigned long long;
    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;
    using reverse_iterator = ReverseIterator<T>;
    using const_reverse_iterator = ReverseIterator<const T>;

private:
    size_type _capacity;
    size_type _size;
    T *_data;

    template <typename E>
    void swap(E &first, E &second);

public:
    Vector();
    Vector(const Vector &vector);
    Vector(Vector &&vector) noexcept;
    explicit Vector(size_type size);
    explicit Vector(size_type size, const T &value);
    Vector(iterator first, iterator last);
    ~Vector();

    void assign(size_type size, const T &value);
    template <class InputIt>
    void assign(InputIt first, InputIt last);
    void clear();
    void pop_back();
    void push_back(const T &item);
    void reserve(size_type capacity);
    void resize(size_type size);
    void resize(size_type size, const T &value);
    void swap(Vector<T> &vector) noexcept;
    [[nodiscard]]
    bool empty() const;
    T &at(size_type index);
    T &back();
    T &front();
    T *data();
    size_type capacity();
    size_type size();
    size_type max_size();
    iterator begin();
    iterator end();
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);
    reverse_iterator rbegin();
    reverse_iterator rend();
    iterator insert(const_iterator pos, const T &value);
    iterator insert(const_iterator pos, size_type count, const T &value);
    template <class InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last);
    template <class... Args>
    iterator emplace(const_iterator pos, Args &&...args);
    template <class... Args>
    iterator emplace_back(Args &&...args);
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    Vector<T> &operator=(const Vector<T> &vector);
    Vector<T> &operator=(Vector<T> &&vector) noexcept;
    bool operator==(const Vector<T> &vector);
    bool operator!=(const Vector<T> &vector);
    T &operator[](size_type index);
};

template <typename T>
Vector<T>::Vector() : _capacity(0), _size(0), _data(nullptr)
{}

template <typename T>
Vector<T>::Vector(const Vector<T> &vector)
    : _capacity(vector._capacity), _size(vector._size), _data(new T[_capacity])
{
    for (size_type i = 0; i < _size; i++)
    {
        _data[i] = vector._data[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector<T> &&vector) noexcept
    : _capacity(vector._capacity), _size(vector._size), _data(new T[_capacity])
{
    for (size_type i = 0; i < _size; i++)
    {
        _data[i] = vector._data[i];
    }
    vector.clear();
}

template <typename T>
Vector<T>::Vector(size_type size)
    : _capacity(size), _size(size), _data(new T[_capacity])
{}

template <typename T>
Vector<T>::Vector(size_type size, const T &value)
    : _capacity(size), _size(size), _data(new T[_capacity])
{
    for (size_type i = 0; i < _size; i++)
    {
        _data[i] = value;
    }
}

template <typename T>
Vector<T>::Vector(iterator first, iterator last)
    : _capacity(first - last), _size(first - last), _data(first.base())
{}

template <typename T>
Vector<T>::~Vector()
{
    for (int i = 0; i < _size; ++i)
    {
        (_data + i)->~T();
    }
    delete[] _data;
    _data = nullptr;
    _capacity = 0;
    _size = 0;
}

template <typename T>
template <typename E>
void Vector<T>::swap(E &first, E &second)
{
    E &temp = first;
    &first = &second;
    &second = &temp;
}

template <typename T>
void Vector<T>::assign(size_type size, const T &value)
{
    clear();
    Vector<T>(size, value);
}

template <typename T>
template <class InputIt>
void Vector<T>::assign(InputIt first, InputIt last)
{
    clear();
    Vector<T>(first, last);
}

template <typename T>
void Vector<T>::clear()
{
    _size = 0;
    delete[] _data;
    _data = nullptr;
}

template <typename T>
void Vector<T>::pop_back()
{
    if (!empty())
    {
        _data[_size - 1].~T();
        _size--;
    }
}

template <typename T>
void Vector<T>::push_back(const T &item)
{
    if (_size >= _capacity)
    {
        reserve(_size == 0 ? 1 : 2 * _size);
    }
    new (_data + _size) T(item);
    ++_size;
}

template <typename T>
void Vector<T>::reserve(size_type capacity)
{
    if (capacity > _capacity)
    {
        T *new_data = new T[capacity];
        for (size_type i = 0; i < _capacity; i++)
        {
            new (new_data + i) T(_data[i]);
            _data[i].~T();
        }
        delete[] _data;
        _data = new_data;
        _capacity = capacity;
    }
}

template <typename T>
void Vector<T>::resize(size_type size)
{
    resize(size, T());
}

template <typename T>
void Vector<T>::resize(size_type size, const T &value)
{
    if (_size >= _capacity)
    {
        reserve(_size == 0 ? 1 : 2 * _size);
        for (size_type i = _size; i < size; i++)
        {
            new (_data + i) T(value);
        }
    }
    _size = size;
}

template <typename T>
void Vector<T>::swap(Vector<T> &vector) noexcept
{
    swap(_capacity, vector._capacity);
    swap(_size, vector._size);
    swap(_data, vector._data);
}

template <typename T>
bool Vector<T>::empty() const
{
    return _size == 0;
}

template <typename T>
T &Vector<T>::at(size_type index)
{
    return _data[index];
}

template <typename T>
T &Vector<T>::back()
{
    return _data[_size - 1];
}

template <typename T>
T &Vector<T>::front()
{
    return _data[0];
}

template <typename T>
T *Vector<T>::data()
{
    return _data;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity()
{
    return _capacity;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size()
{
    return _size;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::max_size()
{
    return ((size_type)-1) / sizeof(T);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return iterator(_data);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end()
{
    return iterator(_data + _size);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator pos)
{
    return erase(pos, pos + 1);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator first, iterator last)
{
    if (begin() <= first && first <= end() && first < last && last <= end())
    {
        while (last < end())
        {
            first->~T();
            new (first.base()) T(*last);
            last->~T();
            first++;
            last++;
        }
        _size -= last - first;
    }
    return last;
}

template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin()
{
    return reverse_iterator(_data + _size);
}

template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend()
{
    return reverse_iterator(_data);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos,
                                               const T &value)
{
    insert(pos, 1, value);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos,
                                               size_type count, const T &value)
{
    _size += count;
    size_type index = pos - cbegin();
    if (_size >= _capacity)
    {
        reserve(_size == 0 ? 1 : 2 * _size);
    }
    memmove((void *)_data + index + count, _data + index,
            (_size - count - index) * sizeof(T));
    for (size_type i = index; i < index + count; i++)
    {
        new (_data + i) T(value);
    }
    return iterator((T *)pos.base());
}

template <typename T>
template <class InputIt>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos,
                                               InputIt first, InputIt last)
{
    while (first < last)
    {
        insert(pos, *first);
        first++;
    }
}

template <typename T>
template <class... Args>
typename Vector<T>::iterator Vector<T>::emplace(const_iterator pos,
                                                Args &&...args)
{
    size_type count = 1;
    _size += count;
    size_type index = pos - cbegin();
    if (_size >= _capacity)
    {
        reserve(_size == 0 ? 1 : 2 * _size);
    }
    memmove(_data + index + count, _data + index,
            (_size - count - index) * sizeof(T));
    for (size_type i = index; i < index + count; i++)
    {
        new (_data + i) T(args...);
    }
    return iterator((T *)pos.base());
}

template <typename T>
template <class... Args>
typename Vector<T>::iterator Vector<T>::emplace_back(Args &&...args)
{
    emplace(end(), args...);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept
{
    return const_iterator(_data);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const noexcept
{
    return const_iterator(_data + _size);
}

template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crbegin() const noexcept
{
    return const_reverse_iterator(_data + _size);
}

template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crend() const noexcept
{
    return const_reverse_iterator(_data);
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &vector)
{
    if (this != &vector)
    {
        delete[] _data;
        _data = nullptr;
        _size = vector._size;
        if (_size >= _capacity)
        {
            reserve(_size == 0 ? 1 : 2 * _size);
        }
        for (size_type i = 0; i < _size; i++)
        {
            _data[i] = vector._data[i];
        }
    }
    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&vector) noexcept
{
    if (this != &vector)
    {
        delete[] _data;
        _size = vector._size;
        if (_size >= _capacity)
        {
            reserve(_size == 0 ? 1 : 2 * _size);
        }
        for (size_type i = 0; i < _size; i++)
        {
            _data[i] = vector._data[i];
        }
        vector.clear();
    }
    return *this;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T> &vector)
{
    if (_capacity == vector._capacity && _size == vector._size)
    {
        for (size_type i = 0; i < _size; i++)
        {
            if ((*this)[i] != vector[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T> &vector)
{
    return !(*this == vector);
}

template <typename T>
T &Vector<T>::operator[](size_type index)
{
    return _data[index];
}

#endif  // VECTOR_H