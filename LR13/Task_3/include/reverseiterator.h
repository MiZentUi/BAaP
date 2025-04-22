#ifndef REVERSEITERATOR_H
#define REVERSEITERATOR_H

template <typename T>
class ReverseIterator
{
public:
    using size_type = unsigned long long;

private:
    T *pointer;

public:
    ReverseIterator(T *pointer);
    ReverseIterator(const ReverseIterator &iter);
    ReverseIterator(ReverseIterator &&) = delete;
    ~ReverseIterator() = default;

    T *base();

    ReverseIterator<T> &operator=(const ReverseIterator &iter);
    ReverseIterator<T> &operator=(ReverseIterator &&) = delete;
    T operator*();
    T *operator->();
    bool operator==(const ReverseIterator &iter);
    bool operator!=(const ReverseIterator &iter);
    T &operator[](size_type index);
    ReverseIterator<T> &operator++();
    ReverseIterator<T> operator++(int);
    ReverseIterator<T> &operator+=(size_type value);
    ReverseIterator<T> operator+(size_type value);
    ReverseIterator<T> &operator--();
    ReverseIterator<T> operator--(int);
    ReverseIterator<T> &operator-=(size_type value);
    ReverseIterator<T> operator-(size_type value);
    bool operator<(const ReverseIterator &iter);
    bool operator>(const ReverseIterator &iter);
    bool operator<=(const ReverseIterator &iter);
    bool operator>=(const ReverseIterator &iter);
};

template <typename T>
ReverseIterator<T>::ReverseIterator(T *pointer) : pointer(pointer)
{}

template <typename T>
ReverseIterator<T>::ReverseIterator(const ReverseIterator &iter)
    : pointer(iter.pointer)
{}

template <typename T>
T *ReverseIterator<T>::base()
{
    return pointer;
}

template <typename T>
ReverseIterator<T> &ReverseIterator<T>::operator=(const ReverseIterator &iter)
{
    if (this != &iter)
    {
        pointer = iter.pointer;
    }
    return *this;
}

template <typename T>
T ReverseIterator<T>::operator*()
{
    return *pointer;
}

template <typename T>
T *ReverseIterator<T>::operator->()
{
    return pointer;
}

template <typename T>
bool ReverseIterator<T>::operator==(const ReverseIterator &iter)
{
    return pointer == iter.pointer;
}

template <typename T>
bool ReverseIterator<T>::operator!=(const ReverseIterator &iter)
{
    return !(*this == iter);
}

template <typename T>
T &ReverseIterator<T>::operator[](size_type index)
{
    return *(pointer - index);
}

template <typename T>
ReverseIterator<T> &ReverseIterator<T>::operator++()
{
    pointer--;
    return *this;
}

template <typename T>
ReverseIterator<T> ReverseIterator<T>::operator++(int)
{
    ReverseIterator<T> temp = *this;
    --(*this);
    return temp;
}

template <typename T>
ReverseIterator<T> &ReverseIterator<T>::operator+=(size_type value)
{
    pointer -= value;
    return *this;
}

template <typename T>
ReverseIterator<T> ReverseIterator<T>::operator+(size_type value)
{
    return ReverseIterator<T>(pointer - value);
}

template <typename T>
ReverseIterator<T> &ReverseIterator<T>::operator--()
{
    pointer++;
    return *this;
}

template <typename T>
ReverseIterator<T> ReverseIterator<T>::operator--(int)
{
    ReverseIterator<T> temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
ReverseIterator<T> &ReverseIterator<T>::operator-=(size_type value)
{
    pointer += value;
    return *this;
}

template <typename T>
ReverseIterator<T> ReverseIterator<T>::operator-(size_type value)
{
    return ReverseIterator<T>(pointer + value);
}

template <typename T>
bool ReverseIterator<T>::operator<(const ReverseIterator<T> &iter)
{
    return (this->base() - iter.base() > 0);
}

template <typename T>
bool ReverseIterator<T>::operator>(const ReverseIterator<T> &iter)
{
    return *this < iter;
}

template <typename T>
bool ReverseIterator<T>::operator<=(const ReverseIterator<T> &iter)
{
    return !(base() < iter);
}

template <typename T>
bool ReverseIterator<T>::operator>=(const ReverseIterator<T> &iter)
{
    return !(base() > iter);
}

#endif  // REVERSEITERATOR_H