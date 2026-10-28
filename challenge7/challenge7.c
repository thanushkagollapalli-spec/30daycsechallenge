#include <stdio.h>
int main(){
    int n, i, j, id, count;
    int missing = 0, duplicate = 0;
    int missingCount = 0, duplicateCount = 0;
    int invalidLog = 0, outOfOrder = 0;
    int r, target, targetCount = 0;
    do
    {
        printf("Enter N (5 to 15): ");
        scanf("%d", &n);
        if (n < 5 || n > 15)
        {
            printf("Invalid N. Enter again.\n");
        }
    } while (n < 5 || n > 15);
    int ticket[15];
    for (i = 0; i < n; i++)
    {
        do
        {
            printf("Enter ticket ID at position %d: ", i + 1);
            scanf("%d", &ticket[i]);
            if (ticket[i] < 1 || ticket[i] > n)
            {
                printf("Invalid ticket ID. Enter again.\n");
            }
        } while (ticket[i] < 1 || ticket[i] > n);
    }
    printf("\nOriginal scan sequence: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", ticket[i]);
    }
    printf("\n");
    for (id = 1; id <= n; id++)
    {
        count = 0;
        for (i = 0; i < n; i++)
        {
            if (ticket[i] == id)
            {
                count++;
            }
        }
        if (count == 0)
        {
            missing = id;
            missingCount++;
        }
        else if (count == 2)
        {
            duplicate = id;
            duplicateCount++;
        }
        else if (count != 1)
        {
            invalidLog = 1;
        }
    }
    if (missingCount != 1 || duplicateCount != 1 ||
        invalidLog == 1)
    {
        printf("Invalid scan log.\n");
    }
    else
    {
        printf("Duplicate ticket ID: %d\n", duplicate);
        printf("Missing ticket ID: %d\n", missing);
    }
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (ticket[i] > ticket[j])
            {
                outOfOrder++;
            }
        }
    }
    printf("Out-of-order pairs: %d\n", outOfOrder);
    printf("Enter the last two digits of your registration number: ");
    scanf("%d", &r);
    target = (r % n) + 1;
    printf("Target ticket ID: %d\n", target);
    printf("Positions of target ID: ");
    for (i = 0; i < n; i++)
    {
        if (ticket[i] == target)
        {
            printf("%d ", i + 1);
            targetCount++;
        }
    }
    if (targetCount == 0)
    {
        printf("None");
    }
    printf("\nOccurrence count: %d\n", targetCount);
    return 0;
}
