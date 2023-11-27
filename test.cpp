#include "CDLinkedList.h"
#include "test.h"
#include <exception>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

template<typename T, typename C>
void AssertEqual(const T& t, const C& c, const std::string& hint) {
    if (t != c) {
        std::ostringstream os;
        os << "Assertion failed: " << t << "!=" << c << " Hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

void TestConstructors() {
    {
        CDLinkedList<int> l;
        AssertEqual(l.size(), 0u, "Error: size != 0");
        AssertEqual(l.begin(), l.end(), "Error: header->next != trailer->prev");
    }

    {
        CDLinkedList<int>::Node node(5);
        CDLinkedList<int> l(node);
        AssertEqual(l.begin().operator*(), 5, "Error: node based constructor");
    }  

    {
        CDLinkedList<int> l({ 1, 2, 3, 4 });
        const int values[] = { 1, 2 ,3, 4 };
        for (unsigned int i = 0; i < l.size(); i++) {
            AssertEqual(l.at(i), values[i], "Error: constructor with initializer list");
        }
    }

    {
        CDLinkedList<char> l;
        AssertEqual(l.begin().operator*(), '\0', "Error: char constructor specialization");
    }

    std::cout << "TESTS Constructors OK" << std::endl;
}

void TestInsert() {
    {
        CDLinkedList<int> l;
        l.insertFront(0);
        AssertEqual(l.begin().operator*(), 0, "Inserting and extracting 0");
        AssertEqual(l.size(), 1u, "Size comparasion");
    }

    {
        CDLinkedList<int> l;
        l.insertFront(1);
        l.insertFront(2);
        l.insertFront(3);
        l.insertFront(4);

        l.insertAtIndex(0, 5);
        AssertEqual(l.begin().operator*(), 5, "insertAtIndex 0 value 1");
        l.insertAtIndex(3, 7);
        AssertEqual(l.at(3), 7, "insertAtIndex 3 value 7");
    }

    
    {
        CDLinkedList<char> l;
        const char symbols[] = {'h', 'e', 'l', 'l', 'o'};
        unsigned int i = 0;
        while (symbols[i] != '\0') {
            l.insertBack(symbols[i]);
            AssertEqual(l.at(i), symbols[i], "Insert chars");
            i++;
        }
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

void TestMerge() {
    {
        std::vector<int> values1 = {0, 1, 2};
        CDLinkedList<int> l1;
        for (unsigned int i = 0; i < values1.size(); i++) {
            l1.insertBack(values1[i]);
        }
        
        std::vector<int> values2 = {3, 4, 5};
        CDLinkedList<int> l2;
        for (unsigned int i = 0; i < values2.size(); i++) {
            l1.insertBack(values2[i]);
        }

        l1.merge(l2);

        std::vector<int> values;
        values.reserve(values1.size() + values2.size());
        values.insert(values.begin(), values1.begin(), values1.end());
        values.insert(values.end(), values2.begin(), values2.end());

        //values.insert(values.begin(), 4);

        for (unsigned int i = 0; i < l1.size(); i++) {
            AssertEqual(l1.at(i), values[i], "Merging two lists");
        }
    }
    std::cout << "TEST Merge OK" << std::endl;
}

void TestReverse() {
    {
        std::vector<int> values = {1, 2, 3};
        CDLinkedList<int> l;
        for (unsigned int i = 0; i < values.size(); i++) {
            l.insertBack(values[i]);
        }



        l.reverse();
        std::reverse(begin(values), end(values));
        for (unsigned int i = 0; i < values.size(); i++) {
            AssertEqual(l.at(i), values[i], "Reversing list");
        }
    }
    std::cout << "TEST Reverse OK" << std::endl;
}

void TestAll() {

    std::vector<std::function<void()>> tests = { TestConstructors, TestInsert, TestRemove, TestMerge, TestReverse };
    unsigned int count = tests.size();
    for (auto& test : tests) {
        try {
            test();
        } catch (const std::runtime_error& ex) {
            count--;
            std::cout << ex.what() << std::endl;
        }
    }
    std::cout << "\n***\n" << "DONE " << count << "/" << tests.size() <<  " GROUPED TESTS\n***" << std::endl;
}