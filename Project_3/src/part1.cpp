#include "hashtable.h"

int main() {
    HashTable *h = new HashTable();
    for (int i = 0; i < 10; i++) {
        h->insert("test");
        /*if (i != 0 && a != 2) {
            break;
        }*/
    }

    delete h;
    return 0;
}
