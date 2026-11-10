#include <stdio.h>
#include "calculator.h"

int main()
{
    printf("Addition: %.2lf\n", basic_calc(ADD, 10, 5));

    printf("Subtraction: %.2lf\n", basic_calc(SUBTRACT, 10, 5));

    printf("Multiplication: %.2lf\n", basic_calc(MULTIPLY, 10, 5));

    printf("Division: %.2lf\n", basic_calc(DIVIDE, 10, 5));

    printf("Power: %.2lf\n", basic_calc(POWER, 2, 3));

    printf("Modulus: %.2lf\n", basic_calc(MODULUS, 10, 3));

    printf("Division by zero: %lf\n", basic_calc(DIVIDE, 10, 0));

    return 0;
}