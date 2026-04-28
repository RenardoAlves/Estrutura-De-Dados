#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct {
    int data[SIZE];
    int size;
} BinaryTree;

void initTree (BinaryTree *tree) {
    for (int i = 0; i < SIZE; i++) {
        tree->data[i] = -1;
    }
    tree->size = 0;
}

void insert (BinaryTree *tree, int value) {
    if (tree->size >= SIZE) {
        printf("Árvore cheia!\n");
        return;
    }

    tree->data[tree->size] = value;
    tree->size++;
}

void inOrder(BinaryTree *tree, int index) {
    if (index >= SIZE || tree->data[index] == -1)
        return;

    inOrder(tree, 2 * index + 1);
    printf("[%d]  ", tree->data[index]);
    inOrder(tree, 2 * index + 2);
}

void preOrder(BinaryTree *tree, int index) {
    if (index >= SIZE || tree->data[index] == -1)
        return;

    printf("[%d]  ", tree->data[index]);
    preOrder(tree, 2 * index + 1);
    preOrder(tree, 2 * index + 2);
}

void postOrder(BinaryTree *tree, int index) {
    if (index >= SIZE || tree->data[index] == -1)
        return;

    postOrder(tree, 2 * index + 1);
    postOrder(tree, 2 * index + 2);
    printf("[%d]  ", tree->data[index]);
}

int main () {
    BinaryTree tree;
    initTree(&tree);

    insert(&tree, 1);
    insert(&tree, 2);
    insert(&tree, 3);
    insert(&tree, 4);
    insert(&tree, 5);
    insert(&tree, 6);
    insert(&tree, 7);
    insert(&tree, 8);

    printf("In-order: ");
    inOrder(&tree, 0);
    printf("\n");

    printf("Pre-order: ");
    preOrder(&tree, 0);
    printf("\n");

    printf("Post-order: ");
    postOrder(&tree, 0);
    printf("\n");
}