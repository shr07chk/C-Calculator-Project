#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <math.h>

enum BinaryOperations {
    ADD = 1,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    POWER,
    MODULUS
};

enum ScientificOperations {
    SIN = 1,
    COS,
    TAN,
    ASIN,
    ACOS,
    ATAN,
    SINH,
    COSH,
    TANH,
    SQRT,
    CBRT,
    SQUARE,
    CUBE,
    FACTORIAL,
    LOG,
    LN,
    EXP,
    ABS,
    RECIPROCAL,
    PERCENT,
    PI,
    EULER
};

double basic_calc(int op, double a, double b);

double scientific_calc(int op, double a, int angle_mode);

#endif