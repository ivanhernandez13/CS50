#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
	//delcare float and assigns user input until it is positive
	float n;
	do 
	{
	printf("How much change is owed?\n");
	n = GetFloat();
	}
	while (n < 0);
	
	//rounds user input up and stores in an int, initializes variable to count coins
	int change = round(n*100);
	int counter = 0;
	
	//finds out maximum number of quarters needed and removes that value in quarters from change
	if (change >= 25)
	{
		counter += (change/25);
		change %= 25;
	}
	
	//finds out maximum number of dimes needed and removes that value in dimes from change
	if (change >= 10)
	{
		counter += (change/10);
		change %= 10;
	}
	
	//finds out maximum number of nickels needed and removes that value in nickels from change
	if (change >= 5)
	{
		counter += (change/5);
		change %= 5;
	}
	
	//counts down the remaining change until it reaches 0, counts up number of coins
	if (change > 0)
	{
		do
		{
			change--;
			counter++;
		}
		while (change > 0);
	}
	
	printf("%d\n",counter);
}
