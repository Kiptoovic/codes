#include <stdio.h>
int main()
{
    int first;

    printf("Enter any number:  ");
    scanf("%d", &first);

    //Determine if number is positive, negative or zero
    if (first > 0) {
        printf("The number is positive.\n", first);
    }

    else if (first < 0) {
        printf("The number is negative.\n", first);
    }

    else {
        printf("The number is zero.\n");
    }

    //Determine if number is even or odd
    if (first % 2 == 0) {
        printf("The number is even.\n", first);
    }
    else {
        printf("The number is odd.\n", first);
    }

     // If number is positive, calculate and print its factorial using a loop
    if (first > 0) {
        // use unsigned long long for larger factorials; warn about overflow for big inputs
        if (first > 20) {
            printf("Just try a number lower than 20 nigga,, as long as the code is running well.\n");
            unsigned long long fact = 1;
        } else {
            unsigned long long fact = 1;
            for (int i = 1; i <= first; ++i) 
            fact *= i;
            printf("Factorial of %d is %llu\n", first, fact);
        }
    }
    else if (first == 0) {
        // Factorial of zero is 1
        printf("Factorial of 0 is 1\n");
    }
    else {
        // Negative number factorial not defined
        printf("Factorial is not defined for negative numbers\n");
    }

    return 0;
}