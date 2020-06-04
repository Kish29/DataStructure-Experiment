//
// Created by asus on 6/4/2020.
//

#include "heap.h"

#include "iostream"

int main() {
    int test[8];
    for (int i = 0; i < 7; ++i)
        test[i] = i * 2;
    test[7] = 1;
    int cur = 7;
    int cur_parent = (cur - 1) / 2;
    int temp = test[cur];
    while (cur > 0) {
        if (test[cur_parent] > temp) {
            test[cur] = test[cur_parent];
            cur = cur_parent;
            cur_parent = (cur_parent - 1) / 2;
        } else
            break;
    }
    test[cur] = temp;
    for (int &i : test) {
        std::cout << i << "-";
    }
    return 0;
}
//#include <iostream>
//
//using namespace std;
//
//const int DefaultSize = 50;
//
//template<typename T>
//class MinHeap {
//public:
//    //构造函数：建立空堆
//    MinHeap(int sz = DefaultSize) {
//        maxHeapSize = (DefaultSize < sz) ? sz : DefaultSize;
//        heap = new T[maxHeapSize];
//        currentSize = 0;
//    }
//
//    //构造函数通过一个数组建立堆
//    MinHeap(T arr[], int n) {
//        maxHeapSize = (DefaultSize < n) ? n : DefaultSize;
//        heap = new T[maxHeapSize];
//        for (int i = 0; i < n; i++) {
//            heap[i] = arr[i];
//        }
//        currentSize = n;
//        int currentPos = (currentSize - 2) / 2;    //找最初调整位置:最后分支结点
//        while (currentPos >= 0)    //自底向上逐步扩大形成堆
//        {
//            siftDowm(currentPos, currentSize - 1);    //局部自上向下下滑调整
//            currentPos--;    //再向前换一个分支结点
//        }
//    }
//
//    //将x插入到最小堆中
//    bool Insert(const T &x) {
//        if (currentSize == maxHeapSize) {
//            cout << "Heap Full!" << endl;
//            return false;
//        }
//        heap[currentSize] = x;    //插入
//        siftUp(currentSize);    //向上调整
//        currentSize++;    //堆计数+1
//        return true;
//    }
//
//    bool RemoveMin(T &x) {
//        if (!currentSize) {
//            cout << "Heap Empty!" << endl;
//            return false;
//        }
//        x = heap[0];    //返回最小元素
//        heap[0] = heap[currentSize - 1];    //最后元素填补到根结点
//        currentSize--;
//        siftDowm(0, currentSize - 1);    //自上向下调整为堆
//        return true;
//    }
//
//    void output() {
//        for (int i = 0; i < currentSize; i++) {
//            cout << heap[i] << " ";
//        }
//        cout << endl;
//    }
//
//protected:
//
//    //最小堆的下滑调整算法
//    void siftDowm(int start, int end)    //从start到end下滑调整成为最小堆
//    {
//        int cur = start;
//        int min_child = 2 * cur + 1;    //先记max_child是cur的左子女位置
//        T temp = heap[cur];
//        while (min_child <= end) {
//            if (min_child < end && heap[min_child] > heap[min_child + 1])    //找到左右孩子中最小的一个
//                min_child++;
//
//            if (temp <= heap[min_child])
//                break;
//            else {
//                heap[cur] = heap[min_child];
//                cur = min_child;
//                min_child = 2 * min_child + 1;
//            }
//        }
//        heap[cur] = temp;
//    }
//
//    //最小堆的上滑调整算法
//    void siftUp(int start)    //从start到0上滑调整成为最小堆
//    {
//        int cur = start;
//        int parent = (cur - 1) / 2;
//        T temp = heap[cur];
//        while (cur > 0) {
//            if (heap[parent] <= temp)
//                break;
//            else {
//                heap[cur] = heap[parent];
//                cur = parent;
//                parent = (parent - 1) / 2;
//            }
//        }
//        heap[cur] = temp;    //回放temp中暂存的元素
//    }
//
//private:    //存放最小堆中元素的数组
//    T *heap;
//    int currentSize;    //最小堆中当前元素个数
//    int maxHeapSize;    //最小堆最多允许元素个数
//};
//
////------------------------主函数-------------------------
//int main(int argc, char *argv[]) {
//    MinHeap<int> h;
//    h.Insert(8);
//    h.Insert(5);
//    h.Insert(7);
//    h.Insert(9);
//    h.Insert(6);
//    h.Insert(12);
//    h.Insert(15);
//    h.Insert(16);
//    h.Insert(7);
//    h.output();
//
//    int out;
//    cout << static_cast<int> (h.RemoveMin(out)) << endl;
//    h.output();
//
//    int arr[10] = {15, 19, 13, 12, 18, 14, 10, 17, 20, 11};
//    MinHeap<int> h1(arr, 10);
//    h1.output();
//}
