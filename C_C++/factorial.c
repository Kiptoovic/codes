#include <stdio.h>
int sum(int x, int y)
{
    int z;
    z = x + y;
    return z; 
}
//int sum(int a, int b);

int main()
{
    int a = 10;
    int b =20;
    int ret;
    ret = sum(a, b);    //function call
    printf("The result is: %d\n", ret);
    return 0;
}



/*
    circumstances of reference
    do the following
    =>what recursive function are
    =>implement
    =>get programe using recursion
*/

//importance of main function
