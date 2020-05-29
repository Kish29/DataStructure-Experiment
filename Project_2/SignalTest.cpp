//
// Created by asus on 5/28/2020.
//

#include "csignal"
#include "string"
#include "iostream"

static bool run = true;

void INT_Handle() {
    std::cout << "Oops! Yout just put Ctr + C! Stop it!";
    exit(0);
    run = false;
}

int main() {
    signal(SIGINT, reinterpret_cast<__p_sig_fn_t>(INT_Handle));
    while (run) {
        int run_time = INT32_MAX;
        while (run_time--);
        std::cout << "it is running!" << "\n";
    }
    return 0;
}