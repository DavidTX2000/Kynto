#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CLR_RESET   "\033[0m"
#define CLR_NEON    "\033[38;5;198m" // Rosa Neon
#define CLR_GOLD    "\033[38;5;214m" // Ouro
#define CLR_CYAN    "\033[38;5;51m"  // Cyan Brilhante
#define CLR_WHITE   "\033[1;37m"

void print_final_dashboard() {
    FILE *f;
    printf("\n");
    // ARTE KYNTO COM ESCAPE CORRIGIDO
    printf(CLR_GOLD"  _  _ "CLR_NEON" _  _ "CLR_GOLD" _  _ "CLR_NEON" ___ "CLR_GOLD" ___ "CLR_NEON" ___ \n");
    printf(CLR_GOLD" | || |"CLR_NEON"\\\// "CLR_GOLD"| \\| |"CLR_NEON"|_ _| "CLR_GOLD"|   |"CLR_NEON"|   |\n");
    printf(CLR_GOLD" |   < "CLR_NEON" \\/  "CLR_GOLD"| |\\ |"CLR_NEON"  | |  "CLR_GOLD"| | |"CLR_NEON"| | |\n");
    printf(CLR_GOLD" |_||_|"CLR_NEON"  ||  "CLR_GOLD"|_|\\_|"CLR_NEON"  |_|  "CLR_GOLD"|___|"CLR_NEON"|___|"CLR_RESET"\n\n");

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char date_buf[64];
    strftime(date_buf, sizeof(date_buf), "%H:%M:%S | %d/%m/%y", t);

    printf(CLR_CYAN" ❯ COMMANDER :"CLR_WHITE" u0_a1010  "CLR_CYAN"❯ TIME :"CLR_WHITE" %s\n", date_buf);
    printf(CLR_CYAN" ❯ STATUS    :"CLR_WHITE" SYSTEM OPERATIONAL\n\n");

    printf(CLR_NEON" [ MONITORING CORE ]\n"CLR_RESET);
    
    // CPU Temp
    f = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (f) {
        int temp; fscanf(f, "%d", &temp); fclose(f);
        printf(CLR_GOLD"  ⚙ TEMP  :"CLR_WHITE" %.1f°C\n", temp / 1000.0);
    }

    // RAM
    printf(CLR_GOLD"  ♨ RAM   :"CLR_WHITE" "); fflush(stdout);
    system("free -m | grep Mem | awk '{print $3\"MB / \"$2\"MB\"}'");

    // BATTERY
    printf(CLR_GOLD"  ⚡ BATT  :"CLR_WHITE" "); fflush(stdout);
    system("termux-battery-status | grep -E 'percentage|status' | xargs | awk '{print $2\"% (\"$4\")\"}' | tr -d ',\"'");

    printf("\n"CLR_NEON" ------------------------------------------\n"CLR_RESET);
}
