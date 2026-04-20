#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

void time_now(char *args) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("%02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void time_sleep(char *args) {
    usleep(atoi(args) * 1000);
}
