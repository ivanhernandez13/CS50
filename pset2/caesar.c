#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

/*
ASCII Values
65: A	90: Z
97: a	122: z
*/

int main(int argc, char* argv[])
{
	//checks for two command line arguments
	if (argc != 2)
	{
		printf("usage: ./ceaser number\n");
		return 1;
	}
	
	//converts the char inputted by user into an int
	int n = atoi(argv[1]) % 26;
	
	//gets a user string to encrypt
	char* input = GetString();
	
	//iterates over every letter in the string
	for(int i = 0; i < strlen(input); i++)
	{
		//checks if current character is indeed a letter
		if (isalpha(input[i]))
		{	
			//loops the alphabet if value goes past z
			if (isupper(input[i]) && (input[i] + n) > 90)
			{
			input[i] = (int)input[i] - 26;
			}
			if (islower(input[i]) && (input[i] + n) > 122)
			{
			input[i] = (int)input[i] - 26;
			}
			//adds the value of the key to the ascii value of the letter
			input[i] = (int)input[i] + n;
		}
	}
	//prints out the encrypted message
	for(int j = 0; j < strlen(input); j++)
	{
		printf("%c",input[j]);
	}
	printf("\n");
}
