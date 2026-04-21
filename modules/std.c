#include "kynto.h"
#include <ctype.h>

void str_upper(char *args, KyntoAPI *api) {
    char vn[64] = {0};
    if (sscanf(args, "{$%[^}]}", vn) == 1) {
        char *val = api->get_var(vn);
        char new_val[256];
        strcpy(new_val, val);
        for(int i = 0; new_val[i]; i++) new_val[i] = toupper(new_val[i]);
        api->set_var(vn, new_val);
    }
}

void math_add(char *args, KyntoAPI *api) {
    char vn[64] = {0}; int a, b;
    if (sscanf(args, "{$%[^=]=%d+%d}", vn, &a, &b) == 3) {
        char res[32];
        sprintf(res, "%d", a + b);
        api->set_var(vn, res);
    }
}

void sys_exec(char *args, KyntoAPI *api) {
    system(args);
}
