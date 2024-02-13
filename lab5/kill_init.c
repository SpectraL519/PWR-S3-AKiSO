// Lab5 - exercise 2.2

#include <stdio.h>
#include <signal.h>
#include <string.h>

#define N_SIG 64 // possible kill signals can be checked with `kill -l` command





int main() {
    for (int i = 1; i <= N_SIG; i++) {
        if (kill(1, i) == -1) {
            fprintf(stderr, "Signal %d cannot be sent to INIT!\n", i);
        }
        else {
            printf("Sent signal %d to INIT\n", i);
        }
    }

    return 0;
}
