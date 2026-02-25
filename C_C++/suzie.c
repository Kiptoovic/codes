#include <stdio.h>
int main()
{   
    int mark ;

    printf("What is the mark of the student? ");
    scanf("%d", &mark);

    if (mark>=70 && mark<=100)
    {
        printf("Excellent and outstanding perfomance.\n");
        printf("It's a grade A.\n");
    }

    else if (mark>=60 && mark<=69)
    {
        printf("Quite impressive lakini hujafika bado.\n");
        printf("It's a grade B.\n");
    }

    else if (mark>=50 && mark<=59)
    {
        printf("Not so bad, keep going.\n");
        printf("It's a grade C.\n");
    }

    else if(mark>=40 && mark<=49)
    {
        printf("Put in some more effort, you can do it.\n");
        printf("It's a grade D.\n");
    }

    else if(mark>=0 && mark<=39)
    {
        printf("Wear your socks and pull them up.\n");
        printf("It's a grade E.\n");
    }

    else
    {
        //printf("\n");
        printf("You entered an invalid value nigga.\n");
    }

    return 0;

}


