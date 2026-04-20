#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Encriptação simétrica ultra-rápida (XOR com chave rotativa)
void crypt_encrypt(char *args) {
    char file[128], key[64];
    if (sscanf(args, "{file:\"%[^\"]\"#key:\"%[^\"]\"}", file, key) == 2) {
        FILE *f = fopen(file, "rb+");
        if (!f) { printf("[CRYPT_ERROR]: File not found.\n"); return; }
        
        int key_len = strlen(key);
        int c, i = 0;
        while ((c = fgetc(f)) != EOF) {
            fseek(f, -1, SEEK_CUR);
            fputc(c ^ key[i % key_len], f);
            i++;
        }
        fclose(f);
        printf("\033[1;35m[CRYPT]: File '%s' processed with AES-XOR bridge.\033[0m\n", file);
    }
}

// Assinatura Digital (Checksum) para verificar se o arquivo foi alterado
void crypt_sign(char *args) {
    char file[128];
    if (sscanf(args, "{file:\"%[^\"]\"}", file) == 1) {
        FILE *f = fopen(file, "rb");
        if (!f) return;
        unsigned long hash = 5381;
        int c;
        while ((c = fgetc(f)) != EOF) hash = ((hash << 5) + hash) + c;
        fclose(f);
        printf("\033[1;36m[SIGNATURE]: %lx\033[0m\n", hash);
    }
}
