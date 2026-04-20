#ifndef KYNTO_H
#define KYNTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

// Definições de Limites de Segurança
#define MAX_VAR_NAME 64
#define MAX_VAR_VAL 1024
#define MAX_PATH 256

// Estrutura principal da Tabela de Símbolos
typedef struct {
    char name[MAX_VAR_NAME];
    char value[MAX_VAR_VAL];
} Symbol;

// Protótipos das funções do Kernel
void k_execute_command(char *line);
void k_load_module(const char *mod_name);
void k_set_var(const char *name, const char *val);
char* k_get_var(const char *name);

#endif
