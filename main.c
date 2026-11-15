#include <stdio.h>
#include <math.h>
#include "calculator.h"

int main()
{
    int choice, op;
    int angle_mode = 0; // 0 = Degrees, 1 = Radians

    double a, b, result;

    while(1)
    {
        printf("\n========== SCIENTIFIC CALCULATOR ==========\n");
        printf("1. Basic Calculator\n");
        printf("2. Scientific Calculator\n");
        printf("3. Change Angle Mode (Current: %s)\n",
               angle_mode == 0 ? "DEG" : "RAD");
        printf("4. Exit\n");

        printf("Enter your choice: ");

        if(scanf("%d", &choice) != 1)
            return 1;

        switch(choice)
        {
            case 1:

                printf("\n------ BASIC OPERATIONS ------\n");
                printf("1. Addition\n");
                printf("2. Subtraction\n");
                printf("3. Multiplication\n");
                printf("4. Division\n");
                printf("5. Power\n");
                printf("6. Modulus\n");

                printf("Select operation: ");
                if(scanf("%d", &op) != 1)
                    return 1;

                if(op < 1 || op > 6)
                {
                    printf("Invalid operation!\n");
                    break;
                }

                printf("Enter first number: ");
                if(scanf("%lf", &a) != 1)
                    return 1;

                printf("Enter second number: ");
                if(scanf("%lf", &b) != 1)
                    return 1;

                result = basic_calc(op, a, b);

                if(isnan(result))
                    printf("Error: Invalid operation!\n");
                else
                    printf("Result = %.10g\n", result);

                break;


            case 2:

                printf("\n------ SCIENTIFIC OPERATIONS ------\n");

                printf("1. SIN\n");
                printf("2. COS\n");
                printf("3. TAN\n");
                printf("4. ASIN\n");
                printf("5. ACOS\n");
                printf("6. ATAN\n");
                printf("7. SINH\n");
                printf("8. COSH\n");
                printf("9. TANH\n");
                printf("10. SQRT\n");
                printf("11. CBRT\n");
                printf("12. SQUARE\n");
                printf("13. CUBE\n");
                printf("14. FACTORIAL\n");
                printf("15. LOG\n");
                printf("16. LN\n");
                printf("17. EXP\n");
                printf("18. ABS\n");
                printf("19. RECIPROCAL\n");
                printf("20. PERCENT\n");
                printf("21. PI\n");
                printf("22. EULER\n");

                printf("Select operation: ");
                if(scanf("%d", &op) != 1)
                    return 1;

                if(op < 1 || op > 22)
                {
                    printf("Invalid operation!\n");
                    break;
                }

                if(op != PI && op != EULER)
                {
                    printf("Enter number: ");
                    if(scanf("%lf", &a) != 1)
                        return 1;
                }
                else
                {
                    a = 0;
                }

                result = scientific_calc(op, a, angle_mode);

                if(isnan(result))
                    printf("Error: Invalid operation!\n");
                else
                    printf("Result = %.10g\n", result);

                break;


            case 3:

                angle_mode = !angle_mode;

                printf("Angle mode changed to %s\n",
                       angle_mode == 0 ? "DEG" : "RAD");

                break;


            case 4:

                printf("\nThank you for using our calculator!\n");
                return 0;


            default:

                printf("Invalid choice! Try again.\n");
        }
    }
}