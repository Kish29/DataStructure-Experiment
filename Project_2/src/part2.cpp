#include <iostream>
#include "stack.h"
#include "queue.h"
#include <cstdlib>
#include "stack"
#include "queue"
#include "extra.cpp"

int main() {
    auto *s = new std::stack<int>();
    auto *q1 = new std::queue<int>();
    s->push(3);
    q1->push(3);
    std::cout << Compare_stack_queue(s, q1) << '\n';
    Queue<int> *q = new Queue<int>();
    q->push(new int(1));
    q->push(new int(2));
    q->push(new int(3));
    q->push(new int(4));
    delete q->pop();
    q->push(new int(0xdeadbeef));
    q->print();
    delete q;
    return 0;
}
