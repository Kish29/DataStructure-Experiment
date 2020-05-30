#include <iostream>
#include "string"
#include "vector.h"
#include "workflow.h"

int main() {
    Workflow *w = new Workflow();
    std::cout << w->insert(nullptr);
    w->print();
    for (int i = 0; i < 10; ++i) {
        w->insert(new Job());
    }
    Job *j = new Job();
    j->worker = new Worker();
    w->insert(j);
    w->print();
    w->get(10)->print();
    vector *v = new vector(10);
    for (int k = 0; k < 10; ++k) {
        v->insert(new Worker());
    }
    std::cout << w->process(v, 8) << std::endl;
    std::cout << w->process(v, 8) << std::endl;
    v->print();
    w->swap(3, 2);
    w->print();
    w->swap(3, 2);
    w->print();
    w->pop();
    w->print();
}