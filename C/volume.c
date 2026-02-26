#include <stdio.h>
#include <math.h>
int main()
{   
    //allows user to input decimals and whole numbers  
    float radius, height;
    float volume;
    
    //prompts user to enter the radius
    printf("What is the radius ? \n");
    scanf("%f", &radius);
    
    //prompts the user to enter the height
    printf("What is the height ? \n");
    scanf("%f", &height);

    //calculates the volime using information provided by user
    volume = (3.142) * radius * radius * height;
    printf("Volume is %.2f\n", volume);

    return 0;
}