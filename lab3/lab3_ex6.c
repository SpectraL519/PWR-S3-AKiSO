#include <stdio.h>





void displayColorSet (char name[], int min, int max) {
    printf("\033[0;00m%s:\n", name);
    for (int c = min; c < max; c++) {
        printf("\033[38;5;%dm", c);
        printf("Hello World!\n");
    }
    printf("\033[0;00m\n");
}

int main()
{
    displayColorSet("Standard color set", 0, 16);
    displayColorSet("Distributed colors' set", 16, 232);
    displayColorSet("Grayscale color set", 232, 256);

    return 0;
}