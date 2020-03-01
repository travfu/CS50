// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Prototype
bool strcmp_ci(const char *str1, const char *str2);

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // TODO

        // malloc new node and store keep address
        node *ptr = malloc(sizeof(node));
        ptr->next = NULL;

        // store word in new node
        strcpy(ptr->word, word);

        // hash word
        int h = hash(&word[0]);

        // insert node into appropriate hashtable index
        if (hashtable[h] != NULL)
        {
            // if linked list exists, insert new node at beginning of linked list
            ptr->next = hashtable[h];
            hashtable[h] = ptr;
        }
        else
        {
            // if no linked list, point to new node
            hashtable[h] = ptr;
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    // initalise counter
    int counter = 0;

    // iterate over each bucket in hashtable
    for (int i = 0; i < N; i++)
    {
        // check if current hashtable index points to a linked list
        if (hashtable[i] != NULL)
        {
            node *ptr = hashtable[i];

            // iterate over each node in linked list
            while (1)
            {
                counter++;

                if (ptr->next != NULL)
                {
                    ptr = ptr->next;
                }
                else
                {
                    break;
                }
            }

        }
    }


    if (counter > 0)
    {
        // if loaded, return counter
        return counter;
    }
    else
        // if unloaded, 0
    {
        return 0;

    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    // hash word to determine correct bucket
    int h = hash(&word[0]);

    // check if current bucket points to a linked list
    if (hashtable[h] != NULL)
    {
        // initialise pointer to search linked list
        node *ptr = hashtable[h];

        // iterate over each node in linked list
        while (1)
        {
            if (strcasecmp(word, ptr->word) == 0)
            {
                // word found
                return true;
            }
            else
            {
                if (ptr->next != NULL)
                {
                    // word not found in current node, move to next node
                    ptr = ptr->next;
                }
                else
                {
                    // word not found
                    return false;
                }
            }
        }
    }
    else
    {
        // no linked list, therfore, no word
        return false;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO

    // iterate over each bucket in hashtable
    for (int i = 0; i < N; i++)
    {
        if (hashtable[i] == NULL)
        {
            // if bucket is empty, do nothing
            continue;
        }
        else
        {
            // unlink linked list from hashtable
            node *ptr1 = hashtable[i];
            hashtable[i] = NULL;

            // iterate over each node in linked list
            while (1)
            {
                if (ptr1->next == NULL)
                {
                    free(ptr1);
                    break;
                }
                else
                {
                    node *ptr2 = ptr1;
                    ptr1 = ptr1->next;
                    free(ptr2);
                }
            }
        }
    }

    return true;
}