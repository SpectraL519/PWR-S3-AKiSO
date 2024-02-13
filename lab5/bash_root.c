// Lab 5 - exercise 1

// compilation: sudo gcc -o br bash_root.c
// privileges: sudo chmod a+s br

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>





void openBash () {
    if (execl("/bin/bash", "bash", (char*) NULL) < 0) {
        perror("execl");
        exit(EXIT_FAILURE);
    }
}



int main(int argc, char *argv[])
{
    if (getuid() == 0) {
        printf("User is already root! Opening bash...\n");
        openBash();
    } 
	else {
        printf("Switching user to root...\n");

        if (setuid(0) < 0) {
            perror("setuid(0)");
            exit(EXIT_FAILURE);
        } 
        printf("Success! Opening bash...\n");
        openBash();
    }

    return 0;
}