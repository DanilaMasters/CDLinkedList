#include "CDLinkedList.h"


CDLinkedList<char>::Iterator::Iterator(Node* v) {
    cursor = v;
}


char& CDLinkedList<char>::Iterator::operator*() const {
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

template<typename T>
CDLinkedList<T*>::Iterator::Iterator(Node* v) {
    cursor = v;
}

template<typename T>
T& CDLinkedList<T*>::Iterator::operator*() const {
    return cursor->elem;
}

template<typename T>
bool CDLinkedList<T*>::Iterator::operator!=(const CDLinkedList<T*>::Iterator& it) const {
    return this->cursor != it.cursor;
}

template<typename T>
bool CDLinkedList<T*>::Iterator::operator==(const CDLinkedList<T*>::Iterator& it) const {
    return cursor == it.cursor;
}

template<typename T>
typename CDLinkedList<T*>::Iterator& CDLinkedList<T*>::Iterator::operator++() {
    cursor = cursor->next;
    return *this;
}

template<typename T>
typename CDLinkedList<T*>::Iterator CDLinkedList<T*>::Iterator::operator++(int d) {
    Iterator old = *this;
    operator++();
    return old;
}

template<typename T>
typename  CDLinkedList<T*>::Iterator& CDLinkedList<T*>::Iterator::operator--() {
    cursor = cursor->prev;
    return *this;
}

template<typename T>
typename CDLinkedList<T*>::Iterator CDLinkedList<T*>::Iterator::operator--(int d) {
    Iterator old = *this;
    operator++();
    return old;
}