#include "stack.h"
#include <iostream>

template<class T>
Node<T>::Node() {
    ptr = NULL;
    next = NULL;
}

template<class T>
Node<T>::Node(Node<T> &other) {
    next = NULL;
    if (other.ptr)
        ptr = new T(*(other.ptr));
    else
        ptr = nullptr;
}

template<class T>
Node<T> &Node<T>::operator=(Node<T> &other) {
    next = NULL;
    if (other.ptr)
        ptr = new T(*(other.ptr));
    else
        ptr = nullptr;
    return *this;
}

template<class T>
Node<T>::Node(T *t) {
    ptr = t;
    next = NULL;
}

template<class T>
Node<T>::~Node() {
    if (ptr != NULL) {
        delete ptr;
    }
}

template<class T>
Node<T> *Node<T>::get_next() const {
    return next;
}

template<class T>
void Node<T>::set_next(Node<T> *n) {
    next = n;
}

template<class T>
void Node<T>::print() {
    if (ptr)
        std::cout << "[" << *ptr << "]->";
}

template<class T>
T *Node<T>::getValue() const {
    return this->ptr;
}

/*
The whole stack was essentially a singlely linked list.
The 'Top' Node is actually
the head of the linked list.
*/

template<class T>
Stack<T>::Stack() {
    length = 0;
    top_ = NULL;
}

template<class T>
Stack<T>::Stack(Stack<T> &other) {
    length = other.length;
    if (other.top_ == NULL) {
        top_ = new Node<T>();
    } else {
        top_ = new Node<T>(*(other.top_));
        copy(this->top_, other.top_);
    }
}

template<class T>
Stack<T> &Stack<T>::operator=(Stack<T> &other) {
    length = other.length;
    if (other.top_ == NULL) {
        top_ = new Node<T>();
    } else {
        top_ = new Node<T>(*(other.top_));
        copy(this->top_, other.top_);
    }
    return *this;
}

template<class T>
Stack<T>::~Stack() {
    remove(top_);
}

template<class T>
T *Stack<T>::top() {
    if (isEmpty())
        return nullptr;
    // Node<T> *temp = this->top_->get_next();
    // while (temp->get_next()) {
    //     temp = temp->get_next();
    // }
    // return temp->getValue();
    return top_->getValue();
}

template<class T>
void Stack<T>::push(T *t) {
    if (!t)
        return;
    if (!top_) {
        top_ = new Node<T>(t);
    } else {
        Node<T> *temp = new Node<T>(t);
        temp->set_next(top_);
        top_ = temp;
    }
    length++;
}

template<class T>
void Stack<T>::push(Node<T> *n) {
    if (!n)
        return;
    if (!top_) {
        top_ = new Node<T>(n->getValue());
    } else {
        n->set_next(top_);
        top_ = n;
    }
    length++;
}

template<class T>
Node<T> *Stack<T>::pop() {
    if (isEmpty())
        return nullptr;
    if (!top_->get_next()) {
        Node<T> *temp = new Node<T>(top_->getValue());
        top_ = nullptr;
        length--;
        return temp;
    } else {
        Node<T> *temp = top_;
        top_ = top_->get_next();
        length--;
        return temp;
    }
}

template<class T>
int Stack<T>::get_size() const {
    return length;
}

template<class T>
void Stack<T>::print() const {
    Node<T> *p = top_;
    while (p != NULL) {
        p->print();
        p = p->get_next();
    }
}

template<class T>
void Stack<T>::copy(Node<T> *this_, Node<T> *other_) {
    if (other_->get_next() == NULL) {
        return;
    }
    this_->set_next(new Node<T>(*(other_->get_next())));
    copy(this_->get_next(), other_->get_next());
}

template<class T>
void Stack<T>::remove(Node<T> *n) {
    if (n == NULL) {
        return;
    }
    if (n->get_next() == NULL) {
        delete n;
        return;
    }
    Node<T> *tmp = n->get_next();
    delete n;
    remove(tmp);
}

template<class T>
bool Stack<T>::isEmpty() const {
    return top_ == nullptr;
}

