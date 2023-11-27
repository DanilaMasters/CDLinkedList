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
CDLinkedList<T>::CDLinkedList(const CDLinkedList& list) : CDLinkedList() {
    for (CDLinkedList<T>::Iterator it = list.begin(); it != list.end(); it++) {
        insertBack(*it);
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
T CDLinkedList<T>::at(unsigned int ind) const {
    CDLinkedList<T>::Iterator it = begin();
    unsigned int j = 0;
    while (j++ < ind) {
        ++it;
    }
    return *it;
}

template<typename T>
void CDLinkedList<T>::insert(CDLinkedList<T>::Iterator it, const T& elem) {
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
void CDLinkedList<T>::insertAtIndex(unsigned int ind, const T& e) {
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
void CDLinkedList<T>::print() {
    CDLinkedList<T>::Iterator it = begin();
    for (unsigned int i = 0; i < size_; i++) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}

// template<>
// void CDLinkedList<char>::print() {
//     CDLinkedList<char>::Iterator it = begin();
//     for (unsigned int i = 0; i < size_; i++) {
//         std::cout << *it;
//         ++it;
//     }
//     std::cout << std::endl;
// }

template<typename T>
void CDLinkedList<T>::merge(CDLinkedList& list) {
    CDLinkedList<T>::Iterator it = list.begin();
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

template<typename T, typename U>
decltype(auto) merge(T& t, U& u) {
    typename T::Iterator it1 = t.begin();
    typename U::Iterator it2 = u.begin();
    CDLinkedList<decltype(*it1 + *it2)> res;

    for (unsigned int i = 0; i < t.size(); i++) {
        res.insertBack(t.at(i));
    }

    for (unsigned int i = 0; i < u.size(); i++) {
        res.insertBack(u.at(i));
    }

    return res;
}