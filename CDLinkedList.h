#ifndef CDLINKEDLIST_H
#define CDLINKEDLIST_H

#include <iostream>
#include <exception>

template<typename T>
class CDLinkedList {
public:
    class Node {
        T elem;
        Node* next;
        Node* prev;
        friend class CDLinkedList;
    public:
        explicit Node(T e) {
            elem = e;
            next = nullptr;
            prev = nullptr;
        }
    };
public:
    class Iterator {
    public:
        const T& operator*() {
            for (CDLinkedList<T>::Iterator it = begin(); it != end(); it++) {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }

        bool operator!=(const Iterator& it) const {
            return this->cursor != it->cursor;
        }

        bool operator==(const Iterator& it) const {
            return cursor == it->cursor;
        }

        Iterator& operator++() {
            cursor = cursor->next;
            return *this;
        }

        Iterator& operator--() {
            cursor = cursor->prev;
            return *this;
        }

        friend class CDLinkedList;
    private:
        explicit Iterator(Node* v) {
            cursor = v;
        }

        Node* cursor;
    };
public:
    CDLinkedList() {
        header = new Node;
        trailer = new Node;
        header->next = trailer;
        trailer->prev = header;
        size_ = 0;
    }

    ~CDLinkedList() {
        while(!empty()) remove();
        delete header;
        delete trailer;
    }

    CDLinkedList(const Node& node) : CDLinkedList() {
        insertFront(node->elem);
    }

    CDLinkedList(const CDLinkedList& list) : CDLinkedList() {
        for (CDLinkedList::Iterator it = list.begin(); it != list.end(); it++) {
            insertBack(*it);
        }
    }

    bool empty() const {
        return size_ == 0;
    }

    unsigned int size() const {
        return size_;
    }

    Iterator begin() const {
        return CDLinkedList<T>::Iterator(header->next);
    }

    Iterator end() const {
        return CDLinkedList<T>::Iterator(trailer);
    }

    void insertFront(const T& elem) {
        insert(begin(), elem);
    }

    void insertBack(const T& elem) {
        insert(end(), elem);
    }

    void insert(Iterator& it, const T& elem) {
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

    void removeFront() {
        remove(begin());
    }   

    void removeBack() {
        remove(end());
    }

    void remove(const Iterator& it) {
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

    void print() const {
        for (CDLinkedList<T>::Iterator it = begin(); it != end(); it++) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

private:
    Node* header;
    Node* trailer;
    unsigned int size_;
};

#endif //CDLINKEDLIST_H