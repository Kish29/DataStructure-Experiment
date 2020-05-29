#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include "stack.h"

template<class T>
class Queue {
private:
    Node<T> *head{};
    int size{};

    void copy(Node<T> *this_, Node<T> *other);

    void remove(Node<T> *node);

public:
    Queue();

    Queue(Queue &other);

    ~Queue();

    Queue &operator=(Queue &other);

    int get_size() const;

    void push(T *t);

    void push(Node<T> *n);

    Node<T> *pop();

    void print();

    Node<T> *back() const ;
    bool isEmpty() const ;
};


#include "queue.cpp"
#endif
