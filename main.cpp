#include "CDLinkedList.h"
#include "test.h"

int main() {

    TestAll();

    CDLinkedList<int>::Node node(0);
    CDLinkedList<int> list(node);

    list.print();
	
    list.insertFront(1);
    list.insertFront(2);

    list.insertBack(2);

    list.print();

    return 0;
}
