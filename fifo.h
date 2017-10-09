/*
TCSS422 
Problem #1
Group Members: 
Joshua Meigs
Yaroslav Salo
*/
#ifndef FIFO
#define FIFO
#include "pcb.h"
/* 
* The Node_p for the Queue that contains the PCB_p object and a link to the next Node_p in the list.
*/ 
typedef struct node{
    PCB_p pcb;
    unsigned int node_number;
    struct node *next_node;
}Node_s;
typedef Node_s* Node_p;

/* 
* The Queue that contains a Node_p object and a parameter for the size of the queue.
*/ 
typedef struct FIFO_s {
    Node_p  my_node;
    unsigned int size;
}FIFO_s;
typedef struct FIFO_s *FIFOq_p;

/*
A function that does a check on the given queue to see if it is empty. It will return a zero for success, or an error number of 1 for failure. 
*/ 
int q_is_empty(FIFOq_p);
/*
* A function that pushes the given Node_p into the Given Queue. It will return a zero for success, or an error number of 1 for failure. 
*/
int q_enqueue(FIFOq_p, Node_p);

/*
A function that pops off the given pcb from the queue and returns the said pcb to the caller. 
*/
PCB_p q_dequeue(FIFOq_p);

/*
A function that creates a Queue and returns the newly constructed Queue.
*/
FIFOq_p q_constructor();

/*
 A function that frees the given Queue from memory. It will return a zero for success, or an error number of 1 for failure. 
*/
int q_deconstructor(FIFOq_p);

/*
A Function that returns a string representation of the given Queue
*/
char* FIFO_to_string(FIFOq_p);
#endif