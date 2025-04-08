#ifndef PAIR_H
#define PAIR_H

template <class T1, class T2>
class Pair
{
public:
    using first_type = T1;
    using second_type = T2;

    first_type first;
    second_type second;

    Pair() = default;
    Pair(const T1 &first, const T2 &second);
    Pair(const Pair<T1, T2> &pair) = default;
    Pair(Pair<T1, T2> &&pair) = default;
    ~Pair() = default;

    void swap(Pair &other) noexcept;

    Pair &operator=(const Pair &other);
    Pair &operator=(Pair &&other) noexcept;

private:
    template <typename E>
    void swap(E &first, E &second);
};

template <class T1, class T2>
Pair<T1, T2>::Pair(const T1 &first, const T2 &second)
    : first(first), second(second)
{}

template <class T1, class T2>
template <typename E>
void Pair<T1, T2>::swap(E &first, E &second)
{
    E &temp = first;
    &first = &second;
    &second = &temp;
}

template <class T1, class T2>
void Pair<T1, T2>::swap(Pair &other) noexcept
{
    swap(first, other.first);
    swap(second, other.second);
}

template <class T1, class T2>
Pair<T1, T2> &Pair<T1, T2>::operator=(const Pair &other)
{
    if (this != &other)
    {
        first = other.first;
        second = other.second;
    }
    return *this;
}

template <class T1, class T2>
Pair<T1, T2> &Pair<T1, T2>::operator=(Pair &&other) noexcept
{
    if (this != &other)
    {
        first = other.first;
        second = other.second;
        other.first = first_type();
        other.second = second_type();
    }
    return *this;
}

#endif  // PAIR_H