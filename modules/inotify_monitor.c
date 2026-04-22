#include <stdio.h>
#include <sys/inotify.h>
#include <unistd.h>

void start_inotify_module() {
    int fd = inotify_init();
    if (fd < 0) return;
    inotify_add_watch(fd, ".", IN_MODIFY | IN_CREATE | IN_DELETE);
    printf("[KYNTO-ADV] File System Monitor: ACTIVE\n");
    fflush(stdout);
    close(fd);
}
