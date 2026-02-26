#include <stdio.h>

int main() {
    int arr[10] = {245, 23, 67, 80, 21, 2, 87, 100, 101, 2000};
    int max, min;
    max = min = arr[0];

    for (int i = 1; i < 10; i++) {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }
    printf("Maximum: %d\n", max);
    printf("Minimum: %d\n", min);

    return 0;
}