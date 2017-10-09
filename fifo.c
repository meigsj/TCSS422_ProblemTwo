/*
TCSS422 
Problem #1
Group Members: 
Joshua Meigs
Yaroslav Salo
*/
#include "fifo.h"
#define MAX_TEMP_STRING_SIZE 200
int q_is_empty(FIFOq_p the_queue) {
    if (the_queue == NULL) {
        return 1;
    }
    if(the_queue->size == 0) {
        return 0;
    }
    return 1;
}

int q_enqueue(FIFOq_p the_queue, Node_p the_node) {
    //Do Error handling
    if (the_queue == NULL || the_node == NULL) {
        return -1;
    }
    
    Node_p current_node =  (Node_p)malloc( sizeof(Node_s) );
    the_node->node_number = (the_queue->size+1);
    if(the_queue->size > 0) {
        current_node = the_queue->my_node;
        while(current_node->next_node != NULL) {
            current_node = current_node->next_node;
        }
        current_node->next_node = the_node;
        
    } else {
        the_queue->my_node = the_node;
    }
    the_queue->size++;
    
    return 0;
}

PCB_p q_dequeue(FIFOq_p the_queue) {
    if (the_queue == NULL || the_queue->size == 0) {
        return NULL;
    }
    Node_p node_to_pop_back_onto_the_queue = the_queue->my_node->next_node;
    PCB_p pcbToReturn = the_queue->my_node->pcb;
    free(the_queue->my_node);
    
    the_queue->my_node = node_to_pop_back_onto_the_queue;
    the_queue->size--;
    return pcbToReturn;
}

FIFOq_p q_constructor() {
    FIFOq_p the_queue = (FIFOq_p)malloc(sizeof(FIFO_s));
    the_queue->size = 0;
    return the_queue;
}

int q_deconstructor(FIFOq_p the_queue) {
    
    int value_to_return = 1;
    if(the_queue != NULL) {
        free(the_queue);
        value_to_return = 0;
    }
    return value_to_return;
}


char* FIFO_to_string(FIFOq_p the_queue) {
    int the_current_node_number = 0;
    //check the pointer 
    if (the_queue == NULL) {//If Null
        return NULL;
    }
    //allocate temp memory for the context string,
    char * str = (char *) malloc(sizeof(char) * MAX_PCB_LEN);
    
    char * temp = (char *) malloc(sizeof(char) * MAX_TEMP_STRING_SIZE);
    sprintf(temp, "Q:Count=%d: ", (the_queue->size));
    Node_p current_node = the_queue->my_node;
    strcat(str, temp);
    
    for(the_current_node_number = 0; the_current_node_number < the_queue->size; the_current_node_number++) {
        if(the_current_node_number>0) {
            strcat(str,">");
        }
        
        sprintf(temp, "P%d-", current_node->node_number); 
        strcat(str, temp);
        if(the_current_node_number < (the_queue->size)-1) {
            current_node = current_node->next_node;
        }
        
    }
    strcat(str,"*\n");
    free(temp);
    fflush(stdout);
    return str;
}

int getQueueSize(FIFOq_p the_queue) {
    if (check_pointer(the_queue) == NO_OBJ_ERR) {
        char *err = malloc (sizeof (char));
        err[0] = NO_OBJ_ERR;
        return -1;
    }
    return the_queue->size;
}


