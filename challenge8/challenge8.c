#include <stdio.h>
#include <limits.h>

int main()
{
    int grid[6][6];
    int N, T;
    int i, j;
    int sum, maxRow, maxCol;
    int maxRisk, count = 0;
    int mainDiag = 0, secDiag = 0;
    int boundarySum = 0;
    int hotspotCount = 0;
    do
    {
        printf("Enter grid size N (3 to 6): ");
        scanf("%d", &N);

        if (N < 3 || N > 6)
            printf("Invalid N! Enter a value from 3 to 6.\n");

    } while (N < 3 || N > 6);
    printf("Enter the risk scores (0 to 100):\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            do
            {
                printf("Grid[%d][%d]: ", i + 1, j + 1);
                scanf("%d", &grid[i][j]);

                if (grid[i][j] < 0 || grid[i][j] > 100)
                    printf("Invalid score! Enter 0 to 100.\n");

            } while (grid[i][j] < 0 || grid[i][j] > 100);
        }
    }
    do
    {
        printf("Enter warning threshold T (1 to 100): ");
        scanf("%d", &T);

        if (T < 1 || T > 100)
            printf("Invalid threshold! Enter 1 to 100.\n");

    } while (T < 1 || T > 100);
    printf("\nGRIDWATCH Risk Grid:\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            printf("%4d", grid[i][j]);

        printf("\n");
    }
    maxRow = INT_MIN;
    for (i = 0; i < N; i++)
    {
        sum = 0;

        for (j = 0; j < N; j++)
            sum += grid[i][j];

        if (sum > maxRow)
            maxRow = sum;
    }
    printf("\nRow totals:\n");
    for (i = 0; i < N; i++)
    {
        sum = 0;

        for (j = 0; j < N; j++)
            sum += grid[i][j];
        printf("Row %d = %d\n", i + 1, sum);
    }
    printf("Highest row total = %d\n", maxRow);
    printf("Highest row number(s): ");
    for (i = 0; i < N; i++)
    {
        sum = 0;
        for (j = 0; j < N; j++)
            sum += grid[i][j];
        if (sum == maxRow)
            printf("%d ", i + 1);
    }
    printf("\n");
    maxCol = INT_MIN;
    for (j = 0; j < N; j++)
    {
        sum = 0;
        for (i = 0; i < N; i++)
            sum += grid[i][j];
        if (sum > maxCol)
            maxCol = sum;
    }
    printf("\nColumn totals:\n");
    for (j = 0; j < N; j++)
    {
        sum = 0;
        for (i = 0; i < N; i++)
            sum += grid[i][j];
        printf("Column %d = %d\n", j + 1, sum);
    }
    printf("Highest column total = %d\n", maxCol);
    printf("Highest column number(s): ");
    for (j = 0; j < N; j++)
    {
        sum = 0;
        for (i = 0; i < N; i++)
            sum += grid[i][j];
        if (sum == maxCol)
            printf("%d ", j + 1);
    }
    printf("\n");
    maxRisk = grid[0][0];
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (grid[i][j] > maxRisk)
                maxRisk = grid[i][j];
            if (grid[i][j] >= T)
                count++;
        }
    }
    printf("\nHighest risk score = %d\n", maxRisk);
    printf("Position(s) of highest risk:\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (grid[i][j] == maxRisk)
                printf("(%d, %d)\n", i + 1, j + 1);
        }
    }
    printf("Cells meeting or exceeding T = %d\n", count);
    for (i = 0; i < N; i++)
    {
        mainDiag += grid[i][i];
        secDiag += grid[i][N - 1 - i];
    }
    printf("\nMain diagonal sum = %d\n", mainDiag);
    printf("Secondary diagonal sum = %d\n", secDiag);
    if (mainDiag == secDiag)
        printf("Diagonal totals are balanced.\n");
    else
        printf("Diagonal totals are not balanced.\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (i == 0 || i == N - 1 ||
                j == 0 || j == N - 1)
            {
                boundarySum += grid[i][j];
            }
        }
    }
    printf("\nBoundary cell total = %d\n", boundarySum);
    printf("\nLocal hotspot position(s):\n");
    for (i = 1; i < N - 1; i++)
    {
        for (j = 1; j < N - 1; j++)
        {
            if (grid[i][j] > grid[i - 1][j] &&
                grid[i][j] > grid[i + 1][j] &&
                grid[i][j] > grid[i][j - 1] &&
                grid[i][j] > grid[i][j + 1] &&
                grid[i][j] >= T)
            {
                printf("(%d, %d) with score %d\n",
                       i + 1, j + 1, grid[i][j]);
                hotspotCount++;
            }
        }
    }
    if (hotspotCount == 0)
        printf("No local hotspots found.\n");
    printf("\nGRIDWATCH Decision: ");
    if (hotspotCount > 0)
        printf("CRITICAL\n");
    else if (count >= N)
        printf("WARNING\n");
    else
        printf("NORMAL\n");
    return 0;
}


