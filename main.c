#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_line(char* line) {
    if (strncmp(line, "print", 5) == 0) {
        char *msg = strchr(line, '{') + 1;
        char *end = strchr(msg, '}');
        if(end) *end = '\0';
        printf("%s\n", msg);
    } 
    else if (strncmp(line, "ui", 2) == 0) {
        printf("[Kynto UI] Executing interface command...\n");
    } 
    else if (strncmp(line, "web", 3) == 0) {
        printf("[Kynto WEB] Connection established.\n");
    }
    else if (strncmp(line, "kernel", 6) == 0) {
        printf("[Kynto KERNEL] System check OK.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    FILE *file = fopen(argv[1], "r");
    char lines[100][256];
    int total_lines = 0;
    int loop_count = 1;

    printf("\033[1;36m--- KYNTO ENGINE: ULTIMATE EDITION ---\033[0m\n");

    while (fgets(lines[total_lines], 256, file)) {
        if (strncmp(lines[total_lines], "loop", 4) == 0) {
            char *start = strchr(lines[total_lines], '{') + 1;
            char *end = strchr(start, '}');
            if(end) *end = '\0';
            loop_count = atoi(start);
            continue;
        }
        if (lines[total_lines][0] != '#' && lines[total_lines][0] != '\n' && strncmp(lines[total_lines], "module", 6) != 0) {
            total_lines++;
        }
    }
    fclose(file);

    for(int i = 1; i <= loop_count; i++) {
        if (loop_count > 1) printf("\n\033[1;33m[Loop %d/%d]\033[0m\n", i, loop_count);
        for(int j = 0; j < total_lines; j++) {
            execute_line(lines[j]);
        }
    }

    printf("\n\033[1;32m--- GLOBAL EXECUTION SUCCESS ---\033[0m\n");
    return 0;
}
