
//Assignment 2

//Dynamic Memory Management.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int *data;      // Pointer to array data
    int size;       // Current number of elements
    int capacity;   // Total allocated capacity
} DynamicArray;

// Function prototypes
DynamicArray* createArray(int initialCapacity);
void insertElement(DynamicArray *arr, int value);
void deleteElement(DynamicArray *arr, int index);
int getElement(DynamicArray *arr, int index);
void displayArray(DynamicArray *arr);
void reverseArray(DynamicArray *arr);
int searchElement(DynamicArray *arr, int value);
void sortArray(DynamicArray *arr);
void freeArray(DynamicArray *arr);
void resizeArray(DynamicArray *arr);

int main() {
    printf("===================================\n");
    printf("   DYNAMIC ARRAY IMPLEMENTATION\n");
    printf("===================================\n\n");
    
    // Create array with initial capacity 5
    DynamicArray *arr = createArray(5);
    if (arr == NULL) {
        printf("Failed to create array. Exiting.\n");
        return 1;
    }
    
    printf("Created array with capacity: %d\n", arr->capacity);
    
    // Add 10 elements (will trigger resize)
    printf("\n=== Adding 10 elements ===\n");
    for (int i = 1; i <= 10; i++) {
        insertElement(arr, i * 10);
        printf("Inserted %d: Size=%d, Capacity=%d\n", 
               i * 10, arr->size, arr->capacity);
    }
    
    // Display array
    printf("\n=== Current Array ===\n");
    displayArray(arr);
    
    // Search for element
    printf("\n=== Searching for elements ===\n");
    int searchValues[] = {30, 55, 100};
    for (int i = 0; i < 3; i++) {
        int index = searchElement(arr, searchValues[i]);
        if (index != -1) {
            printf("Value %d found at index %d\n", searchValues[i], index);
        } else {
            printf("Value %d not found\n", searchValues[i]);
        }
    }
    
    // Get element at specific index
    printf("\n=== Getting elements ===\n");
    printf("Element at index 5: %d\n", getElement(arr, 5));
    printf("Element at index 0: %d\n", getElement(arr, 0));
    
    // Delete elements
    printf("\n=== Deleting elements ===\n");
    deleteElement(arr, 2);  // Delete element at index 2
    printf("After deleting index 2:\n");
    displayArray(arr);
    
    deleteElement(arr, 0);  // Delete first element
    printf("After deleting index 0:\n");
    displayArray(arr);
    
    deleteElement(arr, arr->size - 1);  // Delete last element
    printf("After deleting last element:\n");
    displayArray(arr);
    
    // Reverse array
    printf("\n=== Reversing array ===\n");
    reverseArray(arr);
    printf("After reversing:\n");
    displayArray(arr);
    
    // Sort array
    printf("\n=== Sorting array ===\n");
    sortArray(arr);
    printf("After sorting:\n");
    displayArray(arr);
    
    // Test edge cases
    printf("\n=== Testing edge cases ===\n");
    
    // Try to delete from empty position
    DynamicArray *emptyArr = createArray(5);
    printf("Trying to delete from empty array: ");
    deleteElement(emptyArr, 0);  // Should show error
    
    // Get from invalid index
    printf("Trying to get from invalid index: ");
    getElement(arr, 100);  // Should show error
    
    // Free memory
    printf("\n=== Freeing memory ===\n");
    freeArray(arr);
    freeArray(emptyArr);
    
    printf("\nAll arrays freed successfully!\n");
    printf("Run with valgrind to check for memory leaks:\n");
    printf("  valgrind --leak-check=full ./program\n");
    
    return 0;
}

DynamicArray* createArray(int initialCapacity) {
    if (initialCapacity <= 0) {
        printf("Error: Initial capacity must be positive\n");
        return NULL;
    }
    
    DynamicArray *arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (arr == NULL) {
        printf("Error: Memory allocation failed for DynamicArray\n");
        return NULL;
    }
    
    arr->data = (int*)malloc(initialCapacity * sizeof(int));
    if (arr->data == NULL) {
        printf("Error: Memory allocation failed for array data\n");
        free(arr);
        return NULL;
    }
    
    arr->size = 0;
    arr->capacity = initialCapacity;
    
    return arr;
}

