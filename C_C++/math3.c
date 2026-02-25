#include <stdio.h>
#include <math.h>

int main() {
    double number = 25.0;
    double result = sqrt(number);  // This requires -lm flag
    printf("Square root of %.2f is %.2f\n", number, result);
    return 0;
}