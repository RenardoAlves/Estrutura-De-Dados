#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *previous;
} Node;

typedef struct {
    Node *first;
    Node *last;
} DoublyLinkedList;

void insertStart (int n, DoublyLinkedList *list) {
    Node *new = malloc(sizeof(Node));

    new->value = n;
    new->next = NULL;
    new->previous = NULL;

    if (list->first == NULL) {
        list->first = new;
        list->last = new;
        return;
    }

    list->first->previous = new;
    new->next = list->first;
    list->first = new;
}

void insertEnd (int n, DoublyLinkedList *list) {
    Node *new = malloc(sizeof(Node));

    new->value = n;
    new->next = NULL;
    new->previous = NULL;

    if (list->first == NULL) {
        list->first = new;
        list->last = new;
        return;
    }

    new->previous = list->last;
    list->last->next = new;
    list->last = new;
}

void insertIndex (int n, int index, DoublyLinkedList *list) {
    Node *new = malloc(sizeof(Node));

    new->value = n;
    new->next = NULL;
    new->previous = NULL;

    if (index == 0) {
        list->first->previous = new;
        new->next = list->first;
        list->first = new;
        return;
    }

    Node *actual = list->first;

    for (int i = 0; i < index; i++) {
        actual = actual->next;
    }

    new->previous = actual->previous;
    new->next = actual;
    actual->previous->next = new;
}

void printList (DoublyLinkedList list) {
    while (list.first != NULL) {
        printf("[%d]  ", list.first->value);
        list.first = list.first->next;
    }
    printf("\n");
}

int main () {
    DoublyLinkedList list01;
    list01.first = NULL;
    list01.last = NULL;

    insertStart(1, &list01);
    insertStart(3, &list01);
    insertStart(5, &list01);
    insertStart(7, &list01);

    printList(list01);

    insertEnd(10, &list01);
    insertEnd(20, &list01);
    insertEnd(30, &list01);

    printList(list01);

    insertIndex(0, 0, &list01);
    printList(list01);

    insertIndex(21, 2, &list01);
    printList(list01);
}