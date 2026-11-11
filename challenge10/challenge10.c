#include <stdio.h>
#define ZONES 5
#define DAYS 7
void inputData(float temp[ZONES][DAYS],
float humidity[ZONES][DAYS], int aqi[ZONES][DAYS]);
void displayData(float temp[ZONES][DAYS],
float humidity[ZONES][DAYS], int aqi[ZONES][DAYS]);
void calculateAverages(float temp[ZONES][DAYS],
float humidity[ZONES][DAYS], int aqi[ZONES][DAYS],
float avgTemp[ZONES], float avgHumidity[ZONES],
float avgAQI[ZONES]);
void detectRiskZones(float temp[ZONES][DAYS],
float humidity[ZONES][DAYS], int aqi[ZONES][DAYS],
int riskDays[ZONES]);
void computeGreenIndex(float avgTemp[ZONES],
float avgHumidity[ZONES], float avgAQI[ZONES],
float greenIndex[ZONES]);
void displayRanking(float greenIndex[ZONES]);
void displayRecommendations(float avgTemp[ZONES],
float avgHumidity[ZONES], float avgAQI[ZONES],
int riskDays[ZONES]);
char *names[ZONES] = {
    "Academic Block", "Hostel", "Library",
    "Cafeteria", "Sports Area"
};
void inputData(float t[ZONES][DAYS],
float h[ZONES][DAYS], int a[ZONES][DAYS])
{
    int i, j;
    for(i=0; i<ZONES; i++)
    {
        printf("\n%s\n", names[i]);
        for(j=0; j<DAYS; j++)
        {
            do {
                printf("Day %d Temperature: ", j+1);
                scanf("%f", &t[i][j]);
            } while(t[i][j]<10 || t[i][j]>50);
            do {
                printf("Day %d Humidity: ", j+1);
                scanf("%f", &h[i][j]);
            } while(h[i][j]<0 || h[i][j]>100);
            do {
                printf("Day %d AQI: ", j+1);
                scanf("%d", &a[i][j]);
            } while(a[i][j]<0 || a[i][j]>500);
        }
    }
}
void displayData(float t[ZONES][DAYS],
float h[ZONES][DAYS], int a[ZONES][DAYS])
{
    int i, j;
    printf("\nTEMPERATURE MATRIX\n");
    for(i=0; i<ZONES; i++) {
        printf("%s: ", names[i]);
        for(j=0; j<DAYS; j++)
            printf("%.1f ", t[i][j]);
        printf("\n");
    }
    printf("\nHUMIDITY MATRIX\n");
    for(i=0; i<ZONES; i++) {
        printf("%s: ", names[i]);
        for(j=0; j<DAYS; j++)
            printf("%.1f ", h[i][j]);
        printf("\n");
    }
    printf("\nAQI MATRIX\n");
    for(i=0; i<ZONES; i++) {
        printf("%s: ", names[i]);
        for(j=0; j<DAYS; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}
void calculateAverages(float t[ZONES][DAYS],
float h[ZONES][DAYS], int a[ZONES][DAYS],
float at[ZONES], float ah[ZONES], float aa[ZONES])
{
    int i, j;
    float st, sh, sa;
    for(i=0; i<ZONES; i++)
    {
        st=0; sh=0; sa=0;
        for(j=0; j<DAYS; j++)
        {
            st += t[i][j];
            sh += h[i][j];
            sa += a[i][j];
        }
        at[i]=st/7;
        ah[i]=sh/7;
        aa[i]=sa/7;
        printf("\n%s: Temp=%.2f Humidity=%.2f AQI=%.2f",
        names[i], at[i], ah[i], aa[i]);
    }
    printf("\n");
}
void detectRiskZones(float t[ZONES][DAYS],
float h[ZONES][DAYS], int a[ZONES][DAYS],
int riskDays[ZONES])
{
    int i, j, risk;
    for(i=0; i<ZONES; i++)
    {
        riskDays[i]=0;
        printf("\n%s Risk Days: ", names[i]);
        for(j=0; j<DAYS; j++)
        {
            risk = (a[i][j]>150 ||
                    t[i][j]>35 ||
                    h[i][j]>80);
            if(risk)
            {
                riskDays[i]++;
                printf("%d ", j+1);
            }
        }
        if(riskDays[i]==0)
            printf("None");

        printf("\nTotal Risk Days: %d\n", riskDays[i]);
    }
}
void computeGreenIndex(float at[ZONES],
float ah[ZONES], float aa[ZONES],
float greenIndex[ZONES])
{
    int i;
    float A, T, H, d;
    for(i=0; i<ZONES; i++)
    {
        A=100-aa[i]/5;
        d=at[i]-25;
        if(d<0) d=-d;
        T=100-4*d;
        d=ah[i]-50;
        if(d<0) d=-d;
        H=100-2*d;
        if(A<0) A=0;
        if(T<0) T=0;
        if(H<0) H=0;
        greenIndex[i]=0.4*A+0.3*T+0.3*H;
    }
}

void displayRanking(float g[ZONES])
{
    int i, j, rank;
    printf("\nGREEN INDEX RANKING\n");
    for(i=0; i<ZONES; i++)
    {
        rank=1;
        for(j=0; j<ZONES; j++)
            if(g[j]>g[i])
                rank++;
        printf("%s: %.2f Rank: %d\n",
        names[i], g[i], rank);
    }
}
void displayRecommendations(float at[ZONES],
float ah[ZONES], float aa[ZONES],
int riskDays[ZONES])
{
    int i;
    printf("\nENVIRONMENTAL RECOMMENDATIONS\n");
    for(i=0; i<ZONES; i++)
    {
        printf("\n%s:\n", names[i]);
        if(aa[i]>150)
            printf("- Reduce vehicle idling or improve ventilation.\n");
        if(at[i]>35)
            printf("- Provide shade or increase green cover.\n");
        if(ah[i]>80)
            printf("- Check ventilation or stagnant water.\n");
        if(aa[i]<=150 && at[i]<=35 && ah[i]<=80)
        {
            if(riskDays[i]>0)
                printf("- Review the flagged dates.\n");
            else
                printf("- Continue environmental monitoring.\n");
        }
    }
}
int main()
{
    float temp[ZONES][DAYS];
    float humidity[ZONES][DAYS];
    int aqi[ZONES][DAYS];

    float avgTemp[ZONES], avgHumidity[ZONES];
    float avgAQI[ZONES], greenIndex[ZONES];

    int riskDays[ZONES];
    int choice, dataReady=0;
    do
        
    {
        printf("\n--- ECOGUARD MENU ---\n");
        printf("1. Input / Update Data\n");
        printf("2. Display Data\n");
        printf("3. Zone-wise Averages\n");
        printf("4. Detect Risk Days\n");
        printf("5. Green Index and Ranking\n");
        printf("6. Recommendations\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        if(choice>=2 && choice<=6 && dataReady==0)
        {
            printf("Please enter data first!\n");
            continue;
        }
        switch(choice)
        {
            case 1:
                inputData(temp, humidity, aqi);
                dataReady=1;
                break;
            case 2:
                displayData(temp, humidity, aqi);
                break;
            case 3:
                calculateAverages(temp, humidity, aqi,
                avgTemp, avgHumidity, avgAQI);
                break;
            case 4:
                detectRiskZones(temp, humidity, aqi, riskDays);
                break;
            case 5:
                calculateAverages(temp, humidity, aqi,
                avgTemp, avgHumidity, avgAQI);
                computeGreenIndex(avgTemp, avgHumidity,
                avgAQI, greenIndex);
                displayRanking(greenIndex);
                break;
            case 6:
                calculateAverages(temp, humidity, aqi,
                avgTemp, avgHumidity, avgAQI);
                detectRiskZones(temp, humidity, aqi, riskDays);
                displayRecommendations(avgTemp, avgHumidity,
                avgAQI, riskDays);
                break;
            case 7:
                printf("Thank you for using ECOGUARD!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while(choice!=7);
    return 0;
}
