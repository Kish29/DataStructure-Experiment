#include "hashtable.h"

int main() {
    HashTable * h = new HashTable();
    for (int i = 0; i < 10; i ++) {
        h->insert("test");
        /*if (i != 0 && a != 2) {
            break;
        }*/
    }
    for (int i = 0; i < h->get_size(); i++) {
        if (h->get_pair(i)->first.compare("#")) {
            std::cout << "[" << h->get_pair(i)->first << "]:[" << h->get_pair(i)->second << "]\n";
        }
    }
    delete h;
    return 0;
}
