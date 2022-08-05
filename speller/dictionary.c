// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
unsigned int wordCount;
unsigned int hashValue;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    hashValue = hash(word);
    node *cursor = table[hashValue];

    while (cursor != 0)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open
    FILE *file = fopen(dictionary, "r");


    if (file == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }
    // variable word
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        // alocate memory
        node *nod = malloc(sizeof(node));

        if (nod == NULL)
        {
            return false;
        }
        strcpy(nod->word, word);
        hashValue = hash(word);
        nod->next = table[hashValue];
        table[hashValue] = nod;
        wordCount++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (wordCount > 0)
    {
        return wordCount;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through buckets
    for (int i = 0; i < N; i++)
    {
        // Set cursor to this each bucket location
        node *cursor = table[i];
        // If cursor is not NULL, free
        while (cursor != NULL)
        {
            // Create temp
            node *tmp = cursor;
            // Move cursor to next node
            cursor = cursor->next;
            // Free up templs
            free(tmp);
        }
        // If cursor is NULL
        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
