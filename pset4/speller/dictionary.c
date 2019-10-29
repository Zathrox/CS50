// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26
int counter = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Declaring Functions
node *insert(node *head, char *word);
node *create(const char *word);
void destroy(node *head);
bool find(node *head, const char *word);

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

void printDict(const struct node *list, const char *comment)
{
    if (list == NULL)
    {
        printf("%s is NULL\n", comment);
    }
    else
    {
        printf("%s: word:%s address:%p nextInLine:%p\n", comment, list->word, list, list->next);
    }

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

        node *list = create(word);
        //printDict(list, "test");

        int hashed = hash(list->word); // should return value of hashed text document word
        if (hashtable[hashed] == NULL)
        {
            hashtable[hashed] = list; //puts first entry into array
        }
        else
        {

            hashtable[hashed] = insert(hashtable[hashed], word); //else add it to start via insertion
            free(list);
        }
        size();
        //free(list);
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter++;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hashed = hash(word); // should return value of hashed text document word
    bool check = find(hashtable[hashed], word);
    return check;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        destroy(hashtable[i]);

    }
    return true;
}


bool find(node *head, const char *word)
{
    //create a traversal pointer pointing to the head
    //while(travelpointer != null)
    //{
    //  travelpointer = head->next;
    //  return false;
    //}
    node *ptr = head;
    int count = 0;
    while (ptr != NULL)
    {
        int result = strcasecmp(ptr->word, word);
        if (result == 0)
        {
            //printf("Successful Match: %s:%s\n", ptr->word, word);
            return true;
        }
        else
        {
            //printf("Failed Match: %s:%s\n", ptr->word, word);
            ptr = ptr->next;
        }
    }

    return false;
}

node *create(const char *word)
{

    //Dynamtically allocate space for new node
    //check if we ran out of memory
    //initalise the nodes value field
    //initialise the nodes next field - list->next = newlist;
    //      if first entry, set to null
    //      else set to next
    //return pointer

    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        //destroy(new_node);
        free(new_node);
    }
    strcpy(new_node->word, word);
    new_node->next = NULL;
    return new_node;
}

//insert function
node *insert(node *head, char *word)
{
    //Dynamically ALlocate space fore new node
    // check if it runs out of memory
    // populate and insert node at beginning of list
    // return pointer to new head of list
    // so make new node -> old head

    node *new_node = create(word);  // creating a brand new node
    new_node->next = head;          // pointing new node to the list(head)
    //printDict(new_node, "insert");
    //head = new_node;                // sets (head)list to new node, adding it to the beginning


    return new_node;
}



void destroy(node *head)
{
    node *cursor = head;

    while (cursor != NULL)
    {
        //delete list
        //destroy(cursor->next);
        node *temp = cursor;
        cursor = cursor->next;
        free(temp);

    }
    free(cursor);
}
