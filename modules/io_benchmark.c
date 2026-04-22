#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

void run_io_benchmark() {
    char data[1024];
    int fd = open("test.tmp", O_WRONLY | O_CREAT, 0644);
    if(fd < 0) return;
    for(int i=0; i<1000; i++) write(fd, data, 1024);
    close(fd);
    unlink("test.tmp");
    printf("\n[KYNTO-BENCH] I/O Write Test: COMPLETE\n");
    fflush(stdout);
}
