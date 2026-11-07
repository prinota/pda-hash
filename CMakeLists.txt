
cmake_minimum_required(VERSION 3.16)

project(HashTable)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(HashTable
    src/main.cpp
    src/HashTable.cpp
)

target_include_directories(HashTable PRIVATE include)

add_executable(HashTableTests
    tests/test_hash_table.cpp
    src/HashTable.cpp
)

target_include_directories(HashTableTests PRIVATE include)

enable_testing()

add_test(
    NAME HashTableTests
    COMMAND HashTableTests
)
