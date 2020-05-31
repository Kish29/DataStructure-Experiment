//
// Created by asus on 5/29/2020.
//

#include "hashtable.h"
#include "dict.h"

int main() {
//    Node a("wocao");
//    Node b("wocao");
//    string ab = "wocao";
//    std::cout << boolalpha << (a == b) << std::endl;
//    std::cout << a[4] << std::endl;
//    std::cout << b[3] << std::endl;
    const char *str = "WO caSAFS AF DASDHFIOH FSAFAOS O ni ma";
    const char *new_str = "wo weq de fasdf  cao ni ma ma de wen   sdf";
    const char *str2 = " o o o o o o o  oo    o  oo o ooo  oo  oo  o  ";
    string s = Dict::convertToString(str);
    string s2 = Dict::convertToString(str2);
    std::cout << std::boolalpha << Dict::isAlpha(s) << '\n';
    std::cout << std::boolalpha << Dict::isAlpha(s2) << '\n';
    Dict::toLowerCase(s);
    std::cout << s << "\n";
    Dict d;
    d.insert(str);
    d.insert(new_str);
    d.insert(str2);
    d.print();
}

