#include "CDLinkedList.h"
#include <exception>
#include <iostream>

template<typename T>
CDLinkedList<T>::CDLinkedList() {
    header = new Node;
    trailer = new Node;
    header->next = trailer;
    trailer->prev = header;
    size_ = 0;
}

template<typename T>
CDLinkedList<T>::CDLinkedList(const Node& node) : CDLinkedList() {
    insertFront(node->elem);
}

template<typename T>
CDLinkedList<T>::CDLinkedList(const CDLinkedList& list) : CDLinkedList() {
    for (CDLinkedList::Iterator it = list.begin(); it != list.end(); it++) {
        insertBack(*it);
    }
}

template<typename T>
CDLinkedList<T>::~CDLinkedList() {
    while(!empty()) remove();
    delete header;
    delete trailer;
}

template<typename T>
bool CDLinkedList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
unsigned int CDLinkedList<T>::size() const {
    return size_;
}

template<typename T>
typename CDLinkedList<T>::Iterator CDLinkedList<T>::begin() const {
    return CDLinkedList<T>::Iterator(header->next);
}

template<typename T>
typename CDLinkedList<T>::Iterator CDLinkedList<T>::end() const {
    return CDLinkedList<T>::Iterator(trailer);
}

template<typename T>
void CDLinkedList<T>::insertFront(const T& elem) {
    insert(begin(), elem);
}

template<typename T>
void CDLinkedList<T>::insertBack(const T& elem) {
    insert(end(), elem);
}

template<typename T>
void CDLinkedList<T>::insert(CDLinkedList<T>::Iterator& it, const T& elem) {
    Node* new_node = new Node;
    Node* node = *it;
    new_node->elem = elem;
    if (!size_) {
        new_node->next = new_node;
        new_node->prev = new_node;
        header->next = new_node;
        trailer->prev = new_node;
    }
    else {
        if (node == trailer && size_) {
            new_node->next = node->prev->next;
            new_node->prev = node->prev;
            node->prev->next->prev = new_node;
            node->prev->next = new_node;
            trailer->prev = new_node;
        } else {
            new_node->next = node;
            new_node->prev = node->prev;
            node->prev->next = new_node;
            node->prev = new_node;
            if (node == header->next) {
                header->next = new_node;
            }
        }
    }
    size_++;
}

template<typename T>
void CDLinkedList<T>::removeFront() {
    remove(begin());
}

template<typename T>
void CDLinkedList<T>::removeBack() {
    remove(end());
}


template<typename T>
void CDLinkedList<T>::remove(const CDLinkedList<T>::Iterator& it) {
    if (empty()) throw std::length_error("List is empty");
    T tmp = *it;
    Node* node = it.cursor;
    Node* u = node->prev;
    Node* w = node->next;
    u->next = w;
    w->prev = u;
    if (node == header->next) {
        header->next = header->next->next;
    } else if (node == trailer->prev) {
        trailer->prev = trailer->prev->prev;
    }
    delete node;
    size_--;
    return tmp;
}

template<typename T>
void CDLinkedList<T>::print() const {
    for (CDLinkedList<T>::Iterator it = begin(); it != end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template<typename T>
CDLinkedList<T>::Iterator::Iterator(Node* v) {
    cursor = v;
}

template<typename T>
const T& CDLinkedList<T>::Iterator::operator*() {
    return cursor->elem;
}

template<typename T>
bool CDLinkedList<T>::Iterator::operator!=(const CDLinkedList<T>::Iterator& it) const {
    return this->cursor != it->cursor;
}

template<typename T>
bool CDLinkedList<T>::Iterator::operator==(const CDLinkedList<T>::Iterator& it) const {
    return cursor == it->cursor;
}

template<typename T>
typename CDLinkedList<T>::Iterator& CDLinkedList<T>::Iterator::operator++() {
    cursor = cursor->next;
    return *this;
}

template<typename T>
typename CDLinkedList<T>::Iterator& CDLinkedList<T>::Iterator::operator--() {
    cursor = cursor->prev;
    return *this;
}