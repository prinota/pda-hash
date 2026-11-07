#include <iostream>
#include "HashTable.h"

int main()
{
    HashTable table(7);

    std::cout << "Inserting elements:\n";

    std::cout << "cat: " << table.insert("cat") << '\n';

    std::cout << "dog: " << table.insert("dog") << '\n';

    std::cout << "car: "<< table.insert("car") << '\n';

    std::cout << "bird: "<< table.insert("bird") << '\n';

    std::cout << "cat again: " << table.insert("cat") << '\n';

    return 0;
}
