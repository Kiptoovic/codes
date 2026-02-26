#include <stdio.h>
int main()
{
    int a = 5;
    int b = 10;
    int temp;

    printf("a = %d, b = %d\n", a, b);

    // Swapping values using a temporary variable
    temp = a;
    a = b;
    b = temp;

    printf("a = %d, b = %d\n", a, b);

    return 0;
}