
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstddef>

class HashTable {
private:
    enum class State {
        EMPTY,
        OCCUPIED,
        DELETED
    };

    struct Slot {
        char* key;
        State state;
    };

    Slot* table;
    std::size_t capacity;
    std::size_t count;

    std::size_t hash(const char* str) const;

public:
    explicit HashTable(std::size_t size = 16);

    ~HashTable();

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    bool insert(const char* str);
    bool search(const char* str) const;
    bool remove(const char* str);

    void clear();

    std::size_t size() const;

    void print() const;
};

#endif
