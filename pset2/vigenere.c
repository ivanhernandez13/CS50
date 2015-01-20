#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

/*
ASCII Values
65: A	90: Z
97: a	122: z
*/

int main(int argc, char* argv[])
{
	//checks for only 2 command line arguments
	if (argc != 2)
	{
		printf("Usage: ./caeser keyword\n");
		return 1;
	}
	
	//saves second command line argument as key
	string key = argv[1];
	
	//stores length of key
	int j = strlen(key);
	
	//iterates over all characters in key
	for (int i = 0; i < j; i++)
	{
		//verify's if letters
		if (isalpha(key[i]) == 0)
		{
			printf("Error, keyword must be all letters!\n");
			return 1;
		}
		//converts uppercase letter to ascii value
		else if (isupper(key[i]))
		{
			key[i] -= 65;
		}
		//converts lowercase letter to ascii value
		else
		{
			key[i] -= 97;
		}
	}	
	
	//gets user string to encrypt
	char* e = GetString();
	
	//stores length of string
	int l = 0;
	for (int k = 0, m = strlen(e); k < m; k++)
	{
		//checks if letter
		if (isalpha(e[k]))
		{
			//loops from Z to A
			if (isupper(e[k]) && e[k] + key[l] > 90)
			{
				e[k] -= 26;
			}
			//loops from z to a
			if (islower(e[k]) && e[k] + key[l] > 122)
			{
				e[k] -= 26;
			}
			//adds key to string
			e[k] = e[k] + key[l];
			printf("%c",e[k]);
			//loops keyword
			l++;
			if (l == j)
			l = 0;
		}
		//outputs unchanged if not letter
		else
		{
		printf("%c",e[k]);
		}
	}
	printf("\n");
}
