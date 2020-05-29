#include "stack.h"
#include "queue.h"
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <string>

Stack<std::string> *history;

Stack<std::string> *tmp;

int resume();

int undo();


int resume() {
    if (!history)
        history = new Stack<std::string>();
    if (!tmp) {
        tmp = new Stack<std::string>();
        return -1;
    } else if (tmp->get_size() == 0)
        return -1;
    else {
        history->push(tmp->pop());
        history->print();
        return 0;
    }
}

int undo() {
    if (!tmp)
        tmp = new Stack<std::string>();
    if (!history) {
        history = new Stack<std::string>();
        return -1;
    } else if (history->get_size() == 0)
        return -1;
    else {
        tmp->push(history->pop());
        return 0;
    }
}