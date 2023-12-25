#include "CDLinkedList.h"
#include <exception>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>

#define EPSILON 0.0000001

template<typename T, typename C>
void AssertEqual(const T& t, const C& c, const std::string& hint) {
    if (t != c) {
        std::ostringstream os;
        os << "Assertion failed: " << t << "!=" << c << " Hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

template<>
void AssertEqual(const double& lhs, const double& rhs, const std::string& hint) {
    if (lhs - rhs > EPSILON) {
        std::ostringstream os;
        os << "Assertion failed: " << lhs << "!=" << rhs << " Hint: " << hint;
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
            AssertEqual(l[i], values[i], "Error: constructor with initializer list");
        }
    }

    {
        CDLinkedList<int> l1({1, 2, 3 ,4});
        CDLinkedList<int> l2(l1);
        AssertEqual(l1.size(), l2.size(), "Error: sizes are not equal");
        for (unsigned int i = 0; i < l2.size(); i++) {
            AssertEqual(l1[i], l2[i], "Error: copy constructor");
        }
    }

    {
        CDLinkedList<char> l;
        AssertEqual(l.begin().operator*(), '\0', "Error: char constructor specialization");
    }

    {
        CDLinkedList<double> l1({1.1, 2.2, 3.3 , 4.4});
        CDLinkedList<int> l2(l1);
        const int values[] = {1, 2, 3, 4};
        AssertEqual(l1.size(), l2.size(), "Error: sizes are not equal");
        for (unsigned int i = 0; i < l2.size(); i++) {
            AssertEqual(l2[i], values[i], "Error: copy constructor with type conversion");
        }
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

        l1.append(l2);

        std::vector<int> values;
        values.reserve(values1.size() + values2.size());
        values.insert(values.begin(), values1.begin(), values1.end());
        values.insert(values.end(), values2.begin(), values2.end());

        //values.insert(values.begin(), 4);

        for (unsigned int i = 0; i < l1.size(); i++) {
            AssertEqual(l1.at(i), values[i], "Merging two lists");
        }
    }

    {
        CDLinkedList<int> l1({ 1, 2, 3, 4 });
        CDLinkedList<double> l2({ 5.6, 6.5, 7.3, 8.99 });

        l1.append(l2);
        
        double resArray[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

        for (unsigned int i = 0; i < l1.size(); i++) {
            AssertEqual(l1[i], resArray[i], "Error: array merge funciton");
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

void TestPrint() {
    {   
        std::string result("1 2 3 4");
        CDLinkedList<int> l = {1, 2, 3, 4};
        std::ostringstream os;
        os << l;
        AssertEqual(os.str().compare(result), 0, "Error: operator<<");
    }

    {
        const char result[] = {'h', 'e', 'l', 'l', 'o'};
        CDLinkedList<char> l = {'h', 'e', 'l', 'l', 'o'};
        std::ostringstream os;
        os << l;
        int i = 0;
        while (l.at(i) != '\0') {
            AssertEqual(result[i], os.str()[i], "Error:: operator<< for char");
            i++;
        }
    }

    std::cout << "TEST Print OK" << std::endl;
}

void TestCopyAssignment() {
    {
        CDLinkedList<int> l1{1, 2, 3, 4};
        CDLinkedList<int> l2{5, 6, 7, 8, 9 ,10};

        l1 = l2;

        AssertEqual(l1.size(), l2.size(), "Error: sizes are not equal");

        for (unsigned int i = 0; i < l1.size(); i++) {
            AssertEqual(l1[i], l2[i], "Error: values are not equal");
        }
    }

    {
        CDLinkedList<double> l1{1.1, 2.4, 6.7, 1.8};
        CDLinkedList<int> l2{8, 4};
        const int values[] = {1, 2, 6, 1};
        l2 = l1;
        
        AssertEqual(l1.size(), l2.size(), "Error: sizes are not equal");

        for (unsigned int i = 0; i < l2.size(); i++) {
            AssertEqual(l2[i], values[i], "Error: values are not equal");
        }
    }
    
    std::cout << "TEST CopyAssignment OK" << std::endl;
}

void TestSum() {
    {   
        CDLinkedList<double> l1{4.6, 2.9};
        CDLinkedList<double> l2{1.1, 2.2};

        CDLinkedList<double> res = l1 + l2;

        const double values[] = {5.7, 5.1};

        for (unsigned int i = 0; i < res.size(); i++) {
            AssertEqual(res[i], values[i], "Error: sum values are not equal");
        }
    }

    {
        CDLinkedList<int> l1{1, 2};
        CDLinkedList<double> l2{1.1, 2.2};

        CDLinkedList<double> res = l2 + l1;

        const double values[] = {2.1, 4.2};

        for (unsigned int i = 0; i < res.size(); i++) {
            AssertEqual(res[i], values[i], "Error: sum values are not equal");
        }
    }

    std::cout << "TEST Sum OK" << std::endl;
}

void TestAll() {

    std::vector<std::function<void()>> tests = {
            TestConstructors,
            TestInsert,
            TestRemove,
            TestMerge,
            TestReverse,
            TestPrint,
            TestCopyAssignment,
            TestSum
        };
    unsigned int count = tests.size();
    for (auto& test : tests) {
        try {
            test();
        } catch (const std::runtime_error& ex) {
            count--;
            std::cout << ex.what() << std::endl;
        }
    }
    std::cout << "\n************************\n" << "DONE " << count << "/" << tests.size() <<  " GROUPED TESTS\n************************" << std::endl;
}