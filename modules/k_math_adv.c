#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void math_pow(char *args) {
    double base, exp;
    if (sscanf(args, "%lf,%lf", &base, &exp) == 2) printf("%.4f\n", pow(base, exp));
}

void math_sin(char *args) {
    printf("%.4f\n", sin(atof(args)));
}

void math_pi(char *args) {
    printf("3.1415926535\n");
}
