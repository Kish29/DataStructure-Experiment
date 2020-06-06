#include "hashtable.h"
#include "string.h"

bool Node::operator!=(const char *str) {
    if (!str)
        return false;
    else
        return this->p.first != str;
}

bool Node::operator!=(const string &str) {
    return p.first != str;
}

bool Node::operator==(const char *str) {
    return p.first == str;
}

bool Node::operator==(const string &str) {
    return p.first == str;
}

bool Node::operator!=(Node &n) {
    return p.first != n.p.first;
}

bool Node::operator==(Node &n) {
    return p.first == n.p.first;
}

char Node::operator[](const int index) {
    if (p.first.empty() || (unsigned) index >= p.first.size() || index < 0)
        return '#';
    return p.first[index];
}

int Node::length() { //return length of the string
    if (p.first.empty())
        return 0;
    return p.first.length();
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
    // set hash table to 200000
    elem = new Node[MAX_SIZE];
    size = MAX_SIZE;
}

HashTable::~HashTable() {
    delete[] elem;
}

int HashTable::hash(Node &index) {
    // according to java's hash algorithm
    int hash = 0;
    for (char c : index.getString()) {
        hash = (hash * 256 + c + 128) % MAX_SIZE;
    }
    return hash % MAX_SIZE;
}

bool HashTable::search(Node &index, int &pos, int &times) {
    pos = this->hash(index);
    // collision times
    times = 0;
    while (elem[pos] != index) {
        if (elem[pos] == "#")
            return false;
        times++;
        if (times >= MAX_SIZE)
            return false;
        pos++;
        pos = pos % MAX_SIZE;
    }
    return true;
}

int HashTable::insert(Node &index) {
    int pos, times;
    if (search(index, pos, times)) {
        elem[pos].second()++;
        return 2;
    } else
        elem[pos] = index;
    return 1;
}

int HashTable::insert(const char *str) {
    int pos, times;
    Node n(str);
    if (search(n, pos, times)) {
        elem[pos].second()++;
        return 2;
    } else
        elem[pos] = n;
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

const string &Node::getString() const {
    return p.first;
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

int HashTable::hash(const char *str) {
    if (!str)
        return -1;
    int hash = 0;
    int i = 0;
    while (str[i] != '\0') {
        hash = 31 * hash + str[i];
        i++;
    }
    return abs(hash) % MAX_SIZE;
}

int HashTable::hash(string &str) {
    if (str.empty())
        return -1;
    int hash = 0;
    for (char c : str)
        hash = hash * 31 + c;
    return abs(hash) % MAX_SIZE;
}

