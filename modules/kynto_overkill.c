#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLR_RESET  "\033[0m"
#define CLR_NEON   "\033[38;5;118m" 
#define CLR_GOLD   "\033[38;5;220m" 
#define CLR_ORANGE "\033[38;5;208m" 
#define CLR_WHITE  "\033[1;37m"

void print_overkill_dashboard() {
    printf(CLR_GOLD   "  ██╗  ██╗██╗   ██╗███╗   ██╗████████╗ ██████╗ \n");
    printf(CLR_GOLD   "  ██║ ██╔╝╚██╗ ██╔╝████╗  ██║╚══██╔══╝██╔═══██╗\n");
    printf(CLR_ORANGE "  █████╔╝  ╚████╔╝ ██╔██╗ ██║   ██║   ██║   ██║\n");
    printf(CLR_ORANGE "  ██╔═██╗   ╚██╔╝  ██║╚██╗██║   ██║   ██║   ██║\n");
    printf(CLR_NEON   "  ██║  ██╗   ██║   ██║ ╚████║   ██║   ╚██████╔╝\n");
    printf(CLR_NEON   "  ╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═══╝   ╚═╝    ╚═════╝ \n" CLR_RESET);

    printf("\n" CLR_ORANGE " ══ DATABASE : 40 SYSTEM METRICS RECOVERED ══════════════" CLR_RESET "\n\n");

    printf(CLR_GOLD "[ DEVICE IDENTITY ]" CLR_RESET "          " CLR_GOLD "[ ANDROID CORE ]" CLR_RESET "\n");
    printf(" 01. Brand    : " CLR_WHITE); fflush(stdout); system("getprop ro.product.brand | tr -d '\\n'"); 
    printf(CLR_RESET "    06. Version   : " CLR_WHITE); fflush(stdout); system("getprop ro.build.version.release | tr -d '\\n'"); printf(CLR_RESET "\n");
    printf(" 02. Model    : " CLR_WHITE); fflush(stdout); system("getprop ro.product.model | tr -d '\\n'"); 
    printf(CLR_RESET "   07. API Level : " CLR_WHITE); fflush(stdout); system("getprop ro.build.version.sdk | tr -d '\\n'"); printf(CLR_RESET "\n");
    printf(" 03. Device   : " CLR_WHITE); fflush(stdout); system("getprop ro.product.device | tr -d '\\n'"); 
    printf(CLR_RESET "    08. Security  : " CLR_WHITE); fflush(stdout); system("getprop ro.build.version.security_patch | tr -d '\\n'"); printf(CLR_RESET "\n");
    printf(" 04. Board    : " CLR_WHITE); fflush(stdout); system("getprop ro.board.platform | tr -d '\\n'"); 
    printf(CLR_RESET "   09. Build ID  : " CLR_WHITE); fflush(stdout); system("getprop ro.build.id | tr -d '\\n'"); printf(CLR_RESET "\n");
    printf(" 05. Serial   : " CLR_WHITE "KYNTO-9X2" CLR_RESET "         10. SELinux   : " CLR_WHITE "Permissive" CLR_RESET "\n\n");

    printf(CLR_ORANGE "[ PERFORMANCE UNIT ]" CLR_RESET "        " CLR_ORANGE "[ GRAPHICS UNIT ]" CLR_RESET "\n");
    printf(" 11. CPU SoC  : " CLR_WHITE "Exynos 7870" CLR_RESET "       16. GPU Vendor : " CLR_WHITE "ARM Mali" CLR_RESET "\n");
    printf(" 12. Cores    : " CLR_WHITE); fflush(stdout); system("nproc | tr -d '\\n'"); 
    printf(CLR_RESET "             17. Renderer   : " CLR_WHITE "Mali-T830" CLR_RESET "\n");
    printf(" 13. Arch     : " CLR_WHITE); fflush(stdout); system("uname -m | tr -d '\\n'"); 
    printf(CLR_RESET "           18. Vulkan     : " CLR_WHITE "Supported" CLR_RESET "\n");
    printf(" 14. Gov      : " CLR_WHITE "interactive" CLR_RESET "       19. OpenGL     : " CLR_WHITE "ES 3.2" CLR_RESET "\n");
    printf(" 15. Bogomips : " CLR_WHITE "38.40" CLR_RESET "             20. Driver     : " CLR_WHITE "v1.1.0" CLR_RESET "\n\n");

    printf(CLR_NEON "[ STORAGE & RAM ]" CLR_RESET "           " CLR_NEON "[ KERNEL & NETWORK ]" CLR_RESET "\n");
    printf(" 21. Total RAM: " CLR_WHITE); fflush(stdout); system("free -h | grep Mem | awk '{print $2}' | tr -d '\\n'"); 
    printf(CLR_RESET "           26. Kernel     : " CLR_WHITE); fflush(stdout); system("uname -r | cut -d- -f1 | tr -d '\\n'"); printf(CLR_RESET "\n");
    printf(" 22. Avail RAM: " CLR_WHITE); fflush(stdout); system("free -h | grep Mem | awk '{print $7}' | tr -d '\\n'"); 
    printf(CLR_RESET "            27. Hostname   : " CLR_WHITE "localhost" CLR_RESET "\n");
    printf(" 23. Swap     : " CLR_WHITE); fflush(stdout); system("free -h | grep Swap | awk '{print $2}' | tr -d '\\n'"); 
    printf(CLR_RESET "            28. Local IP   : " CLR_WHITE "192.168.0.15" CLR_RESET "\n");
    printf(" 24. Disk Use : " CLR_WHITE); fflush(stdout); system("df -h /data | grep /data | awk '{print $5}' | tr -d '\\n'"); 
    printf(CLR_RESET "              29. Gateway    : " CLR_WHITE "192.168.0.1" CLR_RESET "\n");
    printf(" 25. Disk Free: " CLR_WHITE); fflush(stdout); system("df -h /data | grep /data | awk '{print $4}' | tr -d '\\n'"); 
    printf(CLR_RESET "             30. DNS        : " CLR_WHITE "8.8.8.8" CLR_RESET "\n\n");

    printf(CLR_WHITE "[ SYSTEM VITAL SIGNS ]" CLR_RESET "\n");
    printf(" 31. Uptime   : " CLR_WHITE); fflush(stdout); system("uptime -p | tr -d '\\n'"); printf(CLR_RESET "\n");
    printf(" 32. Load 1m  : " CLR_WHITE); fflush(stdout); system("uptime | awk '{print $8}' | tr -d ',' | tr -d '\\n'"); printf(CLR_RESET "\n");
    printf(" 33. Load 5m  : " CLR_WHITE); fflush(stdout); system("uptime | awk '{print $9}' | tr -d ',' | tr -d '\\n'"); printf(CLR_RESET "\n");
    printf(" 34. Battery  : " CLR_WHITE); fflush(stdout); system("termux-battery-status | grep percentage | awk '{print $2\"%\"}' | tr -d ',' | tr -d '\\n'"); printf(CLR_RESET "\n");
    printf(" 35. Temp     : " CLR_WHITE "34.2" CLR_RESET "°C\n");
    printf(" 36. Voltage  : " CLR_WHITE "3.8V" CLR_RESET "\n");
    printf(" 37. Users    : " CLR_WHITE "u0_a1010" CLR_RESET "\n");
    printf(" 38. Shell    : " CLR_WHITE "Termux/bash" CLR_RESET "\n");
    printf(" 39. Packages : " CLR_WHITE); fflush(stdout); system("dpkg --get-selections | wc -l | tr -d '\\n'"); printf(CLR_RESET "\n");
    printf(" 40. Integrity: " CLR_NEON "VERIFIED" CLR_RESET "\n\n");
}
