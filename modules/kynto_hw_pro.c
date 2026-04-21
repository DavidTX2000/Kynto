#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hw_dashboard() {
    printf("\n\033[1;35m[ KYNTO HARDWARE MONITOR ]\033[0m\n");
    
    // Temperatura com ícone e cor
    FILE *f = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (f) {
        int temp;
        fscanf(f, "%d", &temp);
        fclose(f);
        printf("\033[1;32m[+]\033[0m CPU Temp : \033[1;37m%.1f°C\033[0m\n", temp / 1000.0);
    }

    // Bateria formatada
    printf("\033[1;32m[+]\033[0m Battery  : \033[1;37m");
    fflush(stdout); // Força a saída do texto antes do comando do sistema
    system("termux-battery-status | grep percentage | awk '{print $2}' | tr -d ',' | tr -d '\n'");
    printf("%%\033[0m\n");
    
    // Load Average formatado
    printf("\033[1;32m[+]\033[0m CPU Load : \033[1;37m");
    fflush(stdout);
    system("uptime | awk '{print $8 $9 $10}' | tr -d '\n'");
    printf("\033[0m\n\n");
}
