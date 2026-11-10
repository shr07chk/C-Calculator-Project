#include "calculator.h"

double basic_calc(int op, double a, double b)
{
    double result;

    switch(op)
    {
        case ADD:
            result = a + b;
            break;

        case SUBTRACT:
            result = a - b;
            break;

        case MULTIPLY:
            result = a * b;
            break;

        case DIVIDE:
            if(b == 0)
                return NAN;

            result = a / b;
            break;

        case POWER:
            result = pow(a, b);
            break;

        case MODULUS:
            if(b == 0)
                return NAN;

            result = fmod(a, b);
            break;

        default:
            return NAN;
    }

    if(!isfinite(result))
        return NAN;

    return result;
}