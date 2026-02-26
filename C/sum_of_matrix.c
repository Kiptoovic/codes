#include <stdio.h>

int main()
{
    //3x3 Matrix
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    

    // Calculate sum of the matrix
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum += matrix[i][j];
        }
    }
    
    printf("Sum of the matrix: %d\n", sum);
    
    return 0;
}