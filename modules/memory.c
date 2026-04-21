#include "kynto.h"

void memory_set(char *args, KyntoAPI *api) {
    char *v_start = strchr(args, '$');
    char *v_end = strchr(args, '=');
    char *q1 = strchr(args, '\"');
    char *q2 = strrchr(args, '\"');
    
    if (v_start && v_end && q1 && q2 && q2 > q1) {
        char vn[64] = {0};
        char vv[256] = {0};
        memcpy(vn, v_start + 1, v_end - v_start - 1);
        memcpy(vv, q1 + 1, q2 - q1 - 1);
        api->set_var(vn, vv);
    }
}

void memory_get(char *args, KyntoAPI *api) {
    char vn[64] = {0};
    if (sscanf(args, "%s", vn) == 1) {
        char *res = api->get_var(vn);
        if (res) printf("%s", res);
    }
}
