#ifndef CDLINKEDLIST_H
#define CDLINKEDLIST_H


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
        const T& operator*();
        bool operator!=(const Iterator& it) const;
        bool operator==(const Iterator& it) const;
        Iterator& operator++();
        Iterator& operator--();
        friend class CDLinkedList;
    private:
        explicit Iterator(Node* v);
        Node* cursor;
    };
public:
    CDLinkedList();
    CDLinkedList(const Node& node);
    CDLinkedList(const CDLinkedList& list);
    ~CDLinkedList();

    inline bool empty() const { return size_ == 0; }
    inline unsigned int size() const { return size_; }
    inline Iterator begin() const { return Iterator(header->next); }
    inline Iterator end() const { return Iterator(trailer); }
    T at(unsigned int ind) const;
    void insert(Iterator it, const T& elem);
    inline void insertFront(const T& elem) { insert(begin(), elem); }
    inline void insertBack(const T& elem) { insert(end(), elem); }
    void insertAtIndex(unsigned int ind, const T& e);
    void remove(Iterator it);
    inline void removeFront() { remove(begin()); }   
    inline void removeBack() { remove(end()); }
    void print();                                                                        // make const?
    void merge(CDLinkedList& list);
    void reverse();

    inline static unsigned int getCounterCreated() { return counterCreated; }
    inline static unsigned int getCounterAlive() { return counterAlive; }
private:
    Node* header;
    Node* trailer;
    unsigned int size_;

    static unsigned int counterCreated;
    static unsigned int counterAlive;
};

template<typename T> unsigned int CDLinkedList<T>::counterCreated(0);
template<typename T> unsigned int CDLinkedList<T>::counterAlive(0);

#include "CDLinkedList.inl"
#include "ListIterator.inl"

#endif //CDLINKEDLIST_H