/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"

int words_loaded = 0;
node* hashtable[HASH - 1];
node* cursor = NULL;
node* data = NULL;
node* tracker[HASH - 1]; /** used to free first 'data' malloced **/

/** Returns true if word is in dictionary else false. **/
bool check(const char* word)
{
	/* parse word from input to new char composed of all lower case */
    unsigned int len = strlen(word);
    char* newword = malloc(sizeof(char) * len + sizeof(char));
    for (int i = 0; i <= len; i++)
    {
        newword[i] = tolower(word[i]);
    }   
    
    /* Create a cursor to move throughout the linked list */
    cursor = hashtable[newword[0] - 97];
    while (cursor->next != NULL)
    {
    	/* Compare the words, free the memory, signal found */
        if(strcmp(newword, cursor->word) == 0)
        {
        	free(newword);
            return true;
        }
        /* Signal not found early if passed all possible locations, free the memory */
        if(cursor->word[1] > newword[1])
        {
        	free(newword);
        	return false;
        }
        cursor = cursor->next;
    }
    /* Free the word, signal not found */
    free(newword);
    return false;
}
/** Loads dictionary into memory.  Returns true if successful else false. **/
bool load(const char* dictionary)
{
	/* Open up dictionary file, signal false if error */
     FILE* dict = fopen(dictionary, "r");
     if (dict == NULL)
     {
        return false;
     }
     
     /* Initialize all 26 nodes in the hashtable, set as last node on list */
     for(int j = 0; j < HASH; j++)
     {
        hashtable[j] = (struct node*) malloc(sizeof(node));
        hashtable[j]->next = NULL;
     }
     
     cursor = (struct node*) malloc(sizeof(node));
     while(fgets(cursor->word, LENGTH+1,dict) != NULL)
     {
     	/* Find the first letter of the current word */
        int  i = (cursor->word[0]) - 97;
        /* If current list is empty, append cursor to list */
        if(hashtable[i]->next == NULL)
        { 
       		hashtable[i]->next = cursor; 
       		data = (struct node*) malloc(sizeof(node));
        	if (data == 0) {return false;}
        	/* tracker node to remember place in memory of first node (for freeing) */
        	tracker[i] = data;
        }
        
        /* Remove the '\n' newline char automatically added by fscanf */
        strtok(cursor->word, "\n");
        
        /* Assign data cursor's place, create next place on list, do some error **
        **  checking, assign cursor the next place, set cursor as end of list  **/
        data = cursor;
        data->next = (struct node*) malloc(sizeof(node));
        if (data->next == 0) {printf("Out of memory\n");}
        cursor = data->next;
        cursor->next = NULL;
        
        /* Increment a counter to keep track of words loaded into memory */
        words_loaded++;
     }
     fclose(dict);
     return true;
}

/** Returns number of words in dictionary if loaded else 0 if not yet loaded. **/
unsigned int size(void)
{
    return words_loaded;
}

/** Unloads dictionary from memory.  Returns true if successful else false. **/
 
bool unload(void)
{
	/* Iterates through all 26 lists freeing memory, frees original nodes, frees all */
    for (int k = 0; k < HASH; k++)
    {
    	node* iterator = hashtable[k];
    	node* temp;
    	while(iterator != NULL)
    	{
    		temp = iterator;
    		iterator = iterator->next;
    		free(temp);
    	}
    	free(tracker[k]);
    }
    free(cursor);
    return true;
}
