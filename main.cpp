#include "CDLinkedList.h"
#include "test.h"
#include <exception>
#include <vector>

//template<> void CDLinkedList<char>::print();

template<typename T>
void printCounter() {
    std::cout << "\n"
              << __PRETTY_FUNCTION__
              << "\nCreated:"
              << CDLinkedList<T>::getCounterCreated()
              << "\nAlive:"
              << CDLinkedList<T>::getCounterAlive()
              << std::endl;
}

int main() {

    TestAll();
    CDLinkedList<int> l1;
    CDLinkedList<int> l2;

    printCounter<int>();
    printCounter<char>();
    

    return 0;
}
