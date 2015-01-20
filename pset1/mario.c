#include <stdio.h>
#include <cs50.h>

int main(void)
{
	//declares n outside of any loops
	int n;
	
	//gets a number until it is between 1-23
	do {printf("Give me a number between 1 and 23!\n"); n = GetInt();}
	while (n < 0 || n > 23);
	
	//loops the printing proccess by n times
	for (int i = 1; i <= n; i++)
	{
		//prints out spaces
		for (int j = n - i; j > 0; j--)
		{
			printf(" ");
		}
		//prints out hashtags
		for (int k = (n-1)-i; k < n; k++)
		{
			printf("#");
		}
		printf("\n");
	}
}
