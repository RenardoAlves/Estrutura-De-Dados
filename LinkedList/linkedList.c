#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *first;
} List;

void insertStart (int n, List *list) {
    Node *new = malloc(sizeof(Node));

    new->value = n;
    new->next = NULL;

    if (list->first == NULL) {
        list->first = new;
    } else {
        new->next = list->first;
        list->first = new;
    }
}

void insertEnd (int n, List *list) {
    Node *new = malloc(sizeof(Node));

    new->value = n;
    new->next = NULL;

    if (list->first == NULL) {
        list->first = new;
    } else {
        Node *actual = list->first;

        while (actual->next != NULL) {
            actual = actual->next;
        }

        actual->next = new;
    }
}

void insertIndex (int n, int index, List *list) {
    Node *new = malloc(sizeof(Node));

    new->value = n;
    new->next = NULL;

    Node *actual = list->first;

    for (int i = 0; i < index - 1; i++) {
        actual = actual->next;
    }

    new->next = actual->next;
    actual->next = new;
}

void removeIndex (int index, List *list) {

    if (index == 0) {
        Node *remove = list->first;
        list->first = list->first->next;
        free(remove);
        return;
    }

    Node *actual = list->first;

    for (int i = 0; i < index - 1; i++) {
        actual = actual->next;
    }

    Node *remove = actual->next;

    actual->next = remove->next;

    free(remove);
}

void printList (List list) {
    Node *actual = list.first;

    while (actual != NULL) {
        printf("[%d]  ", actual->value);
        actual = actual->next;
    }
    printf("\n");
}

int main () {
    List list01;
    list01.first = NULL;

    insertStart(1, &list01);
    insertStart(5, &list01);
    insertStart(10, &list01);
    insertStart(15, &list01);
    insertStart(20, &list01);
    insertStart(25, &list01);
    insertStart(30, &list01);

    printList(list01);

    insertEnd(2, &list01);
    insertEnd(3, &list01);
    insertEnd(4, &list01);
    insertEnd(5, &list01);

    printList(list01);

    insertIndex(7, 2, &list01);
    printList(list01);

    removeIndex(0, &list01);
    printList(list01);

    removeIndex(3, &list01);
    printList(list01);
}