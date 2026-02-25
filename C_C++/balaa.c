#include <stdio.h>
#include <math.h>

int main() {

    int length, width, height;
//Ask user for length dimension
    printf("What is the length? ");
    scanf("%d", &length);

//Ask user for width dimension
    printf("What is the width? ");
    scanf("%d", &width);

//Ask user for height dimension
    printf("What is the height? ");
    scanf("%d", &height);
    
//Calculates volume
    int volume = length * width * height;
    printf("The volume is %d\n", volume);
    
    return 0;
}