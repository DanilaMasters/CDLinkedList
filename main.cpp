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

int main(int argc, char* argv[]) {
    bool runCounter = false;
    if (argc > 1) {
        switch(argc) {
            case 2:
                if (*argv[1] == 't') {
                    TestAll();
                }
                if (*argv[1] == 'c') {
                    runCounter = true;
                }
                break;
            case 3:
                if ((*argv[1] == 't' && *argv[2] == 'c') || (*argv[2] == 't' && *argv[1] == 'c')) {
                    TestAll();
                    runCounter = true;
                }

        }
    }


    CDLinkedList<float> l1 = {5.7, 4.4, 2.4, 4};
    CDLinkedList<double> l2 = {1, 2, 3, 4};

    std::cout << l2 + l1 << std::endl;

    CDLinkedList<int*> l3;
    l3.insert(l3.begin(), 4);
    l3.insert(l3.begin(), 5);
    std::cout << l3 << std::endl;

    CDLinkedList<char> l4{'h', 'e', 'l', 'l', 'o'};

    std::cout << std::endl;
    l2.append(l1);
    std::cout << "l2 = " << l2 << std::endl;

    l1.append(l2);
    std::cout << "l1 = " << l1 << std::endl;

    l3.append(l2);
    std::cout << "l3 = " << l3 << std::endl;

    CDLinkedList<int> l5{32, 87, 79, 82, 76, 68, 33};

    l4.append(l5);
    std::cout << "l4 = " << l4 << std::endl;

    l1.print(); // float
    l2.print(); // int
    l4.print(); // char

    CDLinkedList<double> l11{1.1, 2.4, 6.7, 1.8};
    CDLinkedList<int> l22{8, 4};
    l11 = l22;

    std::cout << l11 << std::endl;

    if (runCounter) {
        printCounter<int>();
        printCounter<char>();
        printCounter<int*>();
    }

    return 0;
}
