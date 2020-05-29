#include "queue.h"
#include <iostream>

template<class T>
Queue<T>::Queue() {
    head = nullptr;
    size = 0;
}

template<class T>
Queue<T>::Queue(Queue &other) {
    size = other.size;
    if (!other.head)
        head = new Node<T>();
    else {
        head = new Node<T>(*other.head);
        copy(this->head, other.head);
    }
}

template<class T>
Queue<T>::~Queue() {
    remove(head);
}

template<class T>
Queue<T> &Queue<T>::operator=(Queue &other) {
    size = other.size;
    if (!other.head)
        head = new Node<T>();
    else {
        head = new Node<T>(*other.head);
        copy(head, other.head);
    }
    return *this;
}

template<class T>
int Queue<T>::get_size() const {
    return size;
}

template<class T>
void Queue<T>::push(T *t) {
    if (!t)
        return;
    if (!head)
        head = new Node<T>(t);
    else {
        Node<T> *tmp = new Node<T>(t);
        tmp->set_next(head);
        head = tmp;
    }
    size++;
}

template<class T>
void Queue<T>::push(Node<T> *n) {
    if (!n)
        return;
    if (!head)
        head = new Node<T>(n->getValue());
    else {
        n->set_next(head);
        head = n;
    }
    size++;
}

template<class T>
Node<T> *Queue<T>::pop() {
    if (isEmpty())
        return nullptr;
    if (!head->get_next()) {
        Node<T> *temp = new Node<T>(head->getValue());
        head = nullptr;
        size--;
        return temp;
    }
    Node<T> *node = head;
    Node<T> *node2 = back();
    while (node->get_next() != node2) {
        node = node->get_next();
    }
    node->set_next(nullptr);
    size--;
    return node2;
}

template<class T>
void Queue<T>::print() {
    Node<T> *p = head;
    while (p) {
        p->print();
        p = p->get_next();
    }
    std::cout << "END\n";
}

template<class T>
void Queue<T>::copy(Node<T> *this_, Node<T> *other_) {
    if (!other_->get_next())
        return;
    this_->set_next(new Node<T>(*(other_->get_next())));
    copy(this_->get_next(), other_->get_next());
}

template<class T>
void Queue<T>::remove(Node<T> *node) {
    if (!node)
        return;
    if (!node->get_next()) {
        delete node;
        node = nullptr;
        return;
    }
    Node<T> *tmp = node->get_next();
    delete node;
    remove(tmp);
}

template<class T>
Node<T> *Queue<T>::back() const {
    if (isEmpty())
        return nullptr;
    Node<T> *temp = head;
    while (temp->get_next()) {
        temp = temp->get_next();
    }
    return temp;
}

template<class T>
bool Queue<T>::isEmpty() const {
    return head == nullptr;
}