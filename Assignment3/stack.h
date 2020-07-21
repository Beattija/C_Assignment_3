/*
Jason Beattie <beattija@sheridan.desire2learn.com>
----------------------------------------------------------------------
 */
#include <stdlib.h>

typedef struct node {
    int num;
    struct node *next;
} Node, *NodePtr;

typedef struct {
    NodePtr top;
    int size;
} StackType, *Stack;

Stack initStack() {
    Stack stackPtr = (Stack) malloc(sizeof (StackType));
    stackPtr->top = NULL;
    return stackPtr;
}

void isEmpty(Stack stack) {
    if (stack->top != NULL) {
        printf("Stack is not empty\n");
    } else {
        printf("Stack is empty\n");
    }

}

void push(Stack stack, int num) {
    NodePtr nodePtr;
    nodePtr = (struct node*) malloc(sizeof (struct node));
    nodePtr->num = num;
    nodePtr->next = stack->top;
    stack->top = nodePtr;
    stack->size += 1;
}

void pop(Stack stack) {
    if (stack->top != NULL) {
        printf("%d popped\n", stack->top->num);
        NodePtr tmp = stack->top;
        stack->top = stack->top->next;
        free(tmp);
        stack->size -= 1;
    }
}

void peek(Stack stack) {
    if (stack != NULL) {
        printf("Number on top is %d\n", stack->top->num);
    } else {
        printf("Stack is empty");
    }
}

void size(Stack stack) {
    printf("The size of the stack is %d \n", stack->size);
}