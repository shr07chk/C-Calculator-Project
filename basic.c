#include "calculator.h"

double basic_calc(int op, double a, double b)
{
    switch(op)
    {
        case ADD:
            return a + b;

        case SUBTRACT:
            return a - b;

        case MULTIPLY:
            return a * b;

        case DIVIDE:
            if(b == 0)
                return NAN;
            return a / b;

        case POWER:
            return pow(a, b);

        case MODULUS:
            if(b == 0)
                return NAN;
            return fmod(a, b);

        default:
            return NAN;
    }
}