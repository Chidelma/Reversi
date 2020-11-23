#include "table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------


typedef struct NODE Node;

struct NODE{
    char *item;
    Node *next;
};

struct TABLE
{
   Node *start;
   Node *traverseNode;

   int numNodes;
   int numTraversals;
};

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// Linked List Implementation
//-------------------------------------------------------------------------------------

void validateTable(Table *table)
{
	  assert(table);
      if ( table->numNodes == 0 )
          assert( table->start == NULL );
      else if ( table->numNodes == 1 )
          assert( table->start->next == NULL );
      else // num_nodes > 1
          assert( table->start != NULL && table->start->next != NULL );
}

Table *createTable()
{
	Table *table = malloc(sizeof(Table));

    if(table)
    {
    	table->start = NULL;
        table->traverseNode = NULL;
        table->numNodes = 0;
        table->numTraversals = 0;
    }
    return table;
}

// add an element to the beginning of the linked list
Boolean insert( Table *table, char *newString ){

    Boolean rc = false;
    Node *newNode = NULL;
    Node *prevNode = NULL;
    Node *currNode;

    validateTable(table);
    assert( newString != NULL );

    if ( newString )
    {
        newNode = (Node *)malloc( sizeof( Node ) );
        assert( newNode != NULL );

        if ( newNode )
        {
            // note that we need to have space for the string as well!
            newNode->item = newString;

            currNode = table->start;

            assert(currNode == NULL || currNode->item != NULL);

            while(currNode != NULL)
            {
            	prevNode = currNode;
                currNode = currNode->next;
            }

            if(prevNode == NULL)
            {
            	newNode->next = table->start;
                table->start = newNode;
            }
            else
            {
            	newNode->next = prevNode->next;
                prevNode->next = newNode;
            }

            table->numNodes++;

            rc  = true;

            validateTable(table);
        }// if( newNode )

    }// if( newString )

    return rc;
}// insert


// tells us whether or not the given string is in the list
Boolean search( Table *table, char *target )
{
    Boolean found = false;
    Node *curr;
    int search_count = 0;

    validateTable(table);

    assert(target != NULL);
    if(target != NULL)
    {
        curr = table->start;

        while(curr != NULL && !found)
        {
            assert(curr->item != NULL);
            if(strcmp(target, curr->item) == 0)
            {
                found = true;
                assert(search_count <= table->numNodes);
            }
            else
            {
                curr = curr->next;
                search_count++;
            }
        }
    }
    assert(found || (search_count == table->numNodes));
    return found;
}// search


// starts a list traversal by getting the data at start
char * firstItem(Table *table)
{
    char *the_item = NULL;

    validateTable(table);

    if ( table->start != NULL )
    {
        table->traverseNode = table->start->next;
        the_item = table->start->item;
        assert( the_item != NULL );

        table->numTraversals = 1;
        // make sure we're still in our list...
        assert( table->numTraversals <= table->numNodes );
    }// if

    // this isn't the safest (caller can modify the string),
    // but we don't have to worry about extra memory mgmt...
    return the_item;
}// firstItem

// increment the traversal and get the item at the current traversal node
char * nextItem(Table *table)
{
    char *the_item = NULL;

    // try to advance the traversal first
    if ( table->traverseNode != NULL )
    {
        the_item = table->traverseNode->item;
        assert(the_item != NULL);
        table->traverseNode = table->traverseNode->next;
        table->traverseNode++;
        assert(table->numTraversals <= table->numNodes);
    }
    // this isn't the safest (caller can modify the string),
    // but we don't have to worry about extra memory mgmt...
    return the_item;
}// nextItem

void clearTable(Table *table)
{
	Node *curr;

    validateTable(table);

    curr = table->start;

    while( table->start != NULL )
    {
    	table->start = table->start->next;

        assert(curr);
        free(curr);

        curr = table->start;

        table->numNodes--;
    }

    validateTable(table);
}


Boolean delete(Table *table, char *target)
{
    Boolean found = false;
    Node *curr;
    Node *prev = NULL;

    int search_count = table->numNodes;
    validateTable(table);

    assert(NULL != target);
    if ( NULL != target )
    {
    	curr = table->start;

        assert((curr == NULL) || (curr->item != NULL));

        while ( curr != NULL && strcmp(target, curr->item) != 0)
        {
            prev = curr;
            curr = curr->next;
            assert(curr != NULL || curr->item != NULL);
        }

        if( curr != NULL )
        {
        	if(prev != NULL)
            {
            	prev->next = curr->next;
            }
            else
            {
            	table->start = curr->next;
            }

            found = true;
            free(curr);
            table->numNodes--;

            validateTable(table);
        }
    }
    assert( !found || search_count > table->numNodes);

    return found;
}

void destroyTable(Table *table)
{
	clearTable(table);

    free(table);
}

int lengthTable(Table *table)
{
	validateTable(table);

    return table->numNodes;
}
