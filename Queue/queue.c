#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *first;
    Node *last;
} Queue;

void enqueue (int n, Queue *queue) {
    Node *new = malloc(sizeof(Node));

    new->value = n;
    new->next = NULL;

    if (queue->first == NULL) {
        queue->first = new;
        queue->last = new;
    } else {
        queue->last->next = new;
        queue->last = new;
    }
}

int dequeue (Queue *queue) {
    Node *actual = queue->first;

    if (queue->first == NULL) {
        return -1;
    }

    queue->first = queue->first->next;
    int n = actual->value;
    free(actual);

    return n;
}

void pqueue (Queue queue) {
    while(queue.first != NULL) {
        printf("[%d]  ", queue.first->value);
        queue.first = queue.first->next;
    }
    printf("\n");
}

int main () {
    Queue queue01;
    queue01.first = NULL;
    queue01.last = NULL;

    enqueue(1, &queue01);
    enqueue(3, &queue01);
    enqueue(5, &queue01);
    enqueue(7, &queue01);
    enqueue(9, &queue01);
    enqueue(11, &queue01);

    pqueue(queue01);

    dequeue(&queue01);
    dequeue(&queue01);

    pqueue(queue01);
}