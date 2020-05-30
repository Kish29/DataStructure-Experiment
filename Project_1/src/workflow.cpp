#include "workflow.h"
#include "worker.h"
#include "vector.h"
#include "cmath"
#include <iostream>

Job::~Job() {
    if (worker)
        delete worker;
    //注意，千万不要对prev和next进行操作，不然会段错误
    // if (prev)
    //     delete prev;
    // if (next)
    //     delete next;
    //worker = nullptr;
    //prev = next = nullptr;   // set null
}

Workflow::Workflow() {
    //TODO
    head = tail = nullptr;
    size = 0;
}

Workflow::~Workflow() {
    Job *temp = head;
    while (temp) {
        head = head->next;
        delete(temp);
        temp = head;
    }
}

int Workflow::insert(Job *j) {
    //TODO
    if (j == nullptr)
        return 1;
    if (head == nullptr) {  // if head is null
        // 娉ㄦ剰, 杩欓噷鍙兘鐢╟alloc鍒嗛厤鍐呭瓨,涓嶇劧job鐨刬d浼�+1
        //head = (Job *) calloc(sizeof(Job), 1);
        //tail = (Job *) calloc(sizeof(Job), 1);
        head = tail = j;
        tail->prev = tail->next = head->prev = nullptr;
        size++;
        return 0;
    }
    tail->next = j;
    j->next = nullptr;
    j->prev = tail;
    tail = j;
    size++;
    return 0;
}

int Workflow::swap(int original_index, int target_index) {
    if (original_index < 0 || original_index >= size || target_index < 0 || target_index >= size)
        return 1;
    if (original_index == target_index)
        return 0;
    int orgi = std::min(original_index, target_index);
    int trgi = std::max(original_index, target_index);
    Job *origin = get(orgi);
    Job *target = get(trgi);
    if (origin && target) {
        Job *origin_prev = origin->prev;
        Job *target_next = target->next;
        if (origin_prev && target_next) {
            //if origin neighbor target
            if (trgi - orgi == 1) {
                origin->next = target_next;
                target->prev = origin_prev;
                target_next->prev = origin;
                target->next = origin;
                origin_prev->next = target;
                origin->prev = target;
                return 0;
            }
            Job *origin_next = origin->next;
            origin->next = target->next;
            origin->prev = target->prev;
            target->prev->next = target_next->prev = origin;
            origin_prev->next = origin_next->prev = target;
            target->prev = origin_prev;
            target->next = origin_next;
        } else if (origin_prev) {
            Job *origin_next = origin->next;
            origin->next = nullptr;
            origin->prev = target->prev;
            target->prev->next = origin;
            origin_prev->next = origin_next->prev = target;
            target->prev = origin_prev;
            target->next = origin_next;
            tail = origin;
        } else {
            Job *origin_next = origin->next;
            origin->next = target_next;
            origin->prev = target->prev;
            target->prev->next = target->next->prev = origin;
            origin_next->prev = target;
            target->next = origin_next;
            target->prev = nullptr;
            head = target;
        }
        return 0;
    }
    return 1;
}

Job *Workflow::pop() {
    //TODO
    if (head == nullptr)
        return nullptr;
    Job *temp = head;
    head->next->prev = nullptr;
    head = head->next;
    size--;
    temp->next = nullptr;
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
        return 0;
    }
    return 1;
}

/*棰勮锛氫互涓嬪唴瀹逛笉璁镐慨鏀广��*/
int Job::num_job = 0;   //Do not remove or modify this line.
//璀﹀憡锛氫綘涓嶅彲浠ユ敼鍔ㄨ繖涓�琛岋紒
Job::Job() {               //璀﹀憡锛氫綘涓嶅彲浠ユ敼鍔ㄨ繖涓嚱鏁帮紒
    id = num_job;
    num_job++;
    next = nullptr;
    prev = nullptr;
    worker = nullptr;
}

int Workflow::print() {     //璀﹀憡锛氫綘涓嶅彲浠ユ敼鍔ㄨ繖涓嚱鏁帮紒
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
    if (this == nullptr)
        return 1;
    std::cout << "job [" << this->id << "]\n";
    return 0;
}

// int Job::getId() const {
//     return id;
// }

// Job *Workflow::getJobById(int id) const {
//     if (id < 0 || id >= size)
//         return nullptr;
//     Job *temp = head;
//     for (int i = 0; i < size; ++i) {
//         if (temp->getId() == id)
//             return temp;
//         temp = temp->next;
//     }
//     return temp;
// }
