// Lab5 - exercise 2.3

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define N_SIG 1000





void signalHandler (int signal) {
    printf("Delivered signal: SIGUSR1\n");
}



int main() {
    signal(SIGUSR1, signalHandler);
    pid_t pid = fork();

    if (pid == 0) {
        while(1);
    }
    else {
        int status;
        int successCount = 0;

        for (int i = 1; i <= N_SIG; i++) {
            kill(pid, SIGUSR1);
        }
        waitpid(pid, &status, 0);
    }

    return 0;
}
