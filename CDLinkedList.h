#ifndef CDLINKEDLIST_H
#define CDLINKEDLIST_H

#include <ostream>
#include <iostream>
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
        Node(T e, Node* next = nullptr, Node* prev = nullptr) : elem(e), next(next), prev(prev) {}
        Node(const Node& node) {
            this->elem = node.elem;
            next = new Node();
            prev = new Node();
            next = node.next;
            prev = node.prev;
        }
    };
public:
    class Iterator {
    public:
        T& operator*() const;
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
    CDLinkedList(const Node&);
    CDLinkedList(std::initializer_list<T>);
    CDLinkedList(const CDLinkedList&);
    ~CDLinkedList();

    template<typename T1>
    CDLinkedList(const CDLinkedList<T1>&);

    inline bool empty() const { return size_ == 0; }
    inline unsigned int size() const { return size_; }
    inline Iterator begin() const { return Iterator(header->next); }
    inline Iterator end() const { return Iterator(trailer); }
    T& at(unsigned int ind) const;
    void insert(Iterator it, const T& elem);
    inline void insertFront(const T& elem) { insert(begin(), elem); }
    inline void insertBack(const T& elem) { insert(end(), elem); }
    void insertAtIndex(unsigned int ind, const T& e);
    void remove(Iterator it);
    inline void removeFront() { remove(begin()); }   
    inline void removeBack() { remove(end()); }
    void print() const;                                                                        // make const?
    void merge(CDLinkedList& list);
    void reverse();

    inline static unsigned int getCounterCreated() { return counterCreated; }
    inline static unsigned int getCounterAlive() { return counterAlive; }

    CDLinkedList<T>& operator=(const CDLinkedList<T>&);

    template<typename T1>
    CDLinkedList<T>& operator=(const CDLinkedList<T1>&);

    const T operator[](unsigned int index) const { 
        return at(index);
    }

    T& operator[](unsigned int index) {
        return at(index);
    }

    template<typename> friend class CDLinkedList;

    template<typename T1, typename T2>
    friend CDLinkedList<decltype(T1() + T2())> operator+(const CDLinkedList<T1>&, const CDLinkedList<T2>&);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const CDLinkedList<U>& list);
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
        char& operator*() const;
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
    char& at(unsigned int ind) const;
    void insert(Iterator it, const char elem);
    inline void insertFront(const char elem) { insert(begin(), elem); }
    inline void insertBack(const char elem) { insert(--end(), elem); }
    void insertAtIndex(unsigned int ind, char e);
    void remove(Iterator it);
    inline void removeFront() { remove(begin()); }   
    inline void removeBack() { remove(end()); }
    void print() const;
    void merge(CDLinkedList& list);
    void reverse();

    char operator[](unsigned int index) const {
        return at(index);
    }

    char& operator[](unsigned int index) {
        return at(index);
    }

    friend std::ostream& operator<<(std::ostream&, const CDLinkedList<char>&);

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

template<typename T>
class CDLinkedList<T*> {
public:
    class Node {
        T elem{};
        Node* next{};
        Node* prev{};
    public:
        Node() = default;
        Node(T elem, Node* next = nullptr, Node* prev = nullptr) : elem(elem), next(next), prev(prev) {}
    };
    class Iterator {
    private:
        Node* cursor;
        explicit Iterator(const Node* cursor) : cursor(cursor) {}
    public:
        inline const T operator*() const { return cursor->elem; }
        inline Iterator& operator++() { return cursor->next; }

        friend class CDLinkedList;
    };

    CDLinkedList() {
        header = new Node();
        trailer = new Node();
        header->next = trailer;
        trailer->prev = header;
        size_ = 0;
    }
    ~CDLinkedList() {
        while(!empty()) remove(header->next);
        delete header;
        delete trailer;
    }

    bool empty() { return size_ == 0; }
    void insert(Iterator it, const char elem) {
        
    }
    void remove(Iterator& it) {
        if (empty()) throw std::length_error("List is empty");
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
    }
private:
    Node* header;
    Node* trailer;
    std::size_t size_;
};

#include "CDLinkedList.inl"
#include "CDLinkedListS.inl"
#include "ListIterator.inl"
#include "ListIteratorS.inl"

#endif //CDLINKEDLIST_H