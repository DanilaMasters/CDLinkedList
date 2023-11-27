#include "CDLinkedList.h"

template<typename T>
CDLinkedList<T>::Iterator::Iterator(Node* v) {
    cursor = v;
}

template<typename T>
const T& CDLinkedList<T>::Iterator::operator*() const {
    return cursor->elem;
}

template<typename T>
bool CDLinkedList<T>::Iterator::operator!=(const CDLinkedList<T>::Iterator& it) const {
    return this->cursor != it.cursor;
}


template<typename T>
bool CDLinkedList<T>::Iterator::operator==(const CDLinkedList<T>::Iterator& it) const {
    return cursor == it.cursor;
}

template<typename T>
typename CDLinkedList<T>::Iterator& CDLinkedList<T>::Iterator::operator++() {
    cursor = cursor->next;
    return *this;
}

template<typename T>
typename CDLinkedList<T>::Iterator CDLinkedList<T>::Iterator::operator++(int d) {
    Iterator old = *this;
    operator++();
    return old;
}

template<typename T>
typename  CDLinkedList<T>::Iterator& CDLinkedList<T>::Iterator::operator--() {
    cursor = cursor->prev;
    return *this;
}

template<typename T>
typename CDLinkedList<T>::Iterator CDLinkedList<T>::Iterator::operator--(int d) {
    Iterator old = *this;
    operator++();
    return old;
}

// template<typename T>
// std::ostream& operator<<(std::ostream& os, typename CDLinkedList<T>::Iterator& it) {
//     os << it.operator*();
//     return os;
// }