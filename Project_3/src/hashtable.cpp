#include "hashtable.h"

bool Node::operator!=(const char *str) {
    if (!str)
        return true;
    else {
        int pStrLen = p.first.size();
        for (int i = 0; i < pStrLen; ++i) {
            if (str[i] != p.first[i])
                break;
            if (i == pStrLen - 1 && str[i + 1] == '\0')
                return false;
            else if (str[i + 1] == '\0' && i != pStrLen - 1)
                break;
            else if (str[i + 1] != '\0' && i == pStrLen - 1)
                break;
        }
    }
    return true;
}

bool Node::operator!=(const string &str) {
    if (str.empty())
        return true;
    return p.first != str;
}

bool Node::operator==(const char *str) {
    return !(p.first != str);
}

bool Node::operator==(const string &str) {
    return !(p.first != str);
}

bool Node::operator!=(Node &n) {
    if (n.p.first.empty())
        return true;
    return p.first != n.p.first;
}

bool Node::operator==(Node &n) {
    return !(*this != n);
}

char Node::operator[](const int index) {
    if (p.first.empty() || index >= p.first.size() || index < 0)
        return '\0';
    return p.first[index];
}

int Node::length() { //return length of the string
    return p.first.size();
}

int &Node::second() {
    return p.second;
}

const pair<string, int> *Node::get_pair() const {
    //const pair<string, int> *pairPtr = &this->p;
    auto *pairPtr = &this->p;
    return pairPtr;
}

Node::~Node() {
}

HashTable::HashTable() {
    //TODO
}

HashTable::~HashTable() {
    //TODO
}

int HashTable::hash(Node &index) {
    //TODO
    return 0;
}

bool HashTable::search(Node &index, int &pos, int &times) {
    //TODO
    return false;
}

int HashTable::insert(Node &index) {
    //TODO
    return 1;
}

int HashTable::insert(const char *str) {
    //TODO
    return 1;
}

/*
 ==========================================================================
 =================Please Do Not Modify Functions Below=====================
 ========================请不要修改下列函数实现================================
 ==========================================================================
 */

Node::Node() {
    p = make_pair(string("#"), 1);
}

Node::Node(const char *str) {
    if (!str)
        p = make_pair(string("#"), 1);
    else
        p = make_pair(string(str), 1);
}

Node::Node(const string &str) {
    p = make_pair(str, 1);
}

int HashTable::get_size() const {
    return size;
}

const pair<string, int> *HashTable::get_pair(int index) {
    if (index < size && index >= 0) {
        return (elem[index].get_pair());
    }
    return NULL;
}

const pair<string, int> *HashTable::get_pair(int index) const {
    if (index < size && index >= 0) {
        return (elem[index].get_pair());
    }
    return NULL;
}
