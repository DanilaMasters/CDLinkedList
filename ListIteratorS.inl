#include "CDLinkedList.h"


CDLinkedList<char>::Iterator::Iterator(Node* v) {
    cursor = v;
}


const char& CDLinkedList<char>::Iterator::operator*() const {
    return cursor->elem;
}


bool CDLinkedList<char>::Iterator::operator!=(const CDLinkedList<char>::Iterator& it) const {
    return this->cursor != it.cursor;
}



bool CDLinkedList<char>::Iterator::operator==(const CDLinkedList<char>::Iterator& it) const {
    return cursor == it.cursor;
}


typename CDLinkedList<char>::Iterator& CDLinkedList<char>::Iterator::operator++() {
    cursor = cursor->next;
    return *this;
}


typename CDLinkedList<char>::Iterator CDLinkedList<char>::Iterator::operator++(int d) {
    Iterator old = *this;
    operator++();
    return old;
}


typename  CDLinkedList<char>::Iterator& CDLinkedList<char>::Iterator::operator--() {
    cursor = cursor->prev;
    return *this;
}


typename CDLinkedList<char>::Iterator CDLinkedList<char>::Iterator::operator--(int d) {
    Iterator old = *this;
    operator++();
    return old;
}

// 
// std::ostream& operator<<(std::ostream& os, typename CDLinkedList<char>::Iterator& it) {
//     os << it.operator*();
//     return os;
// }