void resizeArray(DynamicArray *arr) {
    int newCapacity = arr->capacity * 2;
    int *newData = (int*)realloc(arr->data, newCapacity * sizeof(int));
    
    if (newData == NULL) {
        printf("Error: Memory reallocation failed\n");
        return;
    }
    
    arr->data = newData;
    arr->capacity = newCapacity;
    
    printf("Array resized to capacity: %d\n", newCapacity);
}

void insertElement(DynamicArray *arr, int value) {
    if (arr == NULL) {
        printf("Error: Array is NULL\n");
        return;
    }
    
    // Resize if array is full
    if (arr->size >= arr->capacity) {
        resizeArray(arr);
    }
    
    arr->data[arr->size] = value;
    arr->size++;
}

void deleteElement(DynamicArray *arr, int index) {
    if (arr == NULL) {
        printf("Error: Array is NULL\n");
        return;
    }
    
    if (arr->size == 0) {
        printf("Error: Cannot delete from empty array\n");
        return;
    }
    
    if (index < 0 || index >= arr->size) {
        printf("Error: Index %d out of bounds (size=%d)\n", index, arr->size);
        return;
    }
    
    // Shift elements left
    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    
    arr->size--;
    
    // Optional: Shrink array if it's too empty
    if (arr->size > 0 && arr->size <= arr->capacity / 4) {
        int newCapacity = arr->capacity / 2;
        int *newData = (int*)realloc(arr->data, newCapacity * sizeof(int));
        
        if (newData != NULL) {
            arr->data = newData;
            arr->capacity = newCapacity;
            printf("Array shrunk to capacity: %d\n", newCapacity);
        }
    }
}

int getElement(DynamicArray *arr, int index) {
    if (arr == NULL) {
        printf("Error: Array is NULL\n");
        return -1;
    }
    
    if (index < 0 || index >= arr->size) {
        printf("Error: Index %d out of bounds (size=%d)\n", index, arr->size);
        return -1;
    }
    
    return arr->data[index];
}

void displayArray(DynamicArray *arr) {
    if (arr == NULL) {
        printf("Error: Array is NULL\n");
        return;
    }
    
    printf("Array [Size=%d, Capacity=%d]:\n", arr->size, arr->capacity);
    
    if (arr->size == 0) {
        printf("  (empty)\n");
        return;
    }
    
    printf("  Index\tValue\n");
    printf("  -----\t-----\n");
    
    for (int i = 0; i < arr->size; i++) {
        printf("  [%d]\t%d\n", i, arr->data[i]);
    }
}

void reverseArray(DynamicArray *arr) {
    if (arr == NULL) {
        printf("Error: Array is NULL\n");
        return;
    }
    
    if (arr->size <= 1) {
        return;  // Nothing to reverse
    }
    
    int start = 0;
    int end = arr->size - 1;
    
    while (start < end) {
        // Swap elements
        int temp = arr->data[start];
        arr->data[start] = arr->data[end];
        arr->data[end] = temp;
        
        start++;
        end--;
    }
}

int searchElement(DynamicArray *arr, int value) {
    if (arr == NULL) {
        printf("Error: Array is NULL\n");
        return -1;
    }
    
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] == value) {
            return i;
        }
    }
    
    return -1;
}

void sortArray(DynamicArray *arr) {
    if (arr == NULL) {
        printf("Error: Array is NULL\n");
        return;
    }
    
    if (arr->size <= 1) {
        return;  // Already sorted
    }
    
    // Bubble sort (simple implementation)
    for (int i = 0; i < arr->size - 1; i++) {
        for (int j = 0; j < arr->size - i - 1; j++) {
            if (arr->data[j] > arr->data[j + 1]) {
                // Swap
                int temp = arr->data[j];
                arr->data[j] = arr->data[j + 1];
                arr->data[j + 1] = temp;
            }
        }
    }
}

void freeArray(DynamicArray *arr) {
    if (arr == NULL) {
        return;
    }
    
    if (arr->data != NULL) {
        free(arr->data);
        arr->data = NULL;
    }
    
    free(arr);
}