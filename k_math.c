#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void k_calculate(float v1, const char* op, float v2, float* res) {
    if (strcmp(op, "+") == 0) *res = v1 + v2;
    else if (strcmp(op, "-") == 0) *res = v1 - v2;
    else if (strcmp(op, "*") == 0) *res = v1 * v2;
    else if (strcmp(op, "/") == 0) {
        if (v2 != 0) *res = v1 / v2;
        else printf("Error: Division by zero\n");
    }
}

