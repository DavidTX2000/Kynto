#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void debug_bench(char *args) {
    clock_t start = clock();
    printf("\033[1;33m[DEBUG]: Benchmarking task...\033[0m\n");
    
    // Simula execução de comando
    system(args); 

    clock_t end = clock();
    double cpu_timeUsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\033[1;32m[TIME]: Execution took %f seconds.\033[0m\n", cpu_timeUsed);
}

void debug_sys(char *args) {
    printf("\033[1;35m[SYS_RESOURCE]:\033[0m\n");
    system("uptime && free -m");
}
