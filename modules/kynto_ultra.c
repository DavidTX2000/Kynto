#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void ultra_stress() {
    printf("\033[1;31m[!] WARNING: STARTING CPU STRESS TEST (5s)...\033[0m\n");
    // Simula uma carga pesada enquanto o Kynto monitora
    system("timeout 5s sha256sum /dev/zero &"); 
}

void ultra_sysinfo() {
    printf("\033[1;36m[ KYNTO ELITE DASHBOARD ]\033[0m\n");
    printf("OS Kernel: "); fflush(stdout); system("uname -rs");
    printf("Uptime   : "); fflush(stdout); system("uptime -p");
    printf("Memory   : "); fflush(stdout); system("free -m | grep Mem | awk '{print $3\"MB / \"$2\"MB\"}'");
}
