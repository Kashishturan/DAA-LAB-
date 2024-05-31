#include <stdio.h>

void findDuplicates(int arr[], int n) {
    int XOR = 0;

    for (int i = 1; i <= n; i++) {
        XOR ^= i;
    }

    for (int i = 0; i < n + 2; i++) {
        XOR ^= arr[i];
    }

    int rightmost_set_bit = XOR & -XOR;

    int x = 0, y = 0;

    for (int i = 1; i <= n; i++) {
        if (i & rightmost_set_bit)
            x ^= i;
        else
            y ^= i;
    }

    for (int i = 0; i < n + 2; i++) {
        if (arr[i] == x) {
            printf("The first element that appears twice is: %d\n", x);
            printf("The second element that appears twice is: %d\n", y);
            return;
        }
    }
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    int sequence[n+2];
    printf("Enter the sequence of %d elements (with two elements appearing twice):\n", n+2);
    for (int i = 0; i < n + 2; i++) {
        scanf("%d", &sequence[i]);
    }

    findDuplicates(sequence, n);

    return 0;
}
