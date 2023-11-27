#include "CDLinkedList.h"
#include <iostream>
#include <exception>
#include <sstream>

CDLinkedList<char>::CDLinkedList() {
    header = new Node();
    trailer = new Node();
    header->next = trailer;
    trailer->prev = header;
    size_ = 0;
    
    counterCreated++;
    counterAlive++;
    insertBack('\0');
}


CDLinkedList<char>::CDLinkedList(const Node& node) : CDLinkedList() {
    insertFront(node.elem);
}


CDLinkedList<char>::CDLinkedList(std::initializer_list<char> list) : CDLinkedList() {
    for (auto item : list) {
        insertBack(item);
    }
}


CDLinkedList<char>::CDLinkedList(const CDLinkedList& list) : CDLinkedList() {
    for (CDLinkedList<char>::Iterator it = list.begin(); it != list.end(); it++) {
        insertBack(*it);
    }
}


CDLinkedList<char>::~CDLinkedList() {
    while(!empty()) removeFront();
    delete header;
    delete trailer;
    counterAlive--;
}


char CDLinkedList<char>::at(unsigned int ind) const {
    CDLinkedList<char>::Iterator it = begin();
    unsigned int j = 0;
    while (j++ < ind) {
        ++it;
    }
    return *it;
}


void CDLinkedList<char>::insert(CDLinkedList<char>::Iterator it, const char elem) {
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


void CDLinkedList<char>::insertAtIndex(unsigned int ind, const char e) {
    if (ind >= size_ && size_ != 0) {
        std::ostringstream os;
        os << "Index exceeds list size" << std::endl;
        throw std::out_of_range(os.str());
    } else {
        unsigned int j = 0;
        CDLinkedList<char>::Iterator it = begin();
        while (j++ < ind) {
            ++it;
        }
        insert(it, e);
    }   
}


void CDLinkedList<char>::remove(CDLinkedList<char>::Iterator it) {
    if (empty()) throw std::length_error("List is empty");
    //char tmp = *it;
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


void CDLinkedList<char>::print() {
    CDLinkedList<char>::Iterator it = begin();
    for (unsigned int i = 0; i < size_; i++) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}

// 
// void CDLinkedList<char>::print() {
//     CDLinkedList<char>::Iterator it = begin();
//     for (unsigned int i = 0; i < size_; i++) {
//         std::cout << *it;
//         ++it;
//     }
//     std::cout << std::endl;
// }


void CDLinkedList<char>::merge(CDLinkedList& list) {
    CDLinkedList<char>::Iterator it = list.begin();
    unsigned int i = 0;
    while (i++ < list.size()) {
        this->insertBack(*it);
        ++it;
    }
}


void CDLinkedList<char>::reverse() {
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