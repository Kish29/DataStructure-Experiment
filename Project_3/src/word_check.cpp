#include "hashtable.h"
#include "dict.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

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
    // get file size
    int size = 10000;
    char *str = (char *) malloc(sizeof(char) * size);
    while (fgets(str, size, input_file) != nullptr) {
        if (ferror(input_file)) {
            //free(str);
            return -1;
        }
        d->insert(str);
    }
    return 0;
}
