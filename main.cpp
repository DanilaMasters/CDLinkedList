#include "CDLinkedList.h"

int main() {

    CDLinkedList<int>::Node node(0);
    CDLinkedList<int> list(node);

    list.print();
	//hello world

    return 0;
}
