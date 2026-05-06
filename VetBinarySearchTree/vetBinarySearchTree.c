#include <stdio.h>
#include <stdlib.h>

#define SIZE 250

typedef struct {
    int data[SIZE];
    int used[SIZE];
} BST;

void initBST (BST *tree) {
    for (int i = 0; i < SIZE; i++) {
        tree->used[i] = 0;
    }
}

void insert (BST *tree, int value) {
    int i = 0;

    while (i < SIZE) {
        if (!tree->used[i]) {
            tree->data[i] = value;
            tree->used[i] = 1;
            return;
        }

        if (value < tree->data[i]) {
            i = 2 * i + 1;
        } else if (value > tree->data[i]) {
            i = 2 * i + 2;
        } else {
            return;
        }
    }

    printf("Árvore cheia ou fora do limite.\n");
}

int search (BST *tree, int value) {
    int i = 0;

    while (i < SIZE && tree->used[i]) {
        if (value == tree->data[i]){
            return i;
        }

        if (value < tree->data[i]) {
            i = 2 * i + 1;
        } else {
            i = 2 * i + 2;
        }
    }

    return -1;
}

int max (int a, int b) {
    return (a > b) ? a : b;
}

int calculateHeight (BST *tree, int i) {
    if (i >= SIZE || tree->used[i] == 0) return -1;

    int h_left = calculateHeight(tree, 2 * i + 1);
    int h_right = calculateHeight(tree, 2 * i + 2);

    return 1 + max(h_left, h_right);
}

int getHeight (BST *tree) {
    return calculateHeight(tree, 0);
}

void inOrder (BST *tree, int i) {
    if ( i >= SIZE || !tree->used[i]) return;

    inOrder(tree, 2 * i + 1);
    printf("[%d]  ", tree->data[i]);
    inOrder(tree, 2 * i + 2);
}

void preOrder (BST *tree, int i) {
    if (i >= SIZE || !tree->used[i]) return;

    printf("[%d]  ", tree->data[i]);
    preOrder(tree, 2 * i + 1);
    preOrder(tree, 2 * i + 2);
}

void postOrder (BST *tree, int i) {
    if (i >= SIZE || !tree->used[i]) return;

    postOrder(tree, 2 * i + 1);
    postOrder(tree, 2 * i + 2);
    printf("[%d]  ", tree->data[i]);
}

int main () {
    BST tree;
    initBST(&tree);

    insert(&tree, 100);
    insert(&tree, 70);
    insert(&tree, 200);
    insert(&tree, 250);
    insert(&tree, 180);
    insert(&tree, 90);
    insert(&tree, 70);
    insert(&tree, 80);
    insert(&tree, 90);
    insert(&tree, 20);
    insert(&tree, 5);
    insert(&tree, 17);
    insert(&tree, 13);
    insert(&tree, 15);

    printf("In-order: ");
    inOrder(&tree, 0);
    printf("\n");

    printf("Pre-order: ");
    preOrder(&tree, 0);
    printf("\n");

    printf("Post-order: ");
    postOrder(&tree, 0);
    printf("\n");

    int height = getHeight(&tree);

    printf("Altura da arvore: %d", height);

    return 0;
}