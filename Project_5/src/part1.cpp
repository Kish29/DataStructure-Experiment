#include "heap.h"
#include "iostream"

int main() {
    std::cout << (-1 / 2) << std::endl;
    Heap *h = new Heap();
    for (int i = 0; i < 1999; i++) {
        std::string str("asd");
        Player_info p(str, i, 200);
        h->insert(p);
    }
    Player_info p2("low", 999, 100);
    for (int k = 0; k < 2000; ++k) {
        std::string str("kkk");
        Player_info p(str, k, 300);
        h->insert(p);
    }
    for (int l = 0; l < 1000; ++l) {
        std::string str("kkk");
        Player_info p(str, l, 999);
        h->insert(p);
    }
    for (int l = 0; l < 500; ++l) {
        std::string str("kkk");
        Player_info p(str, l, 888);
        h->insert(p);
    }
    h->insert(p2);
    h->print();
    auto *p = h->sort();
    for (int j = 0; j < 2000; ++j) {
        p[j].print();
    }
    delete h;
    return 0;
}
