#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crypt_hash(char* text) {
    printf("[Kynto CRYPT] Generating SHA-256 for: %s\n", text);
    char cmd[256];
    sprintf(cmd, "echo -n '%s' | sha256sum | awk '{print \"Hash: \" $1}'", text);
    system(cmd);
}

void crypt_gen_key() {
    printf("[Kynto CRYPT] Generating 2048-bit RSA Private Key...\n");
    system("openssl genrsa 2048 2>/dev/null | head -n 5");
    printf("[...] Key generated in memory.\n");
}
