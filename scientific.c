#include "calculator.h"

double scientific_calc(int op, double a, int angle_mode)
{
    double result;
    double angle;

    // Convert degrees to radians when required
    angle = (angle_mode == 0) ? a * acos(-1.0) / 180.0 : a;

    switch(op)
    {
        // Trigonometric functions

        case SIN:
            result = sin(angle);
            break;

        case COS:
            result = cos(angle);
            break;

        case TAN:
            if(fabs(cos(angle)) < 1e-12)
                return NAN;
            result = tan(angle);
            break;

        case ASIN:
            if(a < -1 || a > 1)
                return NAN;

            result = asin(a);

            if(angle_mode == 0)
                result = result * 180.0 / acos(-1.0);

            break;

        case ACOS:
            if(a < -1 || a > 1)
                return NAN;

            result = acos(a);

            if(angle_mode == 0)
                result = result * 180.0 / acos(-1.0);

            break;

        case ATAN:
            result = atan(a);

            if(angle_mode == 0)
                result = result * 180.0 / acos(-1.0);

            break;


        // Hyperbolic functions

        case SINH:
            result = sinh(a);
            break;

        case COSH:
            result = cosh(a);
            break;

        case TANH:
            result = tanh(a);
            break;


        // Roots and powers

        case SQRT:
            if(a < 0)
                return NAN;

            result = sqrt(a);
            break;

        case CBRT:
            result = cbrt(a);
            break;

        case SQUARE:
            result = a * a;
            break;

        case CUBE:
            result = a * a * a;
            break;


        // Factorial

        case FACTORIAL:
            if(a < 0 || a > 170 || floor(a) != a)
                return NAN;

            result = 1;

            for(int i = 1; i <= (int)a; i++)
            {
                result = result * i;
            }

            break;


        // Logarithmic and exponential functions

        case LOG:
            if(a <= 0)
                return NAN;

            result = log10(a);
            break;

        case LN:
            if(a <= 0)
                return NAN;

            result = log(a);
            break;

        case EXP:
            result = exp(a);
            break;


        // Other operations

        case ABS:
            result = fabs(a);
            break;

        case RECIPROCAL:
            if(a == 0)
                return NAN;

            result = 1.0 / a;
            break;

        case PERCENT:
            result = a / 100.0;
            break;

        case PI:
            result = acos(-1.0);
            break;

        case EULER:
            result = exp(1.0);
            break;

        default:
            return NAN;
    }

    if(!isfinite(result))
        return NAN;

    return result;
}
