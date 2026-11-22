#include <stdio.h>
#define ZONES 5
#define DAYS 7
const char *getZoneName(int z)
{
    switch(z)
    {
        case 0: return "Academic Block";
        case 1: return "Hostel";
        case 2: return "Library";
        case 3: return "Cafeteria";
        case 4: return "Sports Complex";
    }
    return "Unknown";
}
int readInt(char message[], int min, int max)
{
    int n, ch;
    while(1)
    {
        printf("%s", message);
        if(scanf("%d", &n) == 1)
        {
            while((ch = getchar()) != '\n' && ch != EOF);
            if(n >= min && n <= max)
                return n;
        }
        else
        {
            while((ch = getchar()) != '\n' && ch != EOF);
        }
        printf("Invalid input! Enter value between %d and %d.\n",
               min, max);
    }
}
void inputWaterData(int usage[ZONES][DAYS],
                    int dailyTarget[ZONES])
{
    char msg[100];
    int i, j;
    printf("\n--- ENTER WATER DATA ---\n");
    for(i = 0; i < ZONES; i++)
    {
        printf("\n%s\n", getZoneName(i));
        sprintf(msg, "Enter daily target (100-50000): ");
        dailyTarget[i] = readInt(msg, 100, 50000);
        for(j = 0; j < DAYS; j++)
        {
            sprintf(msg, "Enter Day %d usage: ", j + 1);
            usage[i][j] = readInt(msg, 0, 50000);
        }
    }
}
void displayWaterData(int usage[ZONES][DAYS],
                      int dailyTarget[ZONES])
{
    int i, j;
    printf("\n--- WATER CONSUMPTION MATRIX ---\n");
    printf("%-18s", "Zone");
    for(j = 0; j < DAYS; j++)
        printf("Day%-5d", j + 1);
    printf("Target\n");
    for(i = 0; i < ZONES; i++)
    {
        printf("%-18s", getZoneName(i));
        for(j = 0; j < DAYS; j++)
            printf("%-8d", usage[i][j]);
        printf("%d\n", dailyTarget[i]);
    }
}
void calculateZoneStats(int *zoneUsage, int *total,
                        float *average, int *peakUsage,
                        int *peakDay)
{
    int i, sum = 0;
    *peakUsage = *zoneUsage;
    *peakDay = 1;
    for(i = 0; i < DAYS; i++)
    {
        sum += *(zoneUsage + i);
        if(*(zoneUsage + i) > *peakUsage)
        {
            *peakUsage = *(zoneUsage + i);
            *peakDay = i + 1;
        }
    }
    *total = sum;
    *average = (float)sum / DAYS;
}
void detectWaterAlerts(int *zoneUsage, int dailyTarget,
                       int *overLimitDays, int *totalExcess,
                       int *spikeDays, int *alertDays)
{
    int i, over, spike;
    *overLimitDays = 0;
    *totalExcess = 0;
    *spikeDays = 0;
    *alertDays = 0;
    for(i = 0; i < DAYS; i++)
    {
        over = 0;
        spike = 0;
        if(*(zoneUsage + i) > dailyTarget)
        {
            (*overLimitDays)++;
            *totalExcess += *(zoneUsage + i) - dailyTarget;
            over = 1;
        }
        if(i > 0 &&
           *(zoneUsage + i) > *(zoneUsage + i - 1) * 1.40)
        {
            (*spikeDays)++;
            spike = 1;
        }
        if(over || spike)
            (*alertDays)++;
    }
}
void generateAuditReport(int usage[ZONES][DAYS],
                         int dailyTarget[ZONES],
                         int excessByZone[ZONES],
                         int overLimitByZone[ZONES],
                         int spikeByZone[ZONES],
                         int alertByZone[ZONES])
{
    int i, total, peak, peakDay;
    float average;
    printf("\n========== WATER AUDIT REPORT ==========\n");
    for(i = 0; i < ZONES; i++)
    {
        calculateZoneStats(&usage[i][0], &total,
                           &average, &peak, &peakDay);
        detectWaterAlerts(&usage[i][0], dailyTarget[i],
                          &overLimitByZone[i], &excessByZone[i],
                          &spikeByZone[i], &alertByZone[i]);
        printf("\nZone: %s\n", getZoneName(i));
        printf("Weekly Total       : %d litres\n", total);
        printf("Daily Average      : %.2f litres\n", average);
        printf("Highest Usage      : %d litres\n", peak);
        printf("Peak Day           : Day %d\n", peakDay);
        printf("Over-limit Days    : %d\n", overLimitByZone[i]);
        printf("Total Excess       : %d litres\n", excessByZone[i]);
        printf("Sudden Spike Days  : %d\n", spikeByZone[i]);
        printf("Unique Alert Days  : %d\n", alertByZone[i]);
    }
}
void rankZones(int excessByZone[ZONES])
{
    int i, j, rank, max = 0;
    printf("\n========== ZONE RANKING ==========\n");
    for(i = 0; i < ZONES; i++)
    {
        if(excessByZone[i] > max)
            max = excessByZone[i];
    }
    printf("Zone(s) with greatest excess:\n");
    for(i = 0; i < ZONES; i++)
    {
        if(excessByZone[i] == max)
            printf("%s - %d litres\n",
                   getZoneName(i), max);
    }
    printf("\nRank List:\n");
    for(i = 0; i < ZONES; i++)
    {
        rank = 1;
        for(j = 0; j < ZONES; j++)
        {
            if(excessByZone[j] > excessByZone[i])
                rank++;
        }
        printf("Rank %d : %-18s %d litres\n",
               rank, getZoneName(i), excessByZone[i]);
    }
}
void displayConservationActions(int overLimitByZone[ZONES],
                                int spikeByZone[ZONES],
                                int excessByZone[ZONES])
{
    int i;
    printf("\n======= CONSERVATION ACTIONS =======\n");
    for(i = 0; i < ZONES; i++)
    {
        printf("\n%s:\n", getZoneName(i));
        if(spikeByZone[i] > 0)
            printf("- Check for leaks or unexpected water usage.\n");
        if(overLimitByZone[i] >= 3)
            printf("- Conduct a water audit and reduction plan.\n");
        else if(overLimitByZone[i] >= 1)
            printf("- Monitor excess days and inspect taps or valves.\n");
        if(overLimitByZone[i] == 0 && spikeByZone[i] == 0)
            printf("- Maintain current good practices.\n");
        printf("Total excess: %d litres\n", excessByZone[i]);
    }
}
int main()
{
    int usage[ZONES][DAYS];
    int dailyTarget[ZONES];
    int excessByZone[ZONES] = {0};
    int overLimitByZone[ZONES] = {0};
    int spikeByZone[ZONES] = {0};
    int alertByZone[ZONES] = {0};
    int choice, reportGenerated = 0;
    inputWaterData(usage, dailyTarget);
    do
    {
        printf("\n========== WATERWISE MENU ==========\n");
        printf("1. Display Water Data\n");
        printf("2. Generate Audit Report\n");
        printf("3. Rank Zones by Excess\n");
        printf("4. Conservation Actions\n");
        printf("5. Exit\n");
        choice = readInt("Enter your choice: ", 1, 5);
        switch(choice)
        {
            case 1:
                displayWaterData(usage, dailyTarget);
                break;
            case 2:
                generateAuditReport(usage, dailyTarget,
                                    excessByZone,
                                    overLimitByZone,
                                    spikeByZone,
                                    alertByZone);
                reportGenerated = 1;
                break;
            case 3:
                if(reportGenerated)
                    rankZones(excessByZone);
                else
                    printf("Please generate the audit report first!\n");
                break;
            case 4:
                if(reportGenerated)
                    displayConservationActions(overLimitByZone,
                                               spikeByZone,
                                               excessByZone);
                else
                    printf("Please generate the audit report first!\n");
                break;
            case 5:
                printf("\nThank you for using WATERWISE!\n");
                break;
        }
    } while(choice != 5);
    return 0;
}
