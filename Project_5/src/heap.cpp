#include "heap.h"
#define LEFT true
#define RIGHT false

#define LIST_SIZE 2000

Heap::~Heap() {
    //TODO
}

Heap::Heap(Heap &other) {
    //TODO
}

Heap &Heap::operator=(Heap &other) {
    //TODO
}

void Heap::heapify_up() {
    //TODO
}

void Heap::heapify_down() {
    //TODO
}

int Heap::get_child(bool direction, int index) {
    //TODO
    return -1;
}

int Heap::get_father(int index) {
    //TODO
    return -1;
}

int Heap::insert(Player_info &p) {
    //TODO
    return -1;
}

Player_info *Heap::sort() {
    //TODO
    return NULL;
}

/*
 =========================================================
 ================ WARNING ===== 警告 ======================
 ===Please Do Not Modify Any of the Following Functions===
 ===================请不要修改以下函数=======================
 =========================================================
 */

int Heap::get_num() const {
    return num;
}

Heap::Heap() {
    num = 0;
    arr = new Player_info[LIST_SIZE];
}

void Heap::print() {
    for (int i = 0; i < num; i++) {
        arr[i].print();
    }
    printf("\nSize of the heap is %d\n", num);
}

Player_info::Player_info() {
    username = std::string("#");
    uid = 0;
    score = 0;
}

Player_info::~Player_info() {

}

Player_info::Player_info(Player_info &other) {
    username = std::string((other.username));
    score = other.score;
    uid = other.uid;
}

Player_info::Player_info(std::string in_name, long in_uid, int in_score) {
    username = std::string(in_name);
    score = in_score;
    uid = in_uid;
}

Player_info &Player_info::operator=(Player_info &other) {
    username = std::string((other.username));
    score = other.score;
    uid = other.uid;
    return *this;
}

int Player_info::get_score() const {
    return score;
}

const std::string &Player_info::get_name() const {
    return username;
}

bool Player_info::operator==(Player_info &other) const {
    if(score == other.score) {
        return true;
    }
    return false;
}

bool Player_info::operator!=(Player_info &other) const {
    if(score == other.score) {
        return false;
    }
    return true;
}

bool Player_info::operator<(Player_info &other) const {
    if(score < other.score) {
        return true;
    }
    return false;
}

bool Player_info::operator<=(Player_info &other) const {
    if(score <= other.score) {
        return true;
    }
    return false;
}

bool Player_info::operator>(Player_info &other) const {
    if(score > other.score) {
        return true;
    }
    return false;
}

bool Player_info::operator>=(Player_info &other) const {
    if(score >= other.score) {
        return true;
    }
    return false;
}

void Player_info::print() {
    printf("[%ld]%s - %d\n", uid, username.c_str(), score);
    return;
}
