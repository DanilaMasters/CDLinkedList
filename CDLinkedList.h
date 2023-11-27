#ifndef CDLINKEDLIST_H
#define CDLINKEDLIST_H

#include <ostream>
#include <initializer_list>

template<typename T>
class CDLinkedList {
public:
    class Node {
    private:
        T elem;
        Node* next;
        Node* prev;
        friend class CDLinkedList;
    public:
        Node() = default;
        Node(T e) : elem(e), next(nullptr), prev(nullptr) {}
    };
public:
    class Iterator {
    public:
        const T& operator*() const;
        bool operator!=(const Iterator& it) const;
        bool operator==(const Iterator& it) const;
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        friend class CDLinkedList;
        friend std::ostream& operator<<(std::ostream& os, const Iterator& it) {
            os << *it;
            return os;
        }
    private:
        explicit Iterator(Node* v);
        Node* cursor;
    };
public:
    CDLinkedList();
    CDLinkedList(const Node& node);
    CDLinkedList(std::initializer_list<T>);
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

template<>
class CDLinkedList<char>{
    public:
    class Node {
    private:
        char elem;
        Node* next;
        Node* prev;
        friend class CDLinkedList;
    public:
        Node() = default;
        Node(char e) : elem(e), next(nullptr), prev(nullptr) {}
    };
public:
    class Iterator {
    public:
        const char& operator*() const;
        bool operator!=(const Iterator& it) const;
        bool operator==(const Iterator& it) const;
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        friend class CDLinkedList;
        friend std::ostream& operator<<(std::ostream& os, const Iterator& it) {
            os << *it;
            return os;
        }
    private:
        explicit Iterator(Node* v);
        Node* cursor;
    };
public:
    CDLinkedList();
    CDLinkedList(const Node& node);
    CDLinkedList(std::initializer_list<char>);
    CDLinkedList(const CDLinkedList& list);
    ~CDLinkedList();

    inline bool empty() const { return size_ == 0; }
    inline unsigned int size() const { return size_; }
    inline Iterator begin() const { return Iterator(header->next); }
    inline Iterator end() const { return Iterator(trailer); }
    char at(unsigned int ind) const;
    void insert(Iterator it, const char elem);
    inline void insertFront(const char elem) { insert(begin(), elem); }
    inline void insertBack(const char elem) { insert(--end(), elem); }
    void insertAtIndex(unsigned int ind, char e);
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

unsigned int CDLinkedList<char>::counterCreated(0);
unsigned int CDLinkedList<char>::counterAlive(0);

#include "CDLinkedList.inl"
#include "CDLinkedListS.inl"
#include "ListIterator.inl"
#include "ListIteratorS.inl"

#endif //CDLINKEDLIST_H