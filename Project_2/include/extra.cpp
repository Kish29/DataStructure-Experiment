#include <stack>
#include <queue>

int Compare_stack_queue(std::stack<int> *s, std::queue<int> *q);

int Compare_stack_queue(std::stack<int> *s, std::queue<int> *q) {
    if (!s || !q)
        return 0;
    if (q->size() != s->size()) return 0;
    auto *temp = new std::stack<int>();
    while (!q->empty()) {
        temp->push(q->front());
        q->pop();
    }
    while (!s->empty() && !temp->empty()) {
        if (s->top() != temp->top()) {
            delete temp;
            return 0;
        }
        s->pop();
        temp->pop();
    }
    delete temp;
    return 1;
}
