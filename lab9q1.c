#include <stdio.h>
#include <string.h>

int main() {
    char names[100][100]; // Assuming a maximum of 100 names with a maximum length of 100 characters each
    printf("Enter the number of names: ");
    int size;
    scanf("%d", &size);

    printf("Enter names:\n");
    for (int i = 0; i < size; i++) {
        scanf("%s", names[i]);
    }

    char temp[100];
    for (int i = 1; i < size; i++) {
        strcpy(temp, names[i]);
        int j = i - 1;
        while (j >= 0 && strcmp(names[j], temp) < 0) {
            strcpy(names[j + 1], names[j]);
            j = j - 1;
        }
        strcpy(names[j + 1], temp);
    }

    printf("Sorted names in descending alphabetical order:\n");
    for (int i = 0; i < size; i++) {
        printf("%s\n", names[i]);
    }

    return 0;
}
