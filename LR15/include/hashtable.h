#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cmath>
#include <utility>

template <typename K, typename V, std::size_t TABLE_SIZE = 16>
class HashTable
{
private:
    struct Node
    {
        K key;
        V value;
        bool deleted = false;

        Node(const K &key, const V &value) : key(key), value(value) {}
    };

    std::size_t _size = 0;
    std::size_t _deleted_size = 0;
    std::size_t _table_size;
    Node **_table;

    std::size_t multi_hash(const K &key);
    std::size_t mod_hash(const K &key);
    void resize(std::size_t new_size);

public:
    HashTable();
    HashTable(const HashTable &other);
    HashTable(HashTable &&other) = delete;
    ~HashTable();

    std::size_t size();
    bool empty();
    bool contains(const K &key);
    void clear();
    void remove(const K &key);

    HashTable &operator=(const HashTable &other);
    HashTable &operator=(HashTable &&other) = delete;
    V &operator[](const K &key);
};

template <typename K, typename V, std::size_t TABLE_SIZE>
std::size_t HashTable<K, V, TABLE_SIZE>::multi_hash(const K &key)
{
    return _table_size * (key * std::fmod((std::sqrt(5) - 1) / 2, 1));
}

template <typename K, typename V, std::size_t TABLE_SIZE>
std::size_t HashTable<K, V, TABLE_SIZE>::mod_hash(const K &key)
{
    return key % _table_size;
}

template <typename K, typename V, std::size_t TABLE_SIZE>
void HashTable<K, V, TABLE_SIZE>::resize(std::size_t new_size)
{
    std::size_t prev_table_size = _table_size;
    _table_size = new_size;
    _size = 0;
    _deleted_size = 0;
    Node **new_table = new Node *[_table_size] {};
    std::swap(_table, new_table);
    for (std::size_t i = 0; i < prev_table_size; i++)
    {
        Node *node = new_table[i];
        if (node != nullptr && !node->deleted)
        {
            operator[](node->key) = node->value;
        }
    }
    for (std::size_t i = 0; i < prev_table_size; i++)
    {
        delete new_table[i];
        new_table[i] = nullptr;
    }
    delete[] new_table;
    new_table = nullptr;
}

template <typename K, typename V, std::size_t TABLE_SIZE>
HashTable<K, V, TABLE_SIZE>::HashTable()
    : _table_size(TABLE_SIZE), _table(new Node *[_table_size] {})
{}

template <typename K, typename V, std::size_t TABLE_SIZE>
HashTable<K, V, TABLE_SIZE>::HashTable(const HashTable &other)
    : _table_size(TABLE_SIZE), _table(new Node *[_table_size] {})
{
    for (std::size_t i = 0; i < other._table_size; i++)
    {
        operator[](other._table[i]->key) = other._table[i]->value;
    }
}

template <typename K, typename V, std::size_t TABLE_SIZE>
HashTable<K, V, TABLE_SIZE>::~HashTable()
{
    for (std::size_t i = 0; i < _table_size; i++)
    {
        delete _table[i];
        _table[i] = nullptr;
    }
    delete[] _table;
    _table = nullptr;
}

template <typename K, typename V, std::size_t TABLE_SIZE>
std::size_t HashTable<K, V, TABLE_SIZE>::size()
{
    return _size;
}

template <typename K, typename V, std::size_t TABLE_SIZE>
bool HashTable<K, V, TABLE_SIZE>::empty()
{
    return _size == 0;
}

template <typename K, typename V, std::size_t TABLE_SIZE>
bool HashTable<K, V, TABLE_SIZE>::contains(const K &key)
{
    std::size_t hash1 = multi_hash(key);
    std::size_t hash2 = mod_hash(key);
    for (std::size_t i = 0; i < _table_size; i++)
    {
        Node *&node = _table[(hash1 + i * hash2) % _table_size];
        if (node == nullptr || node->deleted)
        {
            return false;
        }
        if (node->key == key)
        {
            return true;
        }
    }
    return false;
}

template <typename K, typename V, std::size_t TABLE_SIZE>
void HashTable<K, V, TABLE_SIZE>::clear()
{
    _size = 0;
    _deleted_size = 0;
    for (std::size_t i = 0; i < _table_size; i++)
    {
        delete _table[i];
        _table[i] = nullptr;
    }
}

template <typename K, typename V, std::size_t TABLE_SIZE>
void HashTable<K, V, TABLE_SIZE>::remove(const K &key)
{
    std::size_t hash1 = multi_hash(key);
    std::size_t hash2 = mod_hash(key);
    for (std::size_t i = 0; i < _table_size; i++)
    {
        Node *&node = _table[(hash1 + i * hash2) % _table_size];
        if (node == nullptr || node->deleted)
        {
            return;
        }
        if (node->key == key)
        {
            node->deleted = true;
            _size--;
            _deleted_size++;
            return;
        }
    }
}

template <typename K, typename V, std::size_t TABLE_SIZE>
HashTable<K, V, TABLE_SIZE> &HashTable<K, V, TABLE_SIZE>::operator=(
    const HashTable<K, V, TABLE_SIZE> &other)
{
    if (this != &other)
    {
        clear();
        for (std::size_t i = 0; i < other._table_size; i++)
        {
            operator[](other._table[i]->key) = other._table[i]->value;
        }
    }
}

template <typename K, typename V, std::size_t TABLE_SIZE>
V &HashTable<K, V, TABLE_SIZE>::operator[](const K &key)
{
    if (_size + _deleted_size >= _table_size)
    {
        resize(_table_size * 2);
    }
    if (_deleted_size > _size)
    {
        resize(_table_size);
    }
    std::size_t hash1 = multi_hash(key);
    std::size_t hash2 = mod_hash(key);
    for (std::size_t i = 0; i < _table_size; i++)
    {
        Node *&node = _table[(hash1 + i * hash2) % _table_size];
        if (node == nullptr)
        {
            _size++;
            node = new Node(key, V());
            return node->value;
        }
        if (node->deleted)
        {
            _deleted_size--;
            _size++;
            node->key = key;
            node->value = V();
            node->deleted = false;
            return node->value;
        }
        if (node->key == key)
        {
            return node->value;
        }
    }
    resize(_table_size * 2);
    return operator[](key);
}

#endif  // HASHTABLE_H
