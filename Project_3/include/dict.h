#ifndef DICT_
#define DICT_

#include <iostream>
#include <string>
#include <utility>
#include "hashtable.h"

class Dict {
private:
    HashTable h;
    int size;
    static const int convertCode = 0b00100000;
public:
    Dict();

    int insert(const char *str);

    void print() const;

    // this function must filter illegal words
    static bool isAlpha(string &word);

    static void toLowerCase(string &word);
};

#endif
