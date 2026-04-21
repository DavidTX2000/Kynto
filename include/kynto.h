#ifndef KYNTO_H
#define KYNTO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#define MAX_VARS 100
typedef struct { char name[64]; char value[256]; } Variable;
typedef struct {
    void (*set_var)(const char*, const char*);
    char* (*get_var)(const char*);
} KyntoAPI;
void k_set_var(const char *name, const char *val);
char* k_get_var(const char *name);
#endif
