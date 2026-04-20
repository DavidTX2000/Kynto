#include <stdio.h>
#include <stdlib.h>

void hw_battery(char *args) {
    FILE *f = fopen("/sys/class/power_supply/battery/capacity", "r");
    if (f) {
        int cap;
        fscanf(f, "%d", &cap);
        fclose(f);
        printf("\033[1;32m[HW_INFO]: Battery at %d%%\033[0m\n", cap);
    } else {
        printf("[HW_INFO]: Battery status unavailable.\n");
    }
}

void hw_thermal(char *args) {
    FILE *f = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (f) {
        int temp;
        fscanf(f, "%d", &temp);
        fclose(f);
        printf("\033[1;33m[HW_INFO]: CPU Temp: %.2f°C\033[0m\n", temp / 1000.0);
    }
}

void hw_vibrate(char *args) {
    int ms = atoi(args);
    printf("[SYSTEM]: Vibrating for %dms...\n", ms);
    // Para Termux real: system("termux-vibrate -d ...");
}
