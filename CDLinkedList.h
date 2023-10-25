#ifndef CDLINKEDLIST_H
#define CDLINKEDLIST_H


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
        const T& operator*();
        bool operator!=(const Iterator&) const;
        bool operator==(const Iterator&) const;
        Iterator& operator++();
        Iterator& operator--();
        friend class CDLinkedList;
    private:
        explicit Iterator(Node*);
        Node* cursor;
    };
public:
    CDLinkedList();
    ~CDLinkedList();
    CDLinkedList(const Node&);
    CDLinkedList(const CDLinkedList&);

    bool empty() const;
    unsigned int size() const;
    Iterator begin() const;
    Iterator end() const;

    void insertFront(const T&);
    void insertBack(const T&);
    void insert(Iterator&, const T&);

    void removeFront();
    void removeBack();
    void remove(const Iterator&);

    void print() const;

private:
    Node* header;
    Node* trailer;
    unsigned int size_;
};

#endif //CDLINKEDLIST_H