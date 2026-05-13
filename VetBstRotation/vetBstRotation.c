#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 250
#define STR_LEN 50

typedef struct {
    char data[SIZE][STR_LEN];
    int used[SIZE];
} BST;

typedef struct {
    char values[SIZE][STR_LEN];
    int count;
} Buffer;

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

void insertAt (BST *tree, char *value, int i) {
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
            i = 2 * i + 2;
        } else {
            return;
        }
    }
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

int balanceFactor (BST *tree, int i) {
    if (i >= SIZE || !tree->used[i]) return -1;
   
    return getNodeHeight(tree, 2 * i + 1) - getNodeHeight(tree, 2 * i + 2);
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

void savePreOrder (BST *tree, int i, Buffer *buffer) {
    if (i >= SIZE || !tree->used[i]) return;

    strcpy(buffer->values[buffer->count], tree->data[i]);
    buffer->count++;

    savePreOrder(tree, 2 * i + 1, buffer);
    savePreOrder(tree, 2 * i + 2, buffer);
}

void clearSubtree (BST *tree, int i) {
    if (i >= SIZE || !tree->used[i]) return;

    clearSubtree(tree, 2 * i + 1);
    clearSubtree(tree, 2 * i + 2);

    tree->used[i] = 0;
}

void rotateLeft (BST *tree, int root) {
    int right = 2 * root + 2;

    if (right >= SIZE || !tree->used[right]) {
        printf("Rotacao esquerda impossivel!\n");
        return;
    }

    Buffer buffer;
    buffer.count = 0;

    savePreOrder(tree, root, &buffer);

    char rootValue[STR_LEN];
    char rightValue[STR_LEN];

    strcpy(rootValue, tree->data[root]);
    strcpy(rightValue, tree->data[right]);

    clearSubtree(tree, root);

    strcpy(tree->data[root], rightValue);
    tree->used[root] = 1;

    int leftChild = 2 * root + 1;

    strcpy(tree->data[leftChild], rootValue);
    tree->used[leftChild] = 1;

    for (int i = 0; i < buffer.count; i++) {
        if (
            strcmp(buffer.values[i], rootValue) != 0 &&
            strcmp(buffer.values[i], rightValue) != 0
        ) {
            insertAt(tree, buffer.values[i], root);
        }
    }
}

void rotateRight (BST *tree, int root) {
    int left = 2 * root + 1;

    if (left >= SIZE || !tree->used[left]) {
        printf("Rotacao direita impossivel!\n");
        return;
    }

    Buffer buffer;
    buffer.count = 0;

    savePreOrder(tree, root, &buffer);

    char rootValue[STR_LEN];
    char leftValue[STR_LEN];

    strcpy(rootValue, tree->data[root]);
    strcpy(leftValue, tree->data[left]);

    clearSubtree(tree, root);

    strcpy(tree->data[root], leftValue);
    tree->used[root] = 1;

    int rightChild = 2 * root + 2;

    strcpy(tree->data[rightChild], rootValue);
    tree->used[rightChild] = 1;

    for (int i = 0; i < buffer.count; i++) {
        if (
            strcmp(buffer.values[i], rootValue) != 0 &&
            strcmp(buffer.values[i], leftValue) != 0
        ) {
            insertAt(tree, buffer.values[i], root);
        }
    }
}

int main () {
    BST tree;
    initBST(&tree);
    int height, targetNode, nodeHeight, factor;

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

    height = getTreeHeight(&tree);

    printf("Altura da arvore: %d", height);
    printf("\n");

    targetNode = 0;
    nodeHeight = getNodeHeight(&tree, targetNode);

    printf("Altura do no %d: %d", targetNode, nodeHeight);
    printf("\n");
   
    factor = balanceFactor(&tree, targetNode);
   
    printf("Fator de balanceamento do no %d: %d\n", targetNode, factor);

    printf("Pre-order antes das rotacoes: ");
    preOrder(&tree, 0);
    printf("\n");

    rotateLeft(&tree, 0);

    printf("Pre-order apos rotacao esquerda: ");
    preOrder(&tree, 0);
    printf("\n");

    rotateRight(&tree, 0); //Desfaz rotação anterior
    rotateRight(&tree, 0);

    printf("Pre-order apos rotacao direita: ");
    preOrder(&tree, 0);
    printf("\n");

    height = getTreeHeight(&tree);

    printf("Altura da arvore: %d", height);
    printf("\n");

    targetNode = 0;
    nodeHeight = getNodeHeight(&tree, targetNode);

    printf("Altura do no %d: %d", targetNode, nodeHeight);
    printf("\n");
   
    factor = balanceFactor(&tree, targetNode);
   
    printf("Fator de balanceamento do no %d: %d\n", targetNode, factor);

    return 0;
}