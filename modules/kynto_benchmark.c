#include <stdio.h>
#include <time.h>

void benchmark_run() {
    clock_t start = clock();

    for (volatile int i = 0; i < 100000000; i++);

    clock_t end = clock();
    double t = (double)(end - start) / CLOCKS_PER_SEC;

    printf("[BENCHMARK] Execution time: %.2f seconds\n", t);
}
