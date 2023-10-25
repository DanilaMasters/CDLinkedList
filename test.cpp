#include "CDLinkedList.h"
#include "test.h"
#include <exception>
#include <sstream>
#include <iostream>

template<typename T, typename C>
void AssertEqual(const T& t, const C& c, const std::string& hint) {
    if (t != c) {
        std::ostringstream os;
        os << "Assertion failed: " << t << "!=" << c << " Hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

void TestInsert() {
    {
        CDLinkedList<int> l;
        l.insertFront(0);
        AssertEqual(l.begin().operator*(), 0, "Inserting and extracting 0");
        AssertEqual(l.size(), 1u, "Size comparasion");
    }
    std::cout << "TEST Insertion OK" << std::endl;
}

void TestRemove() {
    {
        CDLinkedList<int> l;
        l.insertFront(1);
        l.insertFront(2);
        l.removeFront();
        AssertEqual(l.size(), 1u, "Removing from front");
    }
    std::cout << "TEST Removing OK" << std::endl;
}

void TestAll() {
    TestInsert();
    TestRemove();

    std::cout << "ALL TESTS OK" << std::endl;
}