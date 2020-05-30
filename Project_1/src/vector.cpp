#include "vector.h"
#include "worker.h"
#include <string>
#include <iostream>
#include <cstdlib>
/*提示：这里的 data 是一个指向指针的指针。
 在操作指针前请三思！
 如果你不知道的话：malloc 的功能和 new 类似，
 这里使用 malloc 是为了方便空间不足时进行扩展。
 不用担心，扩展函数已为你写好。
 －－前一位实习生
 */
/*
 TODO 实现 insert 函数：在数组内插入新的 worker。
 如果数组满了调用 expand()，返回 1
 其他情况执行插入，返回 0
 */
int vector::insert(Worker *new_worker) {
    // if array if full, invoke expand()
    if (length == size) {
        this->expand();
        // pay attention to length - 1
        length++;
        //this->data[length - 1] = (Worker *) calloc(sizeof(Worker), 1);
        this->data[length - 1] = new_worker;
        return 1;
    }
    if (!new_worker)
        return 0;
    // pay attention to length - 1
    length++;   // length should increase preferentially
    //this->data[length - 1] = (Worker *) calloc(sizeof(Worker), 1);
    this->data[length - 1] = new_worker;
    return 0;
}

//TODO get 函数的功能不言自明。你可以自行处理非法输入，但是绝不能容许内存错误。
Worker *vector::get(int index) const {
    if (index >= size || index < 0)
        return nullptr;
    return this->data[index];
}

//TODO
Worker *vector::remove(int index) {
    if (index >= length || index < 0)
        return nullptr;
    Worker *tmp = this->data[index];
    for (int i = index; i < length - 1; ++i) {
        this->data[i] = this->data[i + 1];
    }
    length--;
    return tmp;
}

/*以下内容不建议修改。*/

vector::~vector() {
    for (int i = 0; i < length; i++) {
        delete *(data + i);
    }
    free(data);
}

vector::vector(int input_size) {
    size = input_size;
    length = 0;
    data = (Worker **) calloc(sizeof(Worker *), input_size);
}

void vector::expand() {
    size = size * 2;
    data = (Worker **) realloc(data, sizeof(Worker *) * size);
}

void vector::print() {
    std::cout << "Current vector:\n";
    for (int i = 0; i < length; i++) {
        std::cout << "[" << i << "] ";
        (*(data + i))->print();
    }
    std::cout << "Current vector Ends\n";
}
