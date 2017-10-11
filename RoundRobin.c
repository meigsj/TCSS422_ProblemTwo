#include <stdlib.h>
#include <stdio.h>
#include "fifo.h"
#include "pcb.h"

//Create two lists: one will temporary hold the process that are awaiting to put into the ready queue, second will hold 
// the process that are awaiting to deallocate

// TO DO items: 0 - 9


void randomCreatePCB(FIFOq_p target_List);

int main(void) {

	// Create function that will create random number of processes, 
	// between 0 and 5 and puts them in the list  
	FIFOq_p process_List = q_constructor();
	FIFOq_p deallocate_List = q_constructor();
	randomCreatePCB(process_List);

	//printf("%s",	pcb_to_string(process_List->my_node->pcb));


	//----------Main Loop---------
	// while(1) {
	printf("%s",	FIFO_to_string(process_List));
	// Item 1: Scheduler transfers created processes into ready queue
	FIFOq_p ready_Queue = q_constructor();
	int i, temp;
	temp = getQueueSize(process_List);

	for (i = 0; i < temp; i++) {
		Node_p newNode = (Node_p)malloc( sizeof(Node_s) );
		newNode->pcb = q_dequeue(process_List);
		newNode->next_node = NULL;
		q_enqueue(ready_Queue, newNode);
	}

	printf("%s",	FIFO_to_string(ready_Queue));
	// }
	// Similuate the running of the current process 
		// Add PC value to the PCB 
		// Increment the random number between 3000 and 4000 

	return 0;
}

void randomCreatePCB(FIFOq_p target_List) {

	int ra, i;
	// Need to be fix for automatically generate number 0 - 5 
	// Currently only 3 
	ra = (rand() % 5) + 1;
	for (i = 0; i < ra; i++) {
		Node_p newNode = (Node_p)malloc( sizeof(Node_s) );
		newNode->pcb = pcb_constructor();
		pcb_init(newNode->pcb);
		newNode->next_node = NULL;
		q_enqueue(target_List, newNode);
	}
} 

