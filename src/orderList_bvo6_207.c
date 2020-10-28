/*Bao Vo
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orderList_bvo6_207.h"

/* This function is used to create an orderList and initialize all its data variables
* return a pointer to the allocated orderList.
*/
orderList *createItem()
{
    orderList *newList = dmalloc(sizeof(orderList));
    newList->head = dmalloc(sizeof(foodNode));
    newList->head->next = NULL;
    newList->count = 0;
    return newList;
}
/* This function is used to get the foodItem from the user's input
* return a pointer to a allocated char array if the user enter an appropriate input (beside a blank response).
*/
char *getFood()
{
    char *food = NULL;
    char buffer[100];
    printf("Food Item:\n");
    fgets(buffer, 100, stdin);
    if (buffer[0] != '\n')
    {
        // Check if the input is not a blank response (which contains a new line)
        // Then allocate memory for food with the size of the length of buffer + 1 including a null terminator.
        food = dmalloc(strlen(buffer) + 1);
        // Copy values from buffer to food.
        strcpy(food, buffer);
    }
    return food;
}

/* This function is used to insert a foodNode to the orderList
* has 2 parameter, the foodItem name and the orderList.
*/
int insert(char *str, orderList *s)
{
    // Create a temp foodNode and allocate its memory
    foodNode *newNode = dmalloc(sizeof(foodNode));
    // Then set its data to str.
    newNode->data = str;
    // Set the next foodNode of temp foodNode to the next foodNode of the orderList
    newNode->next = s->head->next;
    // Then set the next foodNode of the orderList to the temp foodNode that was created
    s->head->next = newNode;
    // Increment count for each insertion.
    s->count++;
    return 0;
}

/* allocates memory with a check for successful allocation */
void *dmalloc(size_t size)
{
   void *p = malloc(size);
   if (!p)
   {
      printf("memory allocation failed\n");
      exit(1);
   }
   return p;
}




