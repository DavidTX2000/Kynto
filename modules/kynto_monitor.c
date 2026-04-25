#include <stdio.h>
#include <unistd.h>

void monitor_live() {
    printf("[MONITOR] Starting live monitoring...\n");

    for (int i = 0; i < 5; i++) {
        printf("[MONITOR] Tick %d\n", i+1);
        sleep(1);
    }
}
