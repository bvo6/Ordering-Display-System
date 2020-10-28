/*Bao Vo
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orderList_bvo6_207.h"

// Create a robot structure that holds different data for a robot.
typedef struct _robotOrder
{
   unsigned char robotNum;
   orderList *data;
   char *deliverTo;
   char *restaurant;
   struct _robotOrder *next;
} robotOrder;

/* This function is used to insert a robot to its head,
* has 2 parameter, the head of the robot and the current robot (to be inserted) to the head.
*/
void insertRobot(robotOrder *head, robotOrder *robot)
{
    /* Assign the next robotNode of the current robot to the next RobotNode of the head.
    * Then, Assign the next robotNode of the head to the current robot (to be inserted).
    */
    robot->next = head->next;
    head->next = robot;
}
/* This function is used to prompt the user if they want to place a new delivery order.
 Return 0 for no, return 1 for yes.*/
int getOrder()
{
    char answer[10];
    char ans;
    int choice = 3;
    while (choice == 3)
    {
        printf("New delivery order? (y/n) ");
        fgets(answer, 10, stdin);
        sscanf(answer, "%c", &ans);
        if (ans == 'y' || ans == 'Y')
        {
            choice = 1;
        }
        else if (ans == 'n' || ans == 'N')
        {
            choice = 0;
        }
        else
        {
            printf("Invalid input. Try again\n");
            choice = 3;
        }
    }
    return choice;
}
/* This function is used to print the list of order. Has 1 parameter which is the head of robotOrder.
*/
void printOrder(robotOrder *head)
{
    // Create a temp rebotOrder and set it to the next Robot.
    robotOrder *temp = head->next;
    printf("\nList of deliveries:\n\n");
    // Print until the last robotNode.
    while (temp != NULL)
    {
        printf("Robot: #%d\n", temp->robotNum);
        printf("Delivery order from %s\n", temp->restaurant);
        printf("Contains %d food item(s).\n", temp->data->count);
        // Create a temp foodNode to print out each foodNode in the orderList.
        foodNode *tempFood = temp->data->head->next;
        while(tempFood != NULL)
        {
            printf("\t%s",tempFood->data);
            tempFood = tempFood->next;
        }
        printf("Deliver to: %s\n", temp->deliverTo);
        printf("\n");
        temp = temp->next;
    }
}
/* This function is used to free the memory of robotOrder. Has 1 parameter which is the double pointers of the robotOrder head.
*/
void freeRobot(robotOrder **head)
{
    // Create a temp robotOrder and set it to the head.
    robotOrder *temp = *head;
    while (temp != NULL)
    {
        // Set head to the next robotNode.
        *head = temp->next;
        // Create a temp foodNode and set it the the current foodNode of the temp robot.
        foodNode *tempOrder = temp->data->head;
        while (tempOrder != NULL)
        {
            // Set the current foodNode of the temp robot to the next foodNode.
            temp->data->head = tempOrder->next;
            // Free the tempOrder foodNode that was set to the foodNode of the temp robot.
            free(tempOrder->data);
            // Set the tempOrder foodNode to the foodNode of the tempRobot.
            tempOrder = temp->data->head;
            // It will run until the tempOrder foodNode becomes NULL.
        }
        //Free the tempOrder foodNode.
        free(tempOrder);
        // Free the temp robotNode data.
        free(temp->data);
        // Free the temp robotNode deliverTo address.
        free(temp->deliverTo);
        // Free the temp robotNode restaurant address.
        free(temp->restaurant);
        // Set the temp robotNode to the head which was set to the next node above.
        temp = *head;
        // Run until the temp robotNode becomes NULL.
    }
    /* Comments: Above is my attempt trying to free the memory, I assume it would work like I explained, but I still do not know why
    it would not free the memory as I expected after I tested it with valgrind.
    */
}

int main()
{
    /* Create variables to hold data for the order.
    * Allocate the memory for the robotOrder and named it head.
    */
    int choice = 0;
    robotOrder *head = dmalloc(sizeof(robotOrder));
    char buffer[100];
    char getNum[10];
    int robotNumber;
    choice = getOrder();
    // Assign choice to the function getOrder to get answer from user (return 0 for no, 1 for yes).
    while (choice != 0)
    {
        // Create a robotOrder and allocate the memory for it, named it robot.
        robotOrder *robot = dmalloc(sizeof(robotOrder));
        printf("Task Robot Number:\n");
        // Get a task robot number and assign it to robotNumber.
        fgets(getNum, 10, stdin);
        // Using sscanf to set the robotNumber.
        sscanf(getNum, "%d", &robotNumber);
        // Then assign the robotNum, by casting (unsigned char) from the robotNumber.
        robot->robotNum = (unsigned char) robotNumber;
        printf("Delivery Address for new delivery order: \n");
        // Prompt the user for the delivery address and pass it to buffer.
        fgets(buffer, 100, stdin);
        // Allocate the memory for the rebot (deliveryTo) with the size of length of buffer + 1 (including the null terminator).
        robot->deliverTo = dmalloc(strlen(buffer) + 1);
        // Copy the data from buffer to robot->deliverTo using strcpy.
        strcpy(robot->deliverTo, buffer);
        // After copying the address, I use memset to empty the buffer (set it to '\0').
        memset(buffer, '\0', sizeof(buffer));
        // Same as above.
        printf("Restaurant from which to pick up food:\n");
        fgets(buffer, 100, stdin);
        robot->restaurant = dmalloc(strlen(buffer) + 1);
        strcpy(robot->restaurant, buffer);
        memset(buffer, '\0', sizeof(buffer));
        memset(getNum, '\0', sizeof(getNum));
        /* Create a orderList named newList and allocating the memory for it by calling the function createItem()
         which will return a pointer of an orderList with its initialized data. */
        orderList *newList = createItem();
        // Create an int stop to run the while loop until stop get modified to 1.
        int stop = 0;
        /* Create a char pointer to hold the foodItem from the user's prompt by calling the function getFood()
        which will return a char pointer to an char array that holds the foodItem*/
        // It will return Null if the user enter a blank response.
        char *food;
        while(stop != 1)
        {
            food = getFood();
            // Check if food = NULL which is a blank response from the user's input.
            if (food == NULL)
            {
                // if yes, set stop to 1 and break out of the loop.
                stop = 1;
                break;
            }
            // otherwise, insert the foodItem to the orderList newList by calling the insert function.
            insert(food, newList);
        }
        // Set the next robotNode to NULL and then set the current robotNode data to the orderList after inserting the foodNode
        robot->next = NULL;
        robot->data = newList;
        // Insert the current robotNode to the headRobot by calling the insertRobot function
        insertRobot(head, robot);
        // call the getOrder function until the user enter 'n' which will return 0 and exit the while loop.
        choice = getOrder();
    }
    if (choice == 0)
    {
        // Check if choice = 0 then print out the robotOrder.
        printOrder(head);
    }
    freeRobot(&head);
    return 0;
}
