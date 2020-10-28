/*Bao Vo
 */
#ifndef ORDERLIST
#define ORDERLIST
typedef struct _foodNode
{
   char *data;  // Food Item Name
   struct _foodNode *next;
} foodNode;

typedef struct _orderList
{
   foodNode *head;  // Pointer to first food item for the order (alphabetical)
   int count;   // Number of food items in the order
} orderList;

orderList *createItem();
int insert(char *str, orderList *s);
char *getFood();
void *dmalloc(size_t size);
#endif

