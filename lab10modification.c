#include <stdio.h>
#include <stdlib.h>

// Function to compare integers for sorting
int compareIntegers(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to find and display three duplicate values in the sequence
void findThreeDuplicates(int arr[], int n) {
    // Sort the array
    qsort(arr, n, sizeof(int), compareIntegers);

    int duplicateCount = 0;
    printf("Duplicate elements: ");
    for (int i = 1; i < n + 3; i++) {
        if (arr[i] == arr[i - 1]) {
            printf("%d ", arr[i]);
            duplicateCount++;
            if (duplicateCount == 3) {
                break; // Exit the loop after finding three duplicates
            }
        }
    }
}

int main() {
    int n, i;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    int *arr = (int *)malloc((n + 3) * sizeof(int));

    printf("Enter the elements of the sequence: \n");
    for (i = 0; i < n + 3; i++)
        scanf("%d", &arr[i]);

    findThreeDuplicates(arr, n + 3);

    free(arr);

    return 0;
}