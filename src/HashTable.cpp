
#include "HashTable.h"

#include <iostream>
#include <cstring>
#include <stdexcept>

HashTable::HashTable(std::size_t size)
    : table(nullptr), capacity(size), count(0)
{
    if (size == 0) {
        throw std::invalid_argument(
            "Hash table capacity cannot be zero"
        );
    }

    table = new Slot[capacity];

    for (std::size_t i = 0; i < capacity; ++i) {
        table[i].key = nullptr;
        table[i].state = State::EMPTY;
    }
}

HashTable::~HashTable()
{
    clear();
    delete[] table;
}


std::size_t HashTable::hash(const char* str) const
{
    const std::size_t prime = 31;
    std::size_t result = 0;

    while (*str != '\0') {
        result = result * prime +
                 static_cast<unsigned char>(*str);
        ++str;
    }

    return result % capacity;
}


bool HashTable::insert(const char* str)
{
    if (str == nullptr) {
        return false;
    }

    if (count == capacity) {
        return false;
    }

    std::size_t index = hash(str);
    std::size_t deletedIndex = capacity;

    for (std::size_t i = 0; i < capacity; ++i) {

        std::size_t current = (index + i) % capacity;

        if (table[current].state == State::OCCUPIED) {

            if (std::strcmp(table[current].key, str) == 0) {
                return false;
            }
        }
        else if (table[current].state == State::DELETED) {

            if (deletedIndex == capacity) {
                deletedIndex = current;
            }
        }
        else if (table[current].state == State::EMPTY) {

            if (deletedIndex != capacity) {
                current = deletedIndex;
            }

            std::size_t length = std::strlen(str) + 1;

            char* newKey = new char[length];
            std::strcpy(newKey, str);

            table[current].key = newKey;
            table[current].state = State::OCCUPIED;

            ++count;

            return true;
        }
    }

    if (deletedIndex != capacity) {

        std::size_t length = std::strlen(str) + 1;

        char* newKey = new char[length];
        std::strcpy(newKey, str);

        table[deletedIndex].key = newKey;
        table[deletedIndex].state = State::OCCUPIED;

        ++count;

        return true;
    }

    return false;
}

bool HashTable::search(const char* str) const
{
    if (str == nullptr) {
        return false;
    }

    std::size_t index = hash(str);

    for (std::size_t i = 0; i < capacity; ++i) {

        std::size_t current = (index + i) % capacity;

        if (table[current].state == State::EMPTY) {
            return false;
        }

        if (table[current].state == State::OCCUPIED) {

            if (std::strcmp(table[current].key, str) == 0) {
                return true;
            }
        }
    }

    return false;
}



bool HashTable::remove(const char* str)
{
    if (str == nullptr) {
        return false;
    }

    std::size_t index = hash(str);

    for (std::size_t i = 0; i < capacity; ++i) {

        std::size_t current = (index + i) % capacity;

        if (table[current].state == State::EMPTY) {
            return false;
        }

        if (table[current].state == State::OCCUPIED) {

            if (std::strcmp(table[current].key, str) == 0) {

                delete[] table[current].key;

                table[current].key = nullptr;
                table[current].state = State::DELETED;

                --count;

                return true;
            }
        }
    }

    return false;
}


void HashTable::clear()
{
    for (std::size_t i = 0; i < capacity; ++i) {

        if (table[i].state == State::OCCUPIED) {
            delete[] table[i].key;
            table[i].key = nullptr;
        }

        table[i].state = State::EMPTY;
    }

    count = 0;
}


std::size_t HashTable::size() const
{
    return count;
}


void HashTable::print() const
{
    std::cout << "\nHash Table:\n";

    for (std::size_t i = 0; i < capacity; ++i) {

        std::cout << "[" << i << "] ";

        if (table[i].state == State::EMPTY) {
            std::cout << "EMPTY";
        }
        else if (table[i].state == State::DELETED) {
            std::cout << "DELETED";
        }
        else {
            std::cout << table[i].key;
        }

        std::cout << '\n';
    }

    std::cout << "Elements: "<<count<< " / "<<capacity<< "\n";
}
