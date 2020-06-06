#include "dict.h"

int Dict::insert(const char *str) {
    if (!str)
        return 1;
    string cstr = str;
    if (!isAlpha(cstr))
        return 1;
    else {
        toLowerCase(cstr);
        Node n(cstr);
        h.insert(n);
        size++;
        return 0;
    }
}

/*
 ==========================================================================
 =================Please Do Not Modify Functions Below=====================
 ========================请不要修改下列函数实现================================
 ==========================================================================
 */

Dict::Dict() {
    size = 0;
}

void Dict::print() const {
    for (int i = 0; i < h.get_size(); i++) {
        if (h.get_pair(i)->first.compare("#")) {
            std::cout << "[" << h.get_pair(i)->first << "]:[" << h.get_pair(i)->second << "]\n";
        }
    }
    std::cout << "\nTotal: " << size << " words.\n";
}

bool Dict::isAlpha(string &word) {
    // filter word fill of spaces
    if (word.empty())
        return false;
    else {
        for (char c : word) {
            if (48 <= c && c <= 57)
                return false;
        }
    }
    return true;
}

void Dict::toLowerCase(string &word) {
    if (word.empty())
        return;
    for (char &c : word) {
        c |= convertCode;
    }
}
