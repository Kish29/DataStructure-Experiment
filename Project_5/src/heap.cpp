#include "heap.h"

#define LEFT true
#define RIGHT false

#define LIST_SIZE 2000

Heap::~Heap() {
    delete[] arr;
}

Heap::Heap(Heap &other) {
    this->num = 0;
    this->arr = new Player_info[LIST_SIZE]();
    for (int i = 0; i < other.num; ++i) {
        auto *temp = new Player_info(other.arr[i]);
        this->insert(*temp);
    }
}

Heap &Heap::operator=(Heap &other) {
    this->num = 0;
    this->arr = new Player_info[LIST_SIZE]();
    for (int i = 0; i < other.num; ++i) {
        auto *temp = new Player_info(other.arr[i]);
        this->insert(*temp);
    }
    return *this;
}

void Heap::heapify_up() {
    int cur = num;
    // 父节点下标
    int cur_parent = (cur - 1) / 2;
    // 获得子节点
    Player_info temp = arr[cur];
    while (cur > 0) {
        if (arr[cur_parent] > temp) { // 如果比父节点的值小，互换值
            arr[cur] = arr[cur_parent];
            // 向上取下标，向上堆化
            cur = cur_parent;
            cur_parent = (cur_parent - 1) / 2;
        } else
            break;
    }
    // 更新最后的元素
    arr[cur] = temp;
}

void Heap::heapify_down() {
    int cur = 0;
    int cur_min_child = 2 * cur + 1;
    Player_info temp = arr[cur];
    while (cur_min_child <= num) {
        // 先找到左右孩子的最小值
        if (cur_min_child < num && arr[cur_min_child] > arr[cur_min_child + 1])
            cur_min_child++;    // 如果右孩子存在，且比左孩子小
        if (temp <= arr[cur_min_child])
            break;      // 小于则不需要向下滑
        else {
            arr[cur] = arr[cur_min_child];
            cur = cur_min_child;
            cur_min_child = 2 * cur_min_child + 1;
        }
    }
    arr[cur] = temp;    // 注意这里不能是 cur_min_child，因为循环里
    // cur_min_child已经2倍加1了
}

int Heap::get_child(bool direction, int index) const {
    if (direction) {    // 查找左孩子
        return (2 * index + 1) >= num ? -1 : (2 * index + 1);
    } else
        return (2 * index + 2) >= num ? -1 : (2 * index + 2);
}

int Heap::get_father(int index) const {
    return (index - 1) / 2;
}

int Heap::insert(Player_info &p) {
    if (num == LIST_SIZE) { // 堆已满，删除最小的元素，但是要注意是否比最小的元素大
        if (p <= arr[0])
            return -1;
        remove_min_elem();
        arr[num] = p;
        heapify_up();
        num++;
        return 1;
    } else {
        arr[num] = p;
        heapify_up();
        num++;
        return 1;
    }
}

Player_info *Heap::remove_min_elem() {
    if (!num)   //堆是空的
        return nullptr;
    auto *min = new Player_info(arr[0]);   //返回最小的元素
    arr[0] = arr[num - 1];  //末尾元素移至根部
    num--;
    heapify_down(); //下滑堆化
    return min;
}

Player_info *Heap::sort() {
    if (!num)
        return nullptr;
    auto *sorted_array = new Player_info[num];
    // 用一个副本来排序，不删除原来的堆元素
    auto *temp = new Heap(*this);
    for (int j = num - 1; j >= 0; j--) {
        sorted_array[j] = *temp->remove_min_elem();
    }
    return sorted_array;
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
    return score == other.score;
}

bool Player_info::operator!=(Player_info &other) const {
    return score != other.score;
}

bool Player_info::operator<(Player_info &other) const {
    return score < other.score;
}

bool Player_info::operator<=(Player_info &other) const {
    return score <= other.score;
}

bool Player_info::operator>(Player_info &other) const {
    return score > other.score;
}

bool Player_info::operator>=(Player_info &other) const {
    return score >= other.score;
}

void Player_info::print() {
    printf("[%ld]%s - %d\n", uid, username.c_str(), score);
}
