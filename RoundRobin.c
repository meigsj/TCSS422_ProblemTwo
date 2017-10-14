#include <stdlib.h>
#include <stdio.h>
#include "fifo.h"
#include "pcb.h"

enum interrupt_type {timer, iorequest};
/*
* Randomly generate processes from 0 - 5
*/
void randomCreatePCB(FIFOq_p target_List);

/*
* The scheduler will check whether the process list contains any process 
* and enqueue all the processes into the ready queue 
*/
void scheduler(FIFOq_p processList, FIFOq_p readyQueue);

/*
* Scheduler will determine which type of interrupt and decide how to handle
*/
void scheduler1(enum interrupt_type interruptType, FIFOq_p readyQueue, PCB_p currentRunningP);

/*
* Dispatcher dequeue the process and pull into running state 
*/
PCB_p dispatcher(FIFOq_p readyQueue, unsigned int pcValue);

// Pseudo-stack
unsigned int SysStack;
// Possible interrupt type 


int main(void) {

	/*
	* Create function that will create random number of processes, 
	* between 0 and 5 and puts them in the list  
	*/ 
	FIFOq_p process_List = q_constructor();
	FIFOq_p deallocate_List = q_constructor();
	
	FIFOq_p ready_Queue = q_constructor();

	// PCB for pseudo-CPU
	PCB_p CPU_p = pcb_constructor();
	pcb_init(CPU_p);
	cpu_context_init(CPU_p->context);

	int counter = 0; 

	//----------Main Loop---------
	 while(1) {
	 	randomCreatePCB(process_List);
	 	/*
	 	 * Call scheduler to check if the process_List contains any process 
	 	 * and enqueue process into ready queue
	 	 */ 
	 	scheduler(process_List, ready_Queue); 

	 	/*
	 	* Simulate running of the process
	 	* Increment PC value with the random number between 3000 and 4000 
	 	*/
	 	unsigned int current_CPU_pc = get_pc(CPU_p);
	 	unsigned int randomPCValue = (rand() % 1001) + 3000;
	 	current_CPU_pc += randomPCValue;
	 	set_pc(CPU_p, current_CPU_pc);

	 	// Call dispatcher 
		PCB_p running_Process_p = dispatcher(ready_Queue, get_pc(CPU_p));

		// ISR and do a pseudo-push of the PC to system stack
		SysStack = get_pc(running_Process_p);
		pcb_set_state(running_Process_p, interrupted);

		counter += 2;
		//PCB_p currProcess = q_top(ready_Queue);
		if (counter % 4 == 0) {
			printf("Switching to: \n");
			printf("%s\n", FIFO_to_string(ready_Queue));
		} 

		scheduler1(timer, ready_Queue, running_Process_p);
		PCB_p next_Process_p = dispatcher(ready_Queue, get_pc(next_Process_p));
		
		if (counter % 4 == 0) {
			//printf("%s\n", pcb_to_string(currProcess));
			printf("%s\n", pcb_to_string(next_Process_p));
			printf("%s\n", FIFO_to_string(ready_Queue));
			counter = 0;
		} 

		SysStack = get_pc(next_Process_p);
		set_pc(CPU_p, SysStack);

		int temp = getQueueSize(ready_Queue);
		// Terminated when the number of processes exceed 30 
		if (temp > 30) {
			break;
		}
	}

	return 0;
}

void randomCreatePCB(FIFOq_p target_List) {

	int ra, i;
	ra = (rand() % 6);
	for (i = 0; i < ra; i++) {
		Node_p newNode = (Node_p)malloc( sizeof(Node_s) );
		newNode->pcb = pcb_constructor();
		pcb_init(newNode->pcb);
		cpu_context_init(newNode->pcb->context);
		newNode->next_node = NULL;
		q_enqueue(target_List, newNode);
	}
} 

void scheduler(FIFOq_p processList, FIFOq_p readyQueue) {

	int i, temp;
	temp = getQueueSize(processList);
	if (temp > 0) {
		for (i = 0; i < temp; i++) {
			Node_p newNode = (Node_p)malloc( sizeof(Node_s) );
			newNode->pcb = q_dequeue(processList);
			newNode->next_node = NULL;
			pcb_set_state(newNode->pcb, ready);
			q_enqueue(readyQueue, newNode);
		//	printf("....Enqueue.... PCB: \n%s\n", pcb_to_string(newNode->pcb));
		}
	}
}

void scheduler1(enum interrupt_type interruptType, FIFOq_p readyQueue, PCB_p currentRunningP) {

	if (interruptType == timer) {
		pcb_set_state(currentRunningP, ready);
		Node_p newNode = (Node_p)malloc( sizeof(Node_s) );
		newNode->pcb = currentRunningP;
		newNode->next_node = NULL;
		q_enqueue(readyQueue, newNode);
	}
}

PCB_p dispatcher(FIFOq_p readyQueue, unsigned int pcValue) {

	PCB_p current_Running_p = q_dequeue(readyQueue);
	set_pc(current_Running_p, pcValue);
	pcb_set_state(current_Running_p, running);
	return current_Running_p;

} 


