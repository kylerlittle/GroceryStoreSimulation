/*******************************************************************************
* Programmer: Kyler Little													  *
* Class: CptS 122; Lab Section 6                                              *
* Programming Assignment: Grocery Store Simulation (PA #4)                    *
* Date: 2/20/2017                                                             *
*                                                                             *
* Description: This program simulates two lines in a grocery store as two	  *
*			   queues. There are Normal & Express "lines." The arrival and	  *
*			   service times for each customer are randomly generated.		  *
*			   enqueues and dequeues are made as necessary. The simulation	  *
*			   runs for 'n' minutes (inputted by user). Various information	  *
*			   is printed out as the simulation runs.						  *
*                                                                             *
* Relevant Formulas: Refer to each function definition.                       *
*                                                                             *
*																			  *
******************************************************************************/

#ifndef GROCERY_STORE_SIMULATION
#define GROCERY_STORE_SIMULATION

/* Standard Libraries Included */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Macroconstants */
#define MINUTES_IN_DAY 1440

/* Defined Types */
typedef enum boolean
{
	FALSE, TRUE
} Boolean;

typedef enum line
{
	EXPRESS, NORMAL
} Line;

typedef struct queueNode
{
	int customerNumber;		//Unique identifier; starts at 1; after 24 hours should be reset to 1
	int serviceTime;		//Random time; varies between express and normal lanes; units in minutes
	int totalTime;			//TotalTime = serviceTime + sum of serviceTimes of customers in line before this customer; units in minutes
	struct queueNode *pNext;
} QueueNode;

typedef struct queue
{
	QueueNode *pHead;
	QueueNode *pTail;
} Queue;

/* Function Prototypes */

// GROCERY.C FUNCTIONS
void run_app(void);

// Description: Prompts the user for a number of minutes to run the simulation. Gets
//				this value until the value entered is greater than 0.
void getSimulationTime(int *n);

// Description: Generates a random arrival/service time. Arrival time varies, depending on 
//				whether customer enters express or normal line. If in express line, *pTime 
//				will take a random value between 1-5. If normal line, 3-8.
void Time(int *pTime, Line line);

// Description: This function sums of the service times of the queue.
// Precondition: The queue is not empty. There is logic in place to ensure that this
//				 is the case when I use this function in my program.
int sumServ(Queue Q);

// QUEUE.C FUNCTIONS
// Description: If the Queue Q is empty, TRUE is returned. Else, false.
Boolean isEmpty(Queue Q);

// Description: Allocates memory for a QueueNode on the heap. Initializes the node
//				with the data corresponding to input parameters of the function.
QueueNode *makeNode(int custNum, int servTime, int totTime);

// Description: If function is successful (i.e. malloc doesn't fail in makeNode(),
//				then node is actually added. Else, an error message is printed. This 
//				function allocates memory on the heap (using a helper function) and 
//				adds it to the tail of the Queue.
void enqueue(Queue *pQ, int custNum, int servTime, int totTime);

// Description: Returns the data from the front of the Queue; I can do this rather than
//				passing in a pointer to a QueueNode to store the data since I'm only
//				copying integers and not any strings (which would result in me copying
//				the pointer to a freed up location in memory)
// Precondition: Queue is not empty. I already checked for this in another part of my program.
QueueNode dequeue(Queue *pQueue);

// Description: Prints customer details: line the customer is in, his/her customer number, 
//				and the totalTime they spent in line
void printDeNode(QueueNode Q, Line line);

// Description: Prints customer details: line the customer is in, his/her customer number, 
//				and the total time n (overall arrival time).
void printEnNode(Line line, int n, int custNum);

// Description: Algorithm borrowed from Andy's Lecture Slides! Of course it was modified
//				to fit what I'm working with. This function simply prints the entire
//				contents of the queue.
void printQueueRecursive(QueueNode *pHead);


#endif