#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void math_calc(char *args) {
    double n1, n2;
    char op;
    if (sscanf(args, "{%lf %c %lf}", &n1, &op, &n2) == 3) {
        double res = 0;
        if (op == '+') res = n1 + n2;
        else if (op == '-') res = n1 - n2;
        else if (op == '*') res = n1 * n2;
        else if (op == '/') res = (n2 != 0) ? n1 / n2 : 0;
        printf("\033[1;34m[MATH]: Result = %.2f\033[0m\n", res);
    }
}

void math_sqrt(char *args) {
    double val = atof(args);
    printf("[MATH]: Sqrt = %.4f\n", sqrt(val));
}
