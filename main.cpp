#include "CDLinkedList.h"
#include "test.h"
#include <exception>
#include <vector>

template<> void CDLinkedList<char>::print();

int main() {

    TestAll();
    CDLinkedList<int> l1;
    CDLinkedList<int> l2;


    std::cout << "Created: " << CDLinkedList<int>::getCounterCreated() << "\n" << "Alive: " << CDLinkedList<int>::getCounterAlive()  <<std::endl;

    return 0;
}
