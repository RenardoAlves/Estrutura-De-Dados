#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

void push (int n, Stack *stack) {
    Node *new = malloc(sizeof(Node));

    new->value = n;
    new->next = stack->top;
    stack->top = new;
}

int pop (Stack *stack) {
    Node *actual = stack->top;

    if (stack->top == NULL) {
        return -1;
    }

    int n = actual->value;
    stack->top = actual->next;
    free(actual);

    return n;
}

void pstack (Stack stack) {
    while (stack.top != NULL) {
        printf("[%d]  ", stack.top->value);
        stack.top = stack.top->next;
    }
    printf("\n");
}

int main () {
    Stack stack01;
    stack01.top = NULL;

    push(5, &stack01);
    push(7, &stack01);
    push(9, &stack01);
    push(11, &stack01);
    push(13, &stack01);
    push(15, &stack01);

    pstack(stack01);

    pop(&stack01);
    pop(&stack01);

    pstack(stack01);
}