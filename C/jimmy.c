#include <stdio.h>
int main() {

    int age ;

    //Let's ask for the user's age
    printf("What is your age? ");
    scanf("%d", &age);

    //Of course a student must be more than 4 yrs of age.
    if(age >= 4 && age < 18){
        printf("Student Discount\n");
    } 
    //Again student must be less than 100 yrs to be realistic.
    else if(age >= 18 && age <= 100){
        printf("No Student's Discount\n");
    }
    //Of course if user inputs anything irrelevant, output should be invalid 
    else {
        printf("Invalid..!!\n");
    }

    return 0;
}
