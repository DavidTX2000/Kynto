#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Definição de Cores ANSI (8-bit para degradê suave)
#define CLR_RESET   "\033[0m"
#define CLR_WHITE   "\033[1;37m"
#define CLR_NEON    "\033[38;5;118m" // Verde Neon vibrante
#define CLR_GOLD    "\033[38;5;220m" // Amarelo Ouro
#define CLR_ORANGE  "\033[38;5;208m" // Laranja

// Função para imprimir arte ASCII GIGANTE com degradê calculado
void print_giant_ascii() {
    // Título GIGANTE "KYNTO" (11 linhas de altura)
    char *ascii_art[] = {
        "██╗  ██╗██╗   ██╗██████╗ ████████╗██████╗ ",
        "██║ ██╔╝╚██╗ ██╔╝██╔══██╗╚══██╔══╝██╔══██╗",
        "█████╔╝  ╚████╔╝ ██████╔╝   ██║   ██║  ██║",
        "██╔═██╗   ╚██╔╝  ██╔══██╗   ██║   ██║  ██║",
        "██║  ██╗   ██║   ██║  ██║   ██║   ██████╔╝",
        "╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝   ╚═╝   ╚═════╝ ",
        "      ██████╗ ██████╗ ██████╗ ███████╗      ",
        "     ██╔════╝██╔══██╗██╔══██╗██╔════╝      ",
        "     ██║     ██║  ██║██████╔╝█████╗        ",
        "     ██║     ██║  ██║██╔══██╗██╔══╝        ",
        "     ╚██████╗╚██████╔╝██║  ██║███████╗      ",
        "      ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝      "
    };
    
    // Degradê vertical suave: Amarelo (0-3) -> Laranja (4-7) -> Verde (8-11)
    int art_size = sizeof(ascii_art) / sizeof(char *);
    for (int i = 0; i < art_size; i++) {
        if (i < 4) printf(CLR_GOLD);
        else if (i < 8) printf(CLR_ORANGE);
        else printf(CLR_NEON);
        printf("  %s\n", ascii_art[i]);
    }
    printf(CLR_RESET "\n");
}

void print_final_dashboard() {
    print_giant_ascii();

    // SEÇÃO DE SAUDAÇÃO E TEMPO (Superior à dele)
    time_t now; struct tm *t; time(&now); t = localtime(&now);
    char date_buf[64];
    strftime(date_buf, sizeof(date_buf), "%a %Y-%m-%d | %H:%M:%S %Z", t);
    
    char user[64]; FILE *fp = popen("whoami", "r"); fgets(user, sizeof(user), fp); pclose(fp);
    user[strcspn(user, "\n")] = 0; // Remove \n

    printf(CLR_NEON "  [ COMMANDER ]" CLR_RESET " %s@kynto_os\n", user);
    printf(CLR_NEON "  [ MISSION   ]" CLR_RESET " Operational Audit | %s\n", date_buf);
    printf("\n");

    printf(CLR_ORANGE "--------------------------------------------------------\n" CLR_RESET);
    
    // LAYOUT DE DUAS COLUNAS COM DADOS EXTREMOS (Igualando a densidade dele)
    // Coluna 1: Hardware & OS
    printf(CLR_GOLD "  [ HARDWARE ]" CLR_RESET "\n");
    printf("  ⚙ SoC       : " CLR_WHITE "Snapdragon 888 (SM8350)" CLR_RESET "\n");
    printf("  ⚙ Arch      : " CLR_WHITE); fflush(stdout); system("uname -m | tr -d '\n'"); printf("" CLR_RESET "\n");
    printf("  ⚙ Kernel    : " CLR_WHITE); fflush(stdout); system("uname -r | tr -d '\n'"); printf("" CLR_RESET "\n");
    printf("  ⚙ CPU Freq  : " CLR_WHITE); fflush(stdout); system("lscpu | grep 'CPU MHz' | awk '{print $3}' | tr -d '\n'"); printf("MHz" CLR_RESET "\n");
    printf("  ⚙ CPU Temp  : " CLR_WHITE); fflush(stdout); system("cat /sys/class/thermal/thermal_zone0/temp | awk '{print $1/1000}' | tr -d '\n'"); printf("°C" CLR_RESET "\n");
    printf("  ⚙ Memory    : " CLR_WHITE); fflush(stdout); system("free -h | grep Mem | awk '{print $3\"/\"$2}' | tr -d '\n'"); printf("" CLR_RESET "\n");
    printf("  ⚙ Swap      : " CLR_WHITE); fflush(stdout); system("free -h | grep Swap | awk '{print $3\"/\"$2}' | tr -d '\n'"); printf("" CLR_RESET "\n");
    printf("  ⚙ Disk (/)  : " CLR_WHITE); fflush(stdout); system("df -h / | grep / | awk '{print $3\"/\"$2}' | tr -d '\n'"); printf("" CLR_RESET "\n");
    printf("  ⚙ Uptime    : " CLR_WHITE); fflush(stdout); system("uptime -p | tr -d '\n'"); printf("" CLR_RESET "\n");
    printf("\n");

    // Coluna 2: Android & GPU (Informações que ele não tem)
    printf(CLR_GOLD "  [ ANDROID & GPU ]" CLR_RESET "\n");
    printf("  ⚙ Android V : " CLR_WHITE "12 (API 31)" CLR_RESET "\n");
    printf("  ⚙ GPU       : " CLR_WHITE "Adreno (Turnip)" CLR_RESET "\n");
    printf("  ⚙ GPU Freq  : " CLR_WHITE "315MHz" CLR_RESET "\n"); // Estático, mas mostra que você buscou
    printf("  ⚙ Vulkan V  : " CLR_WHITE "1.1.201" CLR_RESET "\n");
    printf("  ⚙ OpenGL    : " CLR_WHITE "Zink (via Vulkan)" CLR_RESET "\n");
    printf("  ⚙ SELinux   : " CLR_WHITE); fflush(stdout); system("getenforce | tr -d '\n'"); printf("" CLR_RESET "\n");
    printf("\n");

    // Coluna 3: System Status (Load e Bateria)
    printf(CLR_GOLD "  [ STATUS ]" CLR_RESET "\n");
    printf("  ⚖ CPU Load  : " CLR_WHITE); fflush(stdout); system("uptime | awk '{print $8 $9 $10}' | tr -d '\n'"); printf("" CLR_RESET "\n");
    printf("  ⚖ Processes : " CLR_WHITE); fflush(stdout); system("ps -A | wc -l | tr -d '\n'"); printf("" CLR_RESET "\n");
    printf("  ⚡ Battery  : " CLR_WHITE); fflush(stdout); system("termux-battery-status | grep -E 'percentage|status' | xargs | awk '{print $2\"% (\"$4\")\"}' | tr -d ',\"' | tr -d '\n'"); printf("" CLR_RESET "\n");
    printf("\n");
    
    printf(CLR_ORANGE "--------------------------------------------------------\n" CLR_RESET);
}
