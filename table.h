#ifndef _TABLE_H
#define _TABLE_H

typedef enum { false, true } Boolean;

typedef struct TABLE Table;

// add an element to the beginning of the linked list
Boolean insert( Table *table, char *newString );

void validateTable(Table *table);

Table *createTable();

// tells us whether or not the given string is in the list
Boolean search( Table *table, char *target );

// starts a list traversal by getting the data at top
char * firstItem(Table *table);

// increment the traversal and get the data at the current traversal node
char * nextItem(Table *table);

void destroyTable(Table *table);

Boolean delete(Table *table, char *target);

void clearTable(Table *table);

int lengthTable(Table *table);

#endif