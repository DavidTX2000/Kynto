#include "kynto.h"
void math_add(char *args, KyntoAPI *api) {
    int a, b;
    char var_dest[64];
    if (sscanf(args, "%d,%d %s", &a, &b, var_dest) == 3) {
        char res[32];
        sprintf(res, "%d", a + b);
        api->set_var(var_dest, res);
    }
}
