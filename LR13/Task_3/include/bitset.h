#ifndef BITSET_H
#define BITSET_H

#include <iostream>

#include "./string.h"

template <std::size_t N>
class BitSet
{
public:
    class reference
    {
    private:
        friend class BitSet;

        uint64_t *block;
        size_t index;

        reference(BitSet *bits, size_t index) noexcept
            : block(&bits->blocks[index / 64]), index(index % 64)
        {}

    public:
        reference &operator=(bool val) noexcept
        {
            if (val)
            {
                *block |= 1ULL << index;
            }
            else
            {
                *block &= ~(1ULL << index);
            }
            return *this;
        }
        reference &operator=(const reference &other) noexcept
        {
            if (this != &other)
            {
                block = other->block;
                index = other->index;
            }
            return *this;
        }
        bool operator~() const noexcept
        {
            return (bool)(*block ^ (1ULL << index));
        }
        operator bool() const noexcept { return (bool)((*block >> index) & 1); }
        reference &flip() noexcept
        {
            *block ^= 1ULL << index;
            return *this;
        }
    };

private:
    static const size_t BLOCKS_COUNT = (N + 63) / 64;
    static const size_t STORABLE_BITS = BLOCKS_COUNT * 64;
    static const size_t FINAL_BITS = 64 - STORABLE_BITS + N;
    static const size_t FINAL_MASK =
        FINAL_BITS == 64 ? (~0) : ((1ULL << FINAL_BITS) - 1);

    uint64_t blocks[BLOCKS_COUNT]{};

public:
    BitSet();
    constexpr BitSet(unsigned long long val) noexcept;
    template <class CharT = char>
    explicit BitSet(const String &str, String::size_type pos = 0,
                    String::size_type n = String::npos, CharT zero = CharT('0'),
                    CharT one = CharT('1'));
    template <class CharT = char>
    explicit BitSet(const CharT *str, std::size_t n = std::size_t(-1),
                    CharT zero = CharT('0'), CharT one = CharT('1'));

    [[nodiscard]]
    bool test(std::size_t pos) const;
    [[nodiscard]]
    bool all() const;
    [[nodiscard]]
    bool any() const;
    [[nodiscard]]
    bool none() const;
    [[nodiscard]]
    std::size_t count() const;
    [[nodiscard]]
    std::size_t size() const;
    BitSet &set();
    BitSet &set(std::size_t pos, bool value = true);
    BitSet &reset();
    BitSet &reset(std::size_t pos);
    BitSet &flip();
    BitSet &flip(std::size_t pos);
    template <class CharT = char>
    String to_string(CharT zero = CharT('0'), CharT one = CharT('1')) const;
    [[nodiscard]]
    unsigned long to_ulong() const;
    [[nodiscard]]
    unsigned long long to_ullong() const;

    bool operator==(const BitSet &rhs) const;
    bool operator!=(const BitSet &rhs) const;
    bool operator[](std::size_t pos) const;
    reference operator[](std::size_t pos);
    BitSet &operator&=(const BitSet &other);
    BitSet &operator|=(const BitSet &other);
    BitSet &operator^=(const BitSet &other);
    BitSet &operator<<=(std::size_t pos);
    BitSet &operator>>=(std::size_t pos);
    BitSet operator<<(std::size_t pos) const;
    BitSet operator>>(std::size_t pos) const;
    BitSet operator~() const;
    BitSet operator&(const BitSet<N> &other);
    BitSet operator|(const BitSet<N> &other);
    BitSet operator^(const BitSet<N> &other);
};

template <std::size_t N>
BitSet<N>::BitSet()
{
    for (size_t i = 0; i < BLOCKS_COUNT; i++)
    {
        blocks[i] = 0;
    }
}

template <std::size_t N>
template <class CharT>
BitSet<N>::BitSet(const String &str, String::size_type pos, String::size_type n,
                  CharT zero, CharT one)
    : BitSet()
{
    if (n == String::npos)
    {
        n = str.size();
    }
    for (String::size_type i = pos; i < n; i++)
    {
        if (str[i] == one)
        {
            set(i - pos);
        }
    }
}

template <std::size_t N>
template <class CharT>
BitSet<N>::BitSet(const CharT *str, std::size_t n, CharT zero, CharT one)
    : BitSet(str, 0, n, zero, one)
{}

template <std::size_t N>
constexpr BitSet<N>::BitSet(unsigned long long val) noexcept
{
    for (size_t i = 0; i < BLOCKS_COUNT; i++)
    {
        blocks[i] = 0;
    }
    blocks[0] = val;
}

template <std::size_t N>
bool BitSet<N>::test(std::size_t pos) const
{
    return (blocks[pos / 64] >> (pos % 64)) & 1;
}

template <std::size_t N>
bool BitSet<N>::all() const
{
    return count() == N;
}

template <std::size_t N>
bool BitSet<N>::any() const
{
    return count() > 0;
}

template <std::size_t N>
bool BitSet<N>::none() const
{
    return count() == 0;
}

template <std::size_t N>
std::size_t BitSet<N>::count() const
{
    size_t bits = 0;
    for (size_t i = 0; i < BLOCKS_COUNT - 1; i++)
    {
        bits += __builtin_popcountll(blocks[i]);
    }
    bits += __builtin_popcountll(blocks[BLOCKS_COUNT - 1] & FINAL_MASK);
    return bits;
}

template <std::size_t N>
std::size_t BitSet<N>::size() const
{
    return N;
}

template <std::size_t N>
BitSet<N> &BitSet<N>::set()
{
    for (size_t i = 0; i < BLOCKS_COUNT; i++)
    {
        blocks[i] = ~0;
    }
    return *this;
}

