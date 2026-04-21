#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random_seed(char *args) {
    srand(time(NULL));
}

void random_randint(char *args) {
    int min, max;
    if (sscanf(args, "%d,%d", &min, &max) == 2) {
        printf("%d\n", (rand() % (max - min + 1)) + min);
    }
}
