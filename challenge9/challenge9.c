#include <stdio.h>
#define ROWS 5
#define COLS 8
void initializeSeats(int seats[ROWS][COLS]);
void displaySeats(int seats[ROWS][COLS]);
int bookSeat(int seats[ROWS][COLS], int row, int col);
int cancelSeat(int seats[ROWS][COLS], int row, int col);
int reserveGroup(int seats[ROWS][COLS], int groupSize);
void displayReport(int seats[ROWS][COLS]);
void initializeSeats(int seats[ROWS][COLS])
{
    int i, j;
    for(i=0; i<ROWS; i++)
        for(j=0; j<COLS; j++)
            seats[i][j] = 0;
}
void displaySeats(int seats[ROWS][COLS])
{
    int i, j;
    printf("\n0 = Available, 1 = Booked\n");
    printf("     ");
    for(j=1; j<=COLS; j++)
        printf("%d ", j);
    for(i=0; i<ROWS; i++)
    {
        printf("\nRow %d ", i+1);
        for(j=0; j<COLS; j++)
            printf("%d ", seats[i][j]);
    }
    printf("\n");
}
int bookSeat(int seats[ROWS][COLS], int row, int col)
{
    if(row<1 || row>5 || col<1 || col>8)
        return 0;
    if(seats[row-1][col-1] == 1)
        return 0;
    seats[row-1][col-1] = 1;
    return 1;
}
int cancelSeat(int seats[ROWS][COLS], int row, int col)
{
    if(row<1 || row>5 || col<1 || col>8)
        return 0;
    if(seats[row-1][col-1] == 0)
        return 0;
    seats[row-1][col-1] = 0;
    return 1;
}
int reserveGroup(int seats[ROWS][COLS], int groupSize)
{
    int i, j, k, free;
    if(groupSize<2 || groupSize>8)
        return 0;
    for(i=0; i<ROWS; i++)
    {
        for(j=0; j<=COLS-groupSize; j++)
        {
            free = 1;
            for(k=j; k<j+groupSize; k++)
            {
                if(seats[i][k] == 1)
                {
                    free = 0;
                    break;
                }
            }
            if(free == 1)
            {
                for(k=j; k<j+groupSize; k++)
                    seats[i][k] = 1;
                printf("Allocated Row: %d\n", i+1);
                printf("First Seat: %d\n", j+1);
                return 1;
            }
        }
    }
    return 0;
}

void displayReport(int seats[ROWS][COLS])
{
    int i, j, booked=0, free=0;
    int count, max=0;

    for(i=0; i<ROWS; i++)
    {
        count = 0;
        for(j=0; j<COLS; j++)
        {
            if(seats[i][j] == 1)
            {
                booked++;
                count++;
            }
            else
                free++;
        }
        if(count > max)
            max = count;
    }
    printf("\nBooked Seats: %d", booked);
    printf("\nAvailable Seats: %d", free);
    printf("\nOccupancy: %.2f%%", booked*100.0/40);
    printf("\nBusiest Row(s): ");
    for(i=0; i<ROWS; i++)
    {
        count = 0;
        for(j=0; j<COLS; j++)
            if(seats[i][j] == 1)
                count++;
        if(count == max)
            printf("%d ", i+1);
    }
    printf("\n");
}
int main()
{
    int seats[ROWS][COLS];
    int choice, row, col, size;
    initializeSeats(seats);
    do
    {
        printf("\n///// SEATSMART MENU /////");
        printf("\n1. Display Seats");
        printf("\n2. Book One Seat");
        printf("\n3. Cancel Booking");
        printf("\n4. Group Reservation");
        printf("\n5. Occupancy Report");
        printf("\n6. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                displaySeats(seats);
                break;
            case 2:
                printf("Enter row and seat: ");
                scanf("%d%d", &row, &col);
                if(bookSeat(seats, row, col))
                {
                    printf("Booking Successful!\n");
                    displaySeats(seats);
                }
                else
                    printf("Invalid or already booked seat!\n");
                break;
            case 3:
                printf("Enter row and seat: ");
                scanf("%d%d", &row, &col);
                if(cancelSeat(seats, row, col))
                {
                    printf("Cancellation Successful!\n");
                    displaySeats(seats);
                }
                else
                    printf("Invalid or free seat!\n");
                break;
            case 4:
                printf("Enter group size (2-8): ");
                scanf("%d", &size);
                if(reserveGroup(seats, size))
                {
                    printf("Group Booking Successful!\n");
                    displaySeats(seats);
                }
                else
                    printf("Group Reservation Failed!\n");
                break;
            case 5:
                displayReport(seats);
                break;
            case 6:
                printf("Thank you for using SEATSMART!\n");
                break;
            default:
                printf("Invalid menu choice!\n");
        }

    } while(choice != 6);
    return 0;
}
