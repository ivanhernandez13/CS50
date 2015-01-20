/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <math.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    /*
    Now that sort (presumably) works, it’s time to improve upon search, the other function that lives in helpers.c. Recall that your first version implemented linear search. Rip out the lines that you wrote earlier (sniff) and re-implement search as Binary Search, that divide-and-conquer strategy that we employed in Week 0 and again in Week 3. You are welcome to take an iterative or, per Week 4, a recursive approach. If you pursue the latter, though, know that you may not change our declaration of search, but you may write a new, recursive function (that perhaps takes different parameters) that search itself calls. When it comes time to submit this problem set, it suffices to submit this new-and-improved version of search; you needn’t submit your original version that used linear search.
    */
    //if n is negetive stop and return false
    if (n < 0) {return false;}
    int max = n;
    int low = 0;
    int half = ceil((max + low) / 2);
    
    while (max - low != -1)
     {
       		if (values[half] == value)
       		{
       			return true;
       		}
       		else if (values[half] > value)
       		{
       			max = half -1;
       			half = ceil((max + low) / 2);
       		}
       		else if (values[half] < value)
       		{
       			low = half + 1;
       			half = ceil((max + low) / 2);
       		}
       }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    //declares swap to check if any swaps were done, temp to store value while swapping
    int swap = 0;
    int max = n - 1;
    do {
    	swap = 0;
    	//iterates through the 2nd and last number in the array
    	//skips 1st value because algorithm compares previous value
		for (int j = 0; j < max; j++)
		{
		    int k = j + 1;
			if (values[j] > values[k])
			{
				int temp = values[j];
				values[j] = values[k];
				values[k] = temp;
				swap++;
			}
		}
       }
    while (swap != 0);
}
