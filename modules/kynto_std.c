#include "kynto.h"
#include <ctype.h>
#include <math.h>

void math_add(char *a, KyntoAPI *api) { 
    int v1, v2; char res[32]; 
    if(sscanf(a, "%d,%d", &v1, &v2) == 2) { sprintf(res, "%d", v1+v2); api->set_var("RESULT", res); } 
}

void str_upper(char *a, KyntoAPI *api) {
    char *val = api->get_var(a);
    char buf[256]; strcpy(buf, val);
    for(int i=0; buf[i]; i++) buf[i] = toupper(buf[i]);
    api->set_var(a, buf);
}

void sys_exec(char *a, KyntoAPI *api) { system(a); }

void file_write(char *a, KyntoAPI *api) {
    char path[128], content[512];
    if(sscanf(a, "%[^,],%[^\n]", path, content) == 2) {
        FILE *f = fopen(path, "w");
        if(f) { fprintf(f, "%s", content); fclose(f); }
    }
}

void net_ping(char *a, KyntoAPI *api) {
    char cmd[128]; sprintf(cmd, "ping -c 1 %s", a);
    system(cmd);
}
