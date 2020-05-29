#include "workflow.h"
#include "worker.h"
#include "vector.h"
#include <iostream>

Job::~Job() {
    //TODO
    delete worker;
    delete prev;
    delete next;
    worker = nullptr;
    prev = next = nullptr;   // set null
}

Workflow::Workflow() {
    //TODO
    head = tail = nullptr;
    size = 0;
}

Workflow::~Workflow() {
    //TODO
    Job *temp = head;
    Job *temp2;
    while (temp != nullptr) {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    head = tail = temp = temp2 = nullptr;
}

int Workflow::insert(Job *j) {
    //TODO
    if (j == nullptr)
        return 1;
    if (head == nullptr) {  // if head is null
        // 注意, 这里只能用calloc分配内存,不然job的id会+1
        head = (Job *) calloc(sizeof(Job), 1);
        tail = (Job *) calloc(sizeof(Job), 1);
        head = j;
        head->next = nullptr;
        tail->prev = head;
        tail->next = head->prev = nullptr;
        size++;
        return 0;
    }
    tail->prev->next = j;
    j->next = nullptr;
    j->prev = tail->prev;
    tail->prev = j;
    size++;
    return 0;
}

int Workflow::swap(int original_index, int target_index) {
    //TODO
    if (original_index < 0 || original_index >= size || target_index < 0 || target_index >= size)
        return 1;
    Job *origin = get(original_index);
    Job *target = get(target_index);
    Job *temp1 = origin->prev;
    Job *temp2 = origin->next;
    origin->next = target->next;
    origin->prev = target->prev;
    target->prev->next = target->next->prev = origin;
    temp1->next = temp2->prev = target;
    target->prev = temp1;
    target->next = temp2;
    return 0;
}

Job *Workflow::pop() {
    //TODO
    if (head == nullptr)
        return nullptr;
    Job *temp = head;
    head = head->next;
    size--;
    return temp;
}

int Workflow::process(vector *l, int index) {
    //TODO
    if (index < 0 || index >= size || l->get(0) == nullptr)
        return 1;
    Job *cur = get(index);
    if (cur) {
        Worker *newWorker = l->remove(0);
        if (!newWorker)
            return 1;
        if (cur->worker) {
            delete cur->worker;
            cur->worker = newWorker;
        } else
            cur->worker = newWorker;
        swap(0, index);
        return 0;
    }
    return 1;
}

/*预警：以下内容不许修改。*/
int Job::num_job = 0;   //Do not remove or modify this line.
//警告：你不可以改动这一行！
Job::Job() {               //警告：你不可以改动这个函数！
    id = num_job;
    num_job++;
    next = nullptr;
    prev = nullptr;
    worker = nullptr;
}

int Workflow::print() {     //警告：你不可以改动这个函数！
    Job *curr = head;
    int i = 0;
    if (curr == nullptr) {
        std::cout << "Empty Flow\n";
        return 0;
    }
    while (curr != nullptr) {
        std::cout << "[" << i << "]";
        curr->print();
        i++;
        curr = curr->next;
    }
    return 0;
}

Job *Workflow::get(int index) const {
    if (index < 0 || index >= size)
        return nullptr;
    Job *temp = head;
    for (int i = 0; i < index; ++i) {
        temp = temp->next;
    }
    return temp;
}

int Job::print() {
    std::cout << "job [" << this->id << "]\n";
    return 0;
}
