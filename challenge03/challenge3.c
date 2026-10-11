#include <stdio.h>

int main()
{
    float purchase, discount, amount, distance;
    float delivery, finalAmount;
    int customer;

    printf("Enter purchase amount: ");
    scanf("%f", &purchase);

    printf("Enter customer type (1-Student, 2-Regular): ");
    scanf("%d", &customer);

    printf("Enter delivery distance in km: ");
    scanf("%f", &distance);

    if (customer == 1)
    {
        if (purchase >= 2000)
            discount = purchase * 15 / 100;
        else
            discount = purchase * 10 / 100;
    }
    else if (customer == 2)
    {
        if (purchase >= 3000)
            discount = purchase * 8 / 100;
        else
            discount = 0;
    }
    else
    {
        printf("Invalid customer type");
        return 0;
    }

    amount = purchase - discount;

    if (distance <= 5)
        delivery = 40;
    else if (distance <= 15)
        delivery = 70;
    else
        delivery = 100;

    finalAmount = amount + delivery;

    printf("\nPurchase Amount = Rs. %.2f", purchase);
    printf("\nDiscount Amount = Rs. %.2f", discount);
    printf("\nDelivery Charge = Rs. %.2f", delivery);
    printf("\nFinal Payable Amount = Rs. %.2f", finalAmount);

    return 0;
}
