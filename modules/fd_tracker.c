#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

void track_file_descriptors() {
    struct dirent *entry;
    DIR *dp = opendir("/proc/self/fd");
    printf("\n[KYNTO-ADV] Active File Descriptors:\n");
    while (dp && (entry = readdir(dp))) {
        char path[512], link[512];
        if (entry->d_name[0] == '.') continue;
        snprintf(path, sizeof(path), "/proc/self/fd/%s", entry->d_name);
        ssize_t len = readlink(path, link, sizeof(link)-1);
        if (len != -1) {
            link[len] = '\0';
            printf("FD %s -> %s\n", entry->d_name, link);
        }
    }
    if (dp) closedir(dp);
    fflush(stdout);
}
