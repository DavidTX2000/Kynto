#include <stdio.h>
#include <string.h>

void db_set(char *args) {
    char key[64], val[256];
    if (sscanf(args, "{key:\"%[^\"]\"#val:\"%[^\"]\"}", key, val) == 2) {
        FILE *f = fopen("kynto.db", "a");
        fprintf(f, "%s=%s\n", key, val);
        fclose(f);
        printf("\033[1;32m[DB]: Key '%s' stored.\033[0m\n", key);
    }
}

void db_get(char *args) {
    char key[64], line[320];
    sscanf(args, "{key:\"%[^\"]\"}", key);
    FILE *f = fopen("kynto.db", "r");
    if (!f) return;
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, key, strlen(key)) == 0) {
            printf("\033[1;36m[DB_RESULT]: %s\033[0m", line);
        }
    }
    fclose(f);
}
