#include <stdio.h>

int main() {
    double num1, num2, sum;

    // Prompt the user for input
    printf("Enter the first number: ");
    scanf("%lf", &num1);

    printf("Enter the second number: ");
    scanf("%lf", &num2);

    // Calculate the sum
    sum = num1 + num2;

    // Display the result
    printf("The sum of %.2lf and %.2lf is %.2lf\n", num1, num2, sum);

    return 0;
}
