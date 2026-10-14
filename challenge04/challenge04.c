#include <stdio.h>

int main() {
    float amount;
    float smallTotal = 0, mediumTotal = 0, largeTotal = 0;
    float total = 0, average;
    int smallCount = 0, mediumCount = 0, largeCount = 0;
    int validCount = 0;

    printf("LOOPLAB - Daily Expense Analyzer\n");

    while (1) {
        printf("\nEnter expense amount (0 to stop): ");
        scanf("%f", &amount);

        if (amount == 0) {
            break;
        }

        if (amount < 0) {
            printf("Invalid amount! Enter a positive value.\n");
        }
        else {
            validCount++;
            total += amount;

            if (amount < 100) {
                smallCount++;
                smallTotal += amount;
                printf("Category: Small\n");
            }
            else if (amount < 500) {
                mediumCount++;
                mediumTotal += amount;
                printf("Category: Medium\n");
            }
            else {
                largeCount++;
                largeTotal += amount;
                printf("Category: Large\n");
            }
        }
    }

    printf("\n===== EXPENSE SUMMARY =====\n");
    printf("Number of valid expenses: %d\n", validCount);
    printf("Total valid expenses: Rs. %.2f\n", total);

    printf("\nSmall expenses: %d\n", smallCount);
    printf("Small total: Rs. %.2f\n", smallTotal);

    printf("\nMedium expenses: %d\n", mediumCount);
    printf("Medium total: Rs. %.2f\n", mediumTotal);

    printf("\nLarge expenses: %d\n", largeCount);
    printf("Large total: Rs. %.2f\n", largeTotal);

    if (validCount > 0) {
        average = total / validCount;
        printf("\nAverage expense: Rs. %.2f\n", average);
    }
    else {
        printf("\nNo valid expenses were entered.\n");
    }

    return 0;
}