template <std::size_t N>
BitSet<N> &BitSet<N>::set(std::size_t pos, bool value)
{
    reference(this, pos) = value;
    return *this;
}

template <std::size_t N>
BitSet<N> &BitSet<N>::reset()
{
    for (size_t i = 0; i < BLOCKS_COUNT; i++)
    {
        blocks[i] = 0;
    }
    return *this;
}

template <std::size_t N>
BitSet<N> &BitSet<N>::reset(std::size_t pos)
{
    reference(this, pos) = false;
    return *this;
}

template <std::size_t N>
BitSet<N> &BitSet<N>::flip()
{
    for (int i = 0; i < BLOCKS_COUNT; i++)
    {
        blocks[i] = ~blocks[i];
    }
    return *this;
}

template <std::size_t N>
BitSet<N> &BitSet<N>::flip(std::size_t pos)
{
    reference(this, pos).flip();
    return *this;
}

template <std::size_t N>
template <class CharT>
String BitSet<N>::to_string(CharT zero, CharT one) const
{
    String str(N, zero);
    for (size_t i = 0; i < N; i++)
    {
        if (test(i))
        {
            str[N - i - 1] = '1';
        }
    }
    return str;
}

template <std::size_t N>
unsigned long BitSet<N>::to_ulong() const
{
    return blocks[0];
}

template <std::size_t N>
unsigned long long BitSet<N>::to_ullong() const
{
    return blocks[0];
}

template <std::size_t N>
bool BitSet<N>::operator==(const BitSet &rhs) const
{
    size_t count = rhs.size() > N ? rhs.size() : N;
    for (size_t i = 0; i < count; i++)
    {
        if (test(i) != rhs.test(i))
        {
            return false;
        }
    }
    return true;
}

template <std::size_t N>
bool BitSet<N>::operator!=(const BitSet &rhs) const
{
    return !(*this == rhs);
}

template <std::size_t N>
bool BitSet<N>::operator[](std::size_t pos) const
{
    return static_cast<bool>(reference(*this, pos));
}

template <std::size_t N>
typename BitSet<N>::reference BitSet<N>::operator[](std::size_t pos)
{
    return static_cast<bool>(reference(*this, pos));
}

template <std::size_t N>
BitSet<N> &BitSet<N>::operator&=(const BitSet &other)
{
    for (size_t i = 0; i < BLOCKS_COUNT; i++)
    {
        blocks[i] &= other.blocks[i];
    }
    return *this;
}

template <std::size_t N>
BitSet<N> &BitSet<N>::operator|=(const BitSet &other)
{
    for (size_t i = 0; i < BLOCKS_COUNT; i++)
    {
        blocks[i] |= other.blocks[i];
    }
    return *this;
}

template <std::size_t N>
BitSet<N> &BitSet<N>::operator^=(const BitSet &other)
{
    for (size_t i = 0; i < BLOCKS_COUNT; i++)
    {
        blocks[i] ^= other.blocks[i];
    }
    return *this;
}

template <std::size_t N>
BitSet<N> &BitSet<N>::operator<<=(std::size_t pos)
{
    for (size_t i = 0; i < BLOCKS_COUNT; i++)
    {
        blocks[i] <<= pos;
    }
    return *this;
}

template <std::size_t N>
BitSet<N> &BitSet<N>::operator>>=(std::size_t pos)
{
    for (size_t i = 0; i < BLOCKS_COUNT; i++)
    {
        blocks[i] >>= pos;
    }
    return *this;
}

template <std::size_t N>
BitSet<N> BitSet<N>::operator<<(std::size_t pos) const
{
    BitSet<N> res = *this;
    return res <<= pos;
}

template <std::size_t N>
BitSet<N> BitSet<N>::operator>>(std::size_t pos) const
{
    BitSet<N> res = *this;
    return res >>= pos;
}

template <std::size_t N>
BitSet<N> BitSet<N>::operator~() const
{
    BitSet<N> res = *this;
    return res.flip();
}

template <std::size_t N>
BitSet<N> BitSet<N>::operator&(const BitSet<N> &other)
{
    BitSet<N> res;
    for (size_t i = 0; i < BitSet<N>::BLOCKS_COUNT; i++)
    {
        res.blocks[i] = blocks[i] & other.blocks[i];
    }
    return res;
}

template <std::size_t N>
BitSet<N> BitSet<N>::operator|(const BitSet<N> &other)
{
    BitSet<N> res;
    for (size_t i = 0; i < BitSet<N>::BLOCKS_COUNT; i++)
    {
        res.blocks[i] = blocks[i] | other.blocks[i];
    }
    return res;
}

template <std::size_t N>
BitSet<N> BitSet<N>::operator^(const BitSet<N> &other)
{
    BitSet<N> res;
    for (size_t i = 0; i < BitSet<N>::BLOCKS_COUNT; i++)
    {
        res.blocks[i] = blocks[i] ^ other.blocks[i];
    }
    return res;
}

template <class CharT, class Traits, std::size_t N>
std::basic_ostream<CharT, Traits> &operator<<(
    std::basic_ostream<CharT, Traits> &bos, const BitSet<N> &bits)
{
    bos << bits.to_string();
}

template <class CharT, class Traits, std::size_t N>
std::basic_istream<CharT, Traits> &operator>>(
    std::basic_istream<CharT, Traits> &bis, BitSet<N> &bits)
{
    String str;
    bis >> str;
    bits = BitSet<N>(str);
}

#endif  // BITSET_H