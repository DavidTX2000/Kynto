#include <stdio.h>
void ui_window(char *args) {
    printf("\n\033[1;37m[WINDOW]: %s\033[0m\n", args);
}
void ui_button(char *args) {
    printf("[BUTTON]: %s\n", args);
}
