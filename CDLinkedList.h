#ifndef CDLINKEDLIST_H
#define CDLINKEDLIST_H

#include <iostream>
#include <exception>

template<typename T>
class CDLinkedList {
public:
    struct Node {
        T elem;
        Node* next;
        Node* prev;

        Node() {}
        Node(T e) : elem(e), next(nullptr), prev(nullptr) {}
    };
public:
    class Iterator {
    public:
        const T& operator*() {
            return cursor->elem;
        }

        bool operator!=(const Iterator& it) const {
            return this->cursor != it.cursor;
        }

        bool operator==(const Iterator& it) const {
            return cursor == it.cursor;
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
        header = new Node();
        trailer = new Node();
        header->next = trailer;
        trailer->prev = header;
        size_ = 0;
    }

    CDLinkedList(const Node& node) : CDLinkedList() {
        insertFront(node.elem);
    }

    CDLinkedList(const CDLinkedList& list) : CDLinkedList() {
        for (CDLinkedList::Iterator it = list.begin(); it != list.end(); it++) {
            insertBack(*it);
        }
    }

    ~CDLinkedList() {
        while(!empty()) removeFront();
        delete header;
        delete trailer;
    }

    inline bool empty() const {
        return size_ == 0;
    }

    inline unsigned int size() const {
        return size_;
    }

    inline Iterator begin() const {
        return Iterator(header->next);
    }

    inline Iterator end() const {
        return Iterator(trailer);
    }

    inline void insertFront(const T& elem) {
        insert(begin(), elem);
    }

    inline void insertBack(const T& elem) {
        insert(end(), elem);
    }

    void insert(Iterator it, const T& elem) {
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

    inline void removeFront() {
        remove(begin());
    }   

    inline void removeBack() {
        remove(end());
    }

    void remove(Iterator it) {
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

    void print() {
        CDLinkedList<T>::Iterator it = begin();
        for (unsigned int i = 0; i < size_; i++) {
            std::cout << *it << " ";
            ++it;
        }
        std::cout << std::endl;
    }

private:
    Node* header;
    Node* trailer;
    unsigned int size_;
};

#endif //CDLINKEDLIST_H