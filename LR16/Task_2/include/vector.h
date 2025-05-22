#ifndef VECTOR_H
#define VECTOR_H

#include <cstring>
#include <memory>

template <typename T>
class Vector
{
private:
    std::size_t _capacity{0};
    std::size_t _size{0};
    std::shared_ptr<T[]> _data;

public:
    Vector();
    Vector(const Vector &other);
    ~Vector();

    void clear();
    void pop_back();
    void push_back(const T &item);
    void remove(std::size_t index);
    void reserve(std::size_t capacity);
    void resize(std::size_t size);
    void resize(std::size_t size, const T &value);
    void swap(Vector<T> &vector) noexcept;
    [[nodiscard]]
    bool empty() const;
    T &at(std::size_t index);
    T &back();
    T &front();
    T *data();
    std::size_t capacity() const;
    std::size_t size() const;
    std::size_t max_size() const;

    T &operator[](std::size_t index);
    const T &operator[](std::size_t index) const;
};

template <typename T>
Vector<T>::Vector()
{}

template <typename T>
Vector<T>::Vector(const Vector<T> &other)
    : _capacity(other._capacity), _size(other._size), _data(new T[_capacity])
{
    for (std::size_t i = 0; i < _size; i++)
    {
        _data[i] = other._data[i];
    }
}

template <typename T>
Vector<T>::~Vector()
{
    for (int i = 0; i < _size; ++i)
    {
        _data[i].~T();
    }
    _data.reset();
    _capacity = 0;
    _size = 0;
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
    new (_data.get() + _size) T(item);
    ++_size;
}

template <typename T>
void Vector<T>::remove(std::size_t index)
{
    std::memmove(_data.get() + index, _data.get() + index + 1,
                 _size - index - 1);
    _size--;
}

template <typename T>
void Vector<T>::reserve(std::size_t capacity)
{
    if (capacity > _capacity)
    {
        std::shared_ptr<T[]> new_data(new T[capacity]);
        for (std::size_t i = 0; i < _capacity; i++)
        {
            new (new_data.get() + i) T(_data[i]);
            _data[i].~T();
        }
        _data = new_data;
        _capacity = capacity;
    }
}

template <typename T>
void Vector<T>::resize(std::size_t size)
{
    resize(size, T());
}

template <typename T>
void Vector<T>::resize(std::size_t size, const T &value)
{
    if (_size >= _capacity)
    {
        reserve(_size == 0 ? 1 : 2 * _size);
        for (std::size_t i = _size; i < size; i++)
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
T &Vector<T>::at(std::size_t index)
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
    return _data.lock().get();
}

template <typename T>
std::size_t Vector<T>::capacity() const
{
    return _capacity;
}

template <typename T>
std::size_t Vector<T>::size() const
{
    return _size;
}

template <typename T>
std::size_t Vector<T>::max_size() const
{
    return ((std::size_t)-1) / sizeof(T);
}

template <typename T>
T &Vector<T>::operator[](std::size_t index)
{
    return _data[index];
}

template <typename T>
const T &Vector<T>::operator[](std::size_t index) const
{
    return _data[index];
}

#endif  // VECTOR_H