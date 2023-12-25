#include "CDLinkedList.h"
#include <iostream>
#include <exception>
#include <sstream>

template<typename T>
CDLinkedList<T>::CDLinkedList() {
    header = new Node();
    trailer = new Node();
    header->next = trailer;
    trailer->prev = header;
    size_ = 0;
    
    counterCreated++;
    counterAlive++;
}

template<typename T>
CDLinkedList<T>::CDLinkedList(const Node& node) : CDLinkedList() {
    insertFront(node.elem);
}

template<typename T>
CDLinkedList<T>::CDLinkedList(std::initializer_list<T> list) : CDLinkedList() {
    for (auto item : list) {
        insertBack(item);
    }
}

template<typename T>
CDLinkedList<T>::CDLinkedList(const CDLinkedList<T>& list) : CDLinkedList() {
    for (unsigned int i = 0; i < list.size(); i++) {
        insertBack(list[i]);
    }
}

template<typename T>
    template<typename T1>
CDLinkedList<T>::CDLinkedList(const CDLinkedList<T1>& list) : CDLinkedList() {
    for (unsigned int i = 0; i < list.size(); i++) {
        insertBack(list[i]);
    }
}

template<typename T>
CDLinkedList<T>::~CDLinkedList() {
    while(!empty()) removeFront();
    delete header;
    delete trailer;
    counterAlive--;
}

template<typename T>
T& CDLinkedList<T>::at(unsigned int ind) const {
    CDLinkedList<T>::Iterator it = begin();
    unsigned int i = 0;
    while (i++ != ind) {
        it++;
    }
    return *it;
}

template<typename T>
void CDLinkedList<T>::insert(CDLinkedList<T>::Iterator it, const T elem) {
    Node* new_node = new Node();
    Node* node = it.cursor;
    new_node->elem = elem;
    if (!size_) {
        new_node->next = new_node;
        new_node->prev = new_node;
        header->next = new_node;
        trailer->prev = new_node;
    }
    else {
        if (it.cursor== trailer && size_) {
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
            if (it.cursor== header->next) {
                header->next = new_node;
            }
        }
    }
    size_++;
}

template<typename T>
void CDLinkedList<T>::insertAtIndex(unsigned int ind, const T e) {
    if (ind >= size_ && size_ != 0) {
        std::ostringstream os;
        os << "Index exceeds list size" << std::endl;
        throw std::out_of_range(os.str());
    } else {
        unsigned int j = 0;
        CDLinkedList<T>::Iterator it = begin();
        while (j++ < ind) {
            ++it;
        }
        insert(it, e);
    }   
}

template<typename T>
void CDLinkedList<T>::remove(CDLinkedList<T>::Iterator it) {
    if (empty()) throw std::length_error("List is empty");
    //T tmp = *it;
    Node* u = it.cursor->prev;
    Node* w = it.cursor->next;
    u->next = w;
    w->prev = u;
    if (it.cursor== header->next) {
        header->next = header->next->next;
    } else if (it.cursor== trailer->prev) {
        trailer->prev = trailer->prev->prev;
    }
    delete it.cursor;
    size_--;
    //return tmp;
}

template<typename T>
void CDLinkedList<T>::print() const {
    std::cout << "Base template" << std::endl;
    CDLinkedList<T>::Iterator it = begin();
    for (unsigned int i = 0; i < size_; i++) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}

template<>
void CDLinkedList<int>::print() const {
    std::cout << "Method spec for int" << std::endl;
    CDLinkedList<int>::Iterator it = begin();
    for (unsigned int i = 0; i < size_; i++) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}

template<typename T>
    template<typename U>
void CDLinkedList<T>::append(CDLinkedList<U>& list) {
    std::cout << "Base template" << std::endl;
    typename CDLinkedList<U>::Iterator it = list.begin();
    unsigned int i = 0;
    while (i++ < list.size()) {
        this->insertBack(*it);
        ++it;
    }
}


template<typename T>
void CDLinkedList<T>::reverse() {
    Node* temp = header;
    header = trailer;
    trailer = temp; 
   
    Node* current = header; 

    for (unsigned int i = 0; i < size_; i++) {
        temp = current->next; 
        current->next = current->prev; 
        current->prev = temp; 
        current = current->next;
    }
}

template<typename T>
CDLinkedList<T>& CDLinkedList<T>::operator=(const CDLinkedList<T>& other) {
    CDLinkedList<T> tmp(other);
    std::swap(tmp.header->next, header->next);
    std::swap(tmp.trailer->prev, trailer->prev);
    if (size_ != tmp.size_) {
        unsigned int tmpSize = size_;
        size_ = tmp.size_;
        tmp.size_ = tmpSize;
    }

    return *this;
}

template<typename T>
    template<typename T1>
CDLinkedList<T>& CDLinkedList<T>::operator=(const CDLinkedList<T1>& other) {
    operator=((CDLinkedList<T>)other);
    return *this;
}

template<typename T1, typename T2>
CDLinkedList<decltype(T1() + T2())> operator+(const CDLinkedList<T1>& lhs, const CDLinkedList<T2>& rhs) {
    if (lhs.size_ != rhs.size_) throw std::runtime_error("Cannot sum two lists with different sizes");
    CDLinkedList<decltype(T1() + T2())> tmp;
    for (unsigned int i = 0; i < lhs.size_; i++) {
        tmp.insertBack(lhs[i] + rhs[i]);
    }
    return tmp;
}

template<>
CDLinkedList<int> operator+(const CDLinkedList<int>& lhs, const CDLinkedList<int>& rhs) {
    if (lhs.size_ != rhs.size_) throw std::runtime_error("Cannot sum two char lists with differenr sizes");
    CDLinkedList<char> tmp;
    for (std::size_t i = 0; i < lhs.size_; i++) {
        tmp.insertBack(lhs[i] + rhs[i]);
    }
    return tmp;
}


template<typename T>
std::ostream& operator<<(std::ostream& os, const CDLinkedList<T>& list) {
    typename CDLinkedList<T>::Iterator it = list.begin();
    for (unsigned int i = 0; i < list.size(); i++) {
        os << *it;
        if (i != list.size() - 1)
            os << " ";
        ++it;
    }
    return os;
}

template<typename T>
const T CDLinkedList<T>::operator[](unsigned int index) const { 
    return at(index);
}

template<typename T>
T& CDLinkedList<T>::operator[](unsigned int index) {
    return at(index);
}