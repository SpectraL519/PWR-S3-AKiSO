// Lab5 - exercise 2.1

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#define N_SIG 64 // possible kill signals can be checked with `kill -l` command





void signalHandler(int signal) {
    printf("Recieved signal: %d\n", signal);
}



int main() {
    for (int i = 1; i <= N_SIG; i++) {
        if (signal(i, signalHandler) == SIG_ERR) {
            fprintf(stderr, "Signal %d cannot be handled!\n", i);
        }
    }

    return 0;
}
