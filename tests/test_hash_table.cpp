
#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <string>

//повтор хеш-функции для коллизий
std::size_t testHash(const std::string& str, std::size_t capacity) {
    std::size_t result = 0;

    for (unsigned char c : str) {
        result = result * 31 + c;
    }

    return result % capacity;
}

void findCollisions(
    std::size_t capacity,
    std::string& first,
    std::string& second,
    std::string& third
) {
    for (int i = 0; i < 1000; ++i) {
        first = "key" + std::to_string(i);

        for (int j = i + 1; j < 1000; ++j) {
            second = "key" + std::to_string(j);

            if (testHash(first, capacity) != testHash(second, capacity)) {
                continue;
            }

            for (int k = j + 1; k < 1000; ++k) {
                third = "key" + std::to_string(k);

                if (testHash(first, capacity) == testHash(third, capacity)) {
                    return;
                }
            }
        }
    }

    assert(false && "Could not find three colliding strings");
}


void testInsertAndSearch() {
    HashTable table(10);

    assert(table.insert("cat"));
    assert(table.insert("dog"));
    assert(table.insert("bird"));
    assert(table.size() == 3);

    assert(table.search("cat"));
    assert(table.search("dog"));
    assert(table.search("bird"));
    assert(!table.search("fish"));
    //повтор
    assert(!table.insert("cat"));
    assert(table.size() == 3);

    std::cout << "[OK] Insert and search\n";
}

void testCollisions() {
    const std::size_t capacity = 7;

    std::string first;
    std::string second;
    std::string third;

    findCollisions(capacity, first, second, third);

    HashTable table(capacity);

    assert(table.insert(first.c_str()));
    assert(table.insert(second.c_str()));
    assert(table.insert(third.c_str()));
    assert(table.search(first.c_str()));
    assert(table.search(second.c_str()));
    assert(table.search(third.c_str()));
    assert(table.remove(first.c_str()));
    assert(table.search(second.c_str()));
    assert(table.search(third.c_str()));
    assert(!table.search(first.c_str()));

    std::cout << "[OK] Collisions and linear probing\n";
}

void testRemoveAndReinsert() {
    HashTable table(10);

    assert(table.insert("apple"));
    assert(table.insert("banana"));
    assert(table.remove("apple"));
    assert(!table.search("apple"));
    assert(table.search("banana"));
    assert(!table.remove("orange"));
    assert(table.insert("apple"));
    assert(table.search("apple"));

    assert(table.size() == 2);

    std::cout << "[OK] Remove and reinsert\n";
}

void testFullTable() {
    HashTable table(2);

    assert(table.insert("one"));
    assert(table.insert("two"));
    assert(table.size() == 2);
    assert(!table.insert("three"));
    assert(table.search("one"));
    assert(table.search("two"));

    std::cout << "[OK] Full table\n";
}

void testClear() {
    HashTable table(10);

    assert(table.insert("first"));
    assert(table.insert("second"));
    assert(table.insert("third"));

    table.clear();

    assert(table.size() == 0);

    assert(!table.search("first"));
    assert(!table.search("second"));
    assert(!table.search("third"));
    assert(table.insert("new"));
    assert(table.search("new"));

    std::cout << "[OK] Clear\n";
}

int main() {
    testInsertAndSearch();
    testCollisions();
    testRemoveAndReinsert();
    testFullTable();
    testClear();

    std::cout << "\nAll tests passed!\n";

    return 0;
}
