#include <stdio.h>
#include <dirent.h>

void profile_threads() {
    DIR *dir = opendir("/proc/self/task");
    struct dirent *entry;
    printf("\n[KYNTO-CPU] Thread Execution Profile:\n");
    while (dir && (entry = readdir(dir))) {
        if (entry->d_name[0] == '.') continue;
        printf("Thread Active: ID %s\n", entry->d_name);
    }
    if (dir) closedir(dir);
    fflush(stdout);
}
