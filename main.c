#include <stdio.h>
#include <stdlib.h>
#include "table.h"

static int testsPassed = 0;
static int testsFailed = 0;
static int currentSize = 0;

void testInsert();
void testDelete();
void testEmpty();
void testLeaks();
void viewResults();
void testFound(int size, char *words[]);
void testNotFound(int size, char *words[]);
void testSize();

Table *theTable;


int main( int argc, char *argv[] )
{
	printf("Starting Tests.\n\n");
	
	theTable = createTable();
	
  testEmpty();
  testInsert();
  testDelete();
  testLeaks();
  viewResults();

  
  printf("\nFinished Testing.\n");
  
  return EXIT_SUCCESS;
}

void testEmpty()
{
	char *nothing = "Empty";
  
  Boolean result;
  
  printf("Testing edge cases:\n");
  
  testNotFound( 1, &nothing );
  
  result = delete(theTable, nothing);
  
  if(result)
  {
  	printf("deleted something from empty table\n");
    testsFailed++;
  }
  else
  {
  	printf("Not able to delete from empty table\n");
    testsPassed++;
  }
  
  testSize();
}

void testInsert()
{
	char *insertStrings[4] = {"String1", "String2", "String3", "String4"};
  
  char *testString = "Not Found";
  
  Boolean result;
  
  printf("\nTesting Insert Method:\n\n");
  for(int i = 0; i < 4; i++)
  {
  	result = insert(theTable, insertStrings[i]);
    
    if(result)
    {
    	printf("\"%s\" was inserted into the Table\n", insertStrings[i]);
      testsPassed++;
      currentSize++;
    }
    else
    {
    	printf("\"%s\" was not inserted into the Table\n", insertStrings[i]);
      testsFailed++;
    }
  }
  
  testFound(4, insertStrings);
  testNotFound(1, &testString);
  testSize();
}

void testDelete()
{
	char *removeNodes[2] = {"String1", "String2"};
  char *leftNodes[2] = {"String3", "String4"};
  
  Boolean result;
  
  // Table *theTable = createTable();
  
  printf("\nTesting Delete Method:\n\n");
  for(int i = 0; i < 2; i++)
  {
  	printf("deleting \"%s\"\n", removeNodes[i]);
    result = delete(theTable, removeNodes[i]);
    
    if(result)
    {	
    	printf("\"%s\" was deleted from table\n", removeNodes[i]);
      testsPassed++;
      currentSize--;
    }
    else
    {
    	printf("\"%s\" was not deleted from table\n", removeNodes[i]);
      testsFailed++;
    }
  }
  
  testNotFound(2, removeNodes);
  testFound(2, leftNodes);
  testSize();
}

void testFound(int size, char *strings[])
{
	Boolean result;
  
  printf("\nTesting Search Method in finding elements\n\n");
  
  for(int i = 0; i < size; i++)
  {
  	result = search(theTable, strings[i]);
    
    if(result)
    {
    	printf("\"%s\" was found in Table\n", strings[i]);
      testsPassed++;
    }
    else
    {
    	printf("\"%s\" was not found in Table\n", strings[i]);
      testsFailed++;
    }
  }
}

void testNotFound(int size, char *strings[])
{
	Boolean result;
  
  printf("\nTesting Search Method in not finding elements\n\n");
  
  for(int i = 0; i < size; i++)
  {
  	result = search(theTable, strings[i]);
    
    if(result)
    {
    	printf("\"%s\" was found in Table\n", strings[i]);
      testsFailed++;
    }
    else
    {
    	printf("\"%s\" was not found in Table\n", strings[i]);
      testsPassed++;
    }
  }
}
  
void testSize()
{
  int sizeValue = lengthTable(theTable);
  
  printf("\nTesting size of Table:\n\n");
  if(currentSize == sizeValue)
  {
  	printf("Size of Table is %d, as expected\n", currentSize);
    testsPassed++;
  }
  else
  {
  	printf("Size of table says %d, but there are %d\n", sizeValue, currentSize);
    testsFailed++;
  }
}

void testLeaks()
{
	char *leaks = "ZAPP";
  
  for(int i = 0; i < 1000; i++)
  {
  	insert(theTable, leaks);
    currentSize++;
  }
  
  testFound(1, &leaks);
  testSize();
  
  for(int i = 0; i < 1000; i++)
  {
  	delete(theTable, leaks);
    currentSize--;
  }
  
  testNotFound(1, &leaks);
  testSize();
}

void viewResults()
{
	clearTable(theTable);
  currentSize = 0;
  testSize();
  
  printf("\nTest Results:\n\n");
  printf("%d tests ran.\n", testsPassed + testsFailed);
  printf("%d tests passed.\n", testsPassed);
  printf("%d tests failed.\n", testsFailed);
}