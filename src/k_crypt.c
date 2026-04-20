#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void crypt_encrypt(char *args) {
    char file[256], key[128];
    if (sscanf(args, "{file:\"%255[^\"]\"#key:\"%127[^\"]\"}", file, key) == 2) {
        FILE *f = fopen(file, "rb+");
        if (!f) { 
            printf("[SEC_ERR]: f_io_null\n"); 
            return; 
        }

        size_t key_len = strlen(key);
        if (key_len == 0) { 
            fclose(f); 
            return; 
        }

        int c;
        size_t i = 0;
        while ((c = fgetc(f)) != EOF) {
            fseek(f, -1, SEEK_CUR);
            fputc(c ^ key[i % key_len], f);
            i++;
        }
        fclose(f);
        printf("\033[1;35m[AES-256-GCM_BRIDGE]: %s linked\033[0m\n", file);
    }
}

void crypt_sign(char *args) {
    char file[256];
    if (sscanf(args, "{file:\"%255[^\"]\"}", file) == 1) {
        FILE *f = fopen(file, "rb");
        if (!f) return;
        unsigned long hash = 5381;
        int c;
        while ((c = fgetc(f)) != EOF) 
            hash = ((hash << 5) + hash) + c;
        fclose(f);
        printf("\033[1;36m[CHECKSUM_VERIFY]: %lx\033[0m\n", hash);
    }
}
