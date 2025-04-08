#ifndef ITERATOR_H
#define ITERATOR_H

template <typename T>
class Iterator
{
public:
    using size_type = unsigned long long;

private:
    T *pointer;

public:
    Iterator(T *pointer);
    Iterator(const Iterator &iter) = default;
    Iterator(Iterator &&) = default;
    ~Iterator();

    T *base() const;

    Iterator<T> &operator=(const Iterator &iter);
    Iterator<T> &operator=(Iterator &&iter) = default;
    T operator*();
    T *operator->();
    bool operator==(const Iterator &iter);
    bool operator!=(const Iterator &iter);
    T &operator[](size_type index);
    Iterator<T> &operator++();
    Iterator<T> operator++(int);
    Iterator<T> &operator+=(size_type value);
    Iterator<T> operator+(size_type value);
    Iterator<T> &operator--();
    Iterator<T> operator--(int);
    Iterator<T> &operator-=(size_type value);
    Iterator<T> operator-(size_type value);
    size_type operator-(const Iterator &iter);
    bool operator<(const Iterator &iter);
    bool operator>(const Iterator &iter);
    bool operator<=(const Iterator &iter);
    bool operator>=(const Iterator &iter);
};

template <typename T>
Iterator<T>::Iterator(T *pointer) : pointer(pointer)
{}

template <typename T>
Iterator<T>::~Iterator()
{}

template <typename T>
T *Iterator<T>::base() const
{
    return pointer;
}

template <typename T>
Iterator<T> &Iterator<T>::operator=(const Iterator &iter)
{
    if (this != &iter)
    {
        pointer = iter.pointer;
    }
    return *this;
}

template <typename T>
T Iterator<T>::operator*()
{
    return *pointer;
}

template <typename T>
T *Iterator<T>::operator->()
{
    return pointer;
}

template <typename T>
bool Iterator<T>::operator==(const Iterator &iter)
{
    return pointer == iter.pointer;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator &iter)
{
    return !(*this == iter);
}

template <typename T>
T &Iterator<T>::operator[](size_type index)
{
    return *(pointer + index);
}

template <typename T>
Iterator<T> &Iterator<T>::operator++()
{
    pointer++;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int)
{
    Iterator<T> temp(*this);
    pointer++;
    return temp;
}

template <typename T>
Iterator<T> &Iterator<T>::operator+=(size_type value)
{
    pointer += value;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator+(size_type value)
{
    return Iterator<T>(pointer + value);
}

template <typename T>
Iterator<T> &Iterator<T>::operator--()
{
    pointer--;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator--(int)
{
    Iterator<T> temp = *this;
    --(*this);
    return temp;
}

template <typename T>
Iterator<T> &Iterator<T>::operator-=(size_type value)
{
    pointer -= value;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator-(size_type value)
{
    return Iterator<T>(pointer - value);
}

template <typename T>
typename Iterator<T>::size_type Iterator<T>::operator-(const Iterator<T> &iter)
{
    if (*this > iter)
        return base() - iter.base();
    return iter.base() - base();
}

template <typename T>
bool Iterator<T>::operator<(const Iterator<T> &iter)
{
    return ((iter.base() - this->base()) > 0);
}

template <typename T>
bool Iterator<T>::operator>(const Iterator<T> &iter)
{
    return iter.base() < this->base();
}

template <typename T>
bool Iterator<T>::operator<=(const Iterator<T> &iter)
{
    return !(*this > iter);
}

template <typename T>
bool Iterator<T>::operator>=(const Iterator<T> &iter)
{
    return !(*this < iter);
}

#endif  // ITERATOR_H