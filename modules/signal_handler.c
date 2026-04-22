#include <stdio.h>
#include <signal.h>

void kynto_shutdown(int sig) {
    printf("\n[KYNTO-CORE] Signal %d: Graceful Shutdown Initiated.\033[0m\n", sig);
    fflush(stdout);
}

void setup_signal_handler() {
    signal(SIGINT, kynto_shutdown);
    printf("[KYNTO-ADV] Signal Monitoring: ENABLED\n");
    fflush(stdout);
}
