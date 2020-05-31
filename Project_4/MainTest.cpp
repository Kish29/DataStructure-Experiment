//
// Created by asus on 6/1/2020.
//
#include "iostream"

int main() {
    uint8_t a = 252, b = 253, c = 254, d = 255;
    int ret = 0;
    ret += a;
    ret += b;
    ret += c;
    ret += d;
    std::cout << (ret / 4) << std::endl;
    return 0;
}
