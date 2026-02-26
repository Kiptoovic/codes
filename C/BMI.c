#include <stdio.h>
#include <math.h>
int main ()
{
    float weight, height;
    float BMI;

    // i)prompts user to enter the weight
    printf("What is the weight(kg)? ");
    scanf("%f", &weight);

    //prompts the user to enter the height    
    printf("What is the height(m)? ");
    scanf("%f", &height);

    // ii)calculates the Body Mass Index using information provided by the user
    BMI = weight / (height * height);
    printf("The Body Mass Index is %.2f\n", BMI);

    // iii)use of if...else conditions
    if (BMI <= 18.4){
        printf("Underweight! \n");
    } else if (BMI >= 18.5 && BMI <= 24.9){
        printf("Normal weight \n");
    }else if (BMI >= 25.0 && BMI <=29.9) {
        printf("Overweight! \n");
    } else if (BMI >= 30.0 && BMI <= 40.0) {
        printf("Obesity!!! \n");
    } else {
        printf("Check your details and please try again. \n");
    }


    return 0;
}