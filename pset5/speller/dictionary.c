// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>

#include "dictionary.h"

//create a structure of nodes for linked list
typedef struct node
{
    //size of word is 1 greater than length of word because of null character at end
    char word[LENGTH + 1];
    struct node *next;
}
node;

//hash table size
#define table_size 143295
bool load1 = false;
//dictionary_size counts size of words from dictionary loaded
int dictionary_size = 0;
//make a hashtable
node *hashtable[table_size];


//this hash function is taken from http://www.cse.yorku.ca/~oz/hash.html
//creates a unique hash value for each word
unsigned long hash(const char *word)
{
    unsigned int hash = 0;
    int c = 0;

    while (c == *word++)
    {
        hash += c;
    }
    return hash;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //ensure word being checked is lowercase
    //create copy of word and add 1 to ensure comparison with dictionary words works
    char check_word[strlen(word) + 1];
    int length = strlen(word) + 1;

    //convert words to lowercase
    for (int i = 0; i < length; i++)
    {
        check_word[i] = tolower(word[i]);
    }



    int index = hash(check_word);
    node *hash_index = hashtable[index];

    //check if there's anything in hashtable where the hash of check_word points to
    if (hash_index == NULL)
    {
        //no word found
        return false;
    }
    else
    {
        //pt compares with word in dic
        //goes through the linked list at the specific hash node
        for (node *pt = hash_index; pt != NULL; pt = pt->next)
        {
            //compare whole strings
            if ((strcmp(check_word, pt -> word) == 0))
            {
                return true;
            }
        }
    }
    return false;
}
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    //Open dictionary for reading
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "error");
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {

        //allocate memory for node to store the word
        node *new_node = malloc(sizeof(node));

        //checks if new_node points to anything
        if (new_node == NULL)
        {
            unload ();
            return false;
        }

        //copy word from dictionary read into new_node
        strcpy(new_node -> word, word);
        //hash gives unique index for word
        //calls hash function
        int hashindex = hash(word);
        //use hash to find index where word is put
        if (hashtable[hashindex] == NULL)
        {
            hashtable[hashindex] = new_node;
            //incremenet dictionary size
            dictionary_size = dictionary_size + 1;
            //node doesn't point anywhere because it was empty
            new_node -> next = NULL;
        }
        else
        {
            new_node -> next = hashtable[hashindex];
            //newnode inserted points to what hashtable node was pointing to
            hashtable[hashindex] = new_node;
            //incremenet dictionary size
            dictionary_size = dictionary_size + 1;


        }
    }
    load1 = true;
    fclose(file);
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (load1 == true)
    {
        //dictionary_size is global and calculated in load
        return dictionary_size;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false

bool unload(void)
{
    if (load1 == true)
    {

        //goes through each hashtable entry
        for (int j = 0; j < table_size; j++)
        {
            //goes through the linked list in a specific table block
            for (node *cursor = hashtable[j]; cursor != NULL; cursor = cursor -> next)
            {
                node *temp = cursor;
                free(temp);
            }
            return true;
        }
    }
    return false;
}
