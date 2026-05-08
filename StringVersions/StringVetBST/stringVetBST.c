#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 250
#define STR_LEN 50

typedef struct {
    char data[SIZE][STR_LEN];
    int used[SIZE];
} BST;

void initBST (BST *tree) {
    for (int i = 0; i < SIZE; i++) {
        tree->used[i] = 0;
    }
}

void insert (BST *tree, char *value) {
    int i = 0;

    while (i < SIZE) {
        if (!tree->used[i]) {
            strcpy(tree->data[i], value);
            tree->used[i] = 1;
            return;
        }

        int cmp = strcmp(value, tree->data[i]);

        if (cmp < 0) {
            i = 2 * i + 1;
        } else if (cmp > 0) {
            i = 2 *i + 2;
        } else {
            return;
        }
    }
    printf("Erro: Limite da arvore atingido!\n");
}

int search (BST *tree, char *value) {
    int i = 0;

    while (i < SIZE && tree->used[i]) {
        int cmp = strcmp(value, tree->data[i]);

        if (cmp == 0) return i;

        if (cmp < 0) {
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

int getNodeHeight (BST *tree, int i) {
    if (i >= SIZE || tree->used[i] == 0) return -1;

    int h_left = getNodeHeight(tree, 2 * i + 1);
    int h_right = getNodeHeight(tree, 2 * i + 2);

    return 1 + max(h_left, h_right);
}

int getTreeHeight (BST *tree) {
    return getNodeHeight(tree, 0);
}

void inOrder (BST *tree, int i) {
    if ( i >= SIZE || !tree->used[i]) return;

    inOrder(tree, 2 * i + 1);
    printf("[%s]  ", tree->data[i]);
    inOrder(tree, 2 * i + 2);
}

void preOrder (BST *tree, int i) {
    if (i >= SIZE || !tree->used[i]) return;

    printf("[%s]  ", tree->data[i]);
    preOrder(tree, 2 * i + 1);
    preOrder(tree, 2 * i + 2);
}

void postOrder (BST *tree, int i) {
    if (i >= SIZE || !tree->used[i]) return;

    postOrder(tree, 2 * i + 1);
    postOrder(tree, 2 * i + 2);
    printf("[%s]  ", tree->data[i]);
}

int main () {
    BST tree;
    initBST(&tree);

    insert(&tree, "Janeiro");
    insert(&tree, "Fevereiro");
    insert(&tree, "Marco");
    insert(&tree, "Abril");
    insert(&tree, "Maio");
    insert(&tree, "Junho");
    insert(&tree, "Julho");
    insert(&tree, "Agosto");
    insert(&tree, "Setembro");
    insert(&tree, "Outubro");
    insert(&tree, "Novembro");
    insert(&tree, "Dezembro");

    printf("In-order: ");
    inOrder(&tree, 0);
    printf("\n");

    printf("Pre-order: ");
    preOrder(&tree, 0);
    printf("\n");

    printf("Post-order: ");
    postOrder(&tree, 0);
    printf("\n");

    int height = getTreeHeight(&tree);

    printf("Altura da arvore: %d", height);
    printf("\n");

    int targetNode = 2;
    int nodeHeight = getNodeHeight(&tree, targetNode);

    printf("Altura do no %d: %d", targetNode, nodeHeight);
    printf("\n");

    return 0;
}