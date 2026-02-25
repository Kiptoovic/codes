#include <stdio.h>
int main()
{
    int mark;
    int graded;
    
    printf("What is the mark ?");
    scanf("%d", &mark);

    if(mark<0 || mark>100){
        printf("inalid");
        return 0;
    }
    graded = mark/10;
    switch(graded){
        case 10:
        case 9:
        case 8:
        case 7:
        printf("A");
        break;

        case 6:
        printf("B");
        break;

        case 5:
        printf("C");
        break;

        case 4:
        printf("D");
        break;

        case 3:
        case 2:
        case 1:
        case 0:
        printf("E");
        break;

        default:
        printf("invalid mark");
    }

    return 0;
}