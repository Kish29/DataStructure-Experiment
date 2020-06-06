#include "hashtable.h"
#include "dict.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>


// 计蒜客非常煞笔，他认为像 shit40这种去掉数字也算作一个单词
bool is_alpha(char c) {
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
}

int read_from_file(FILE *input_file, Dict *d);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        exit(1);
    }
    FILE *input = fopen(argv[1], "r");
    if (input == nullptr) {
        perror("Fopen Failed ");
        exit(-1);
    }
    Dict d = Dict();
    read_from_file(input, &d);
    fclose(input);
    d.print();
    return 0;
}

int read_from_file(FILE *input_file, Dict *d) {
    if (input_file && d) {
        string str = "";
        char c;
        bool tag = false;
        while (((c = fgetc(input_file)) != EOF)) {
            if (is_alpha(c)) {
                str += c;
                tag = true;
            } else {
                if (tag) {
                    d->insert(str.c_str());
                    tag = false;
                    str = "";
                }
            }
        }
    }
    return 0;
}
