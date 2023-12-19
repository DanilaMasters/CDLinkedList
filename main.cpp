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
    CDLinkedList<int> l1;
    CDLinkedList<int> l2;

    if (runCounter) {
        printCounter<int>();
        printCounter<char>();
    }

    return 0;
}
