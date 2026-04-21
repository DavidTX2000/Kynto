#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute(const char *arg) {
    FILE *fp;
    char buffer[16];

    // Log para saber se a função foi chamada
    // printf("Debug: Chamou execute com %s\n", arg); 

    if (strstr(arg, "battery") != NULL) {
        fp = fopen("/sys/class/power_supply/battery/capacity", "r");
        if (fp) {
            fgets(buffer, sizeof(buffer), fp);
            printf("[Hardware] Battery: %s", buffer);
            fclose(fp);
        }
    } else if (strstr(arg, "temp") != NULL) {
        fp = fopen("/sys/class/power_supply/battery/temp", "r");
        if (fp) {
            fgets(buffer, sizeof(buffer), fp);
            printf("[Hardware] Temp: %.1f°C\n", atof(buffer) / 10.0);
            fclose(fp);
        }
    }
    fflush(stdout); // Força o texto a aparecer na tela NA HORA
}
