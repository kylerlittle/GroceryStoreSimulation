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

#include "grocery_store.h"

Boolean isEmpty(Queue Q)
{
	Boolean is_empty = FALSE;
	if (Q.pHead == NULL)
	{
		is_empty = TRUE;
	}
	return is_empty;
}

QueueNode *makeNode(int custNum, int servTime, int totTime)
{
	QueueNode *pMem = NULL;

	pMem = (QueueNode *)malloc(sizeof(QueueNode));
	if (pMem != NULL)  //memory successfully allocated
	{
		pMem->customerNumber = custNum;
		pMem->serviceTime = servTime;
		pMem->totalTime = totTime;
		pMem->pNext = NULL;
	}
	return pMem;
}

void enqueue(Queue *pQ, int custNum, int servTime, int totTime)
{
	QueueNode *pMem = makeNode(custNum, servTime, totTime);

	if (pMem != NULL)  // successfully allocated memory on the heap
	{
		if (pQ->pHead == NULL) // queue is empty
		{
			pQ->pHead = pMem;
		}
		else  // queue is not empty; connect current tail pointer's pNext to pMem
		{
			pQ->pTail->pNext = pMem;
		}
		pQ->pTail = pMem;
	}
	else
	{
		printf("Error: Computer was not able to allocate memory on the heap.\n");
	}
}

QueueNode dequeue(Queue *pQueue)
{
	QueueNode store = { 0,0,0, NULL }, *pTemp = pQueue->pHead;
	
	// Store data
	store.customerNumber = pTemp->customerNumber;
	store.serviceTime = pTemp->serviceTime;
	store.totalTime = pTemp->totalTime;
	store.pNext = pTemp->pNext;

	pQueue->pHead = pQueue->pHead->pNext;
	if (pQueue->pHead == NULL)  // Queue is now empty
	{
		pQueue->pTail = NULL;  // Update the tail
	}
	free(pTemp);

	return store;
}

void printDeNode(QueueNode Q, Line line)
{
	printf("\nThe following customer has left:\n");
	printf("CUSTOMER #%d\n", Q.customerNumber);
	if (line == EXPRESS)
	{
		printf("LINE: Express\n");
	}
	else
	{
		printf("Line: Normal\n");
	}
	printf("Time Spent in Line: %d minutes\n\n", Q.totalTime);
}

void printEnNode(Line line, int n, int custNum)
{
	printf("\nA customer has arrived! Details below:\n");
	printf("CUSTOMER #%d\n", custNum);
	if (line == EXPRESS)
	{
		printf("LINE: Express\n");
	}
	else
	{
		printf("Line: Normal\n");
	}
	printf("Arrival Time: %d minutes\n\n", n);
}

void printQueueRecursive(QueueNode *pHead)
{
	if (pHead != NULL)  // while not at the end of the list
	{
		printf("Cust. #%d\n", pHead->customerNumber);
		printf("Service Time: %d minutes\t\t Total Time at Checkout: %d minutes\n", 
			pHead->serviceTime, pHead->totalTime);
		printQueueRecursive(pHead->pNext);
	}
	else   // base case because we're at the end of the list
	{
		return;
	}
}