#include <stdio.h>
#include <math.h>

#define TITLE "DECIMAL TO RADIX-i converter"
#define AUTHOR "Name"
#define YEAR 2023
#define MAX_SIZE 100

void Dec2RadixI(int decValue, int radValue) {
    int list[MAX_SIZE];
    int size = 0;

    // Convert decimal to binary
    while (decValue > 0) {
        list[size++] = decValue % radValue;
        decValue /= radValue;
    }

    // Print the binary representation
    printf("Binary representation: ");
    for (int i = size - 1; i >= 0; i--) {
        printf("%d", list[i]);
    }
    printf("\n");
}

int main() {
    printf("*****************************\n");
    printf(" %s\n", TITLE);
    printf(" Written by: %s\n", AUTHOR);
    printf(" Date: %d\n", YEAR);
    printf("*****************************\n");

    while (1) {
        int decValue;
        printf("Enter a decimal number: ");
        scanf("%d", &decValue);
        if (decValue < 0) {
            printf("EXIT\n");
            break;
        }
        printf("The number you have entered is %d\n", decValue);

        int radValue;
        printf("Enter a radix for the converter between 2 and 16: ");
        scanf("%d", &radValue);
        printf("The radix you have entered is %d\n", radValue);

        Dec2RadixI(decValue, radValue);
            // Calculate and print log2 of the number
        printf("The log2 of the number is %.2f\n", log2(decValue));

        // Calculate and print integer division result
        printf("The integer result of the number divided by %d is %d\n", radValue, decValue / radValue);

       // Calculate and print remainder
       printf("The remainder is %d\n", decValue % radValue);
    }

    return 0;
}
