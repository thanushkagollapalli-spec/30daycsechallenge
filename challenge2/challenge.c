#include <stdio.h>
int main()
{
  float distance, mileage, fuelPrice;
  float fuelRequired, totalCost;
  printf("Enter distance in km");
  scanf("%f", &distance);
  printf("Enter vehicle mileage km/l");
  scanf("%f", &mileage);
  printf("Enter fuel price per litre");
  scanf("%f", &fuelPrice);
  fuelRequired = distance / mileage;
  totalCost = fuelRequired * fuelPrice;
  printf("\n----- Trip Calculation -----\n");
  printf("Distance : %.2f km\n", distance);
  printf("Mileage : %.2f km/l\n", mileage);
  printf("Fuel Required : %.2f litres\n", fuelRequired);
  printf("Fuel Price : Rs. %.2f/litre\n", fuelPrice);
  printf("Total Fuel Cost: Rs. %.2f\n", totalCost);
  return 0;
}
