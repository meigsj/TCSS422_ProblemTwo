#include <stdlib.h>
#include <stdio.h>
#include "fifo.h"
#include "pcb.h"

//Create two lists: one will temporary hold the process that are awaiting to put into the ready queue, second will hold 
// the process that are awaiting to deallocate

// TO DO items: 0 - 9


void randomCreatePCB(FIFOq_p target_List);

unsigned int SysStack;

int main(void) {

	// Create function that will create random number of processes, 
	// between 0 and 5 and puts them in the list  
	FIFOq_p process_List = q_constructor();
	FIFOq_p deallocate_List = q_constructor();
	

	// Scheduler transfers created processes into ready queue
	FIFOq_p ready_Queue = q_constructor();
	//----------Main Loop---------
	// while(1) {
	printf("%s",	FIFO_to_string(process_List));
	
	randomCreatePCB(process_List);
	int i, temp;
	temp = getQueueSize(process_List);

	for (i = 0; i < temp; i++) {
		Node_p newNode = (Node_p)malloc( sizeof(Node_s) );
		newNode->pcb = q_dequeue(process_List);
		newNode->next_node = NULL;
		q_enqueue(ready_Queue, newNode);
	}

	// Dispatcher dequeue the process and pull into running state 
	// Similuate the running of the current process 
	// Add PC value to the PCB 
	// Increment the random number between 3000 and 4000 
	PCB_p current_Running_p = q_dequeue(ready_Queue);
	current_Running_p->state = running;
	unsigned int randomPCValue = (rand() % 1001) + 3000;
	current_Running_p->context->pc = randomPCValue; 
 
	// ISR puts process into interrupt state and pseudo-push into system stack
	SysStack = current_Running_p->context->pc;
	current_Running_p->state = interrupted;

	// Pseudo-ISR calls the scheduler, denotes that it's a timer interrupt 
	// (maybe create function for scheduler)
	current_Running_p->state = ready;
	Node_p updateNode = (Node_p)malloc( sizeof(Node_s) );
	updateNode->pcb = current_Running_p;
	updateNode->next_node = NULL;
	q_enqueue(ready_Queue, updateNode);

	// Dequeue the next waiting process, change its state to running, 
	// and copy its PCB->PC to SysStack
	PCB_p next_Running_p = q_dequeue(ready_Queue);
	next_Running_p->state = running;
	randomPCValue = (rand() % 1001) + 3000;
	next_Running_p->context->pc = randomPCValue; 
	SysStack = current_Running_p->context->pc;

	if (temp > 30) {
		break;
	}
	//printf("%s\n", pcb_to_string(current_Running_p));
	// 
	//printf("%s",	FIFO_to_string(ready_Queue));
	// }

	return 0;
}

void randomCreatePCB(FIFOq_p target_List) {

	int ra, i;
	// Need to double check for automatically generate number 0 - 5 
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

