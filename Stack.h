#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>



typedef struct StackNode{
	Item elem;
	struct StackNode *next;
}StackNode;

typedef StackNode TCelSt; // Redenumirea unui nod la notatiile din curs 
typedef StackNode *ACelSt; // Redenumirea unui pointer la nod la notatiile din curs

typedef struct Stack{
	StackNode* head;  // Varful stivei
	long size; // Numarul de elemente din stiva
}Stack;

typedef Stack TStiva; // Redenumirea stivei la notatiile din curs
typedef Stack *ASt;//  // Redenumirea unui pointer la stiva la notatiile din curs

Stack* createStack(void){
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->head = NULL;
	s -> size = 0;
	return s;
}

int isStackEmpty(Stack* stack){
	// TODO: Cerinta 1
	if( stack == NULL ) return 0;

	return (stack->head == NULL);
}

void push(Stack *stack, Item elem){
	// TODO: Cerinta 1
	StackNode *node =(StackNode *)malloc(sizeof(StackNode));

	node->elem = elem;
	node->next = stack->head;
	stack->head = node;
	stack->size++;
}


void pop(Stack *stack){
	StackNode *node = stack->head;
	stack->head = stack->head->next;
	stack->size--;
	free(node);
}

void destroyStack(Stack *stack){
	while(stack->head != NULL){
		pop(stack);
	}
	free(stack);
}

#endif 
