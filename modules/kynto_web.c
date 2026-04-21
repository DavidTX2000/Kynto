#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void web_get(char* url) {
    printf("[Kynto WEB] Fetching data from: %s\n", url);
    char cmd[256];
    sprintf(cmd, "curl -s -L %s | head -n 5", url);
    system(cmd);
}

void web_download(char* url) {
    printf("[Kynto WEB] Downloading resource...\n");
    char cmd[256];
    sprintf(cmd, "curl -O %s", url);
    system(cmd);
}
