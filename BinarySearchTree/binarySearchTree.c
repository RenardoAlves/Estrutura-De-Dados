#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode (int value) {
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Erro de alocacao.\n");
        exit(1);
    }

    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node* insert (Node *tree, int value) {
    if (tree == NULL) {
        return createNode(value);
    }

    if (value < tree->value) {
        tree->left = insert(tree->left, value);
    } else if (value > tree->value) {
        tree->right = insert(tree->right, value);
    }

    return tree;
}

Node* search (Node *tree, int value) {
    if (tree == NULL || tree->value == value) {
        return tree;
    }

    if (value < tree->value) {
        return search(tree->left, value);
    }

    return search(tree->right, value);
}

Node* minValueNode (Node *node) {
    Node *current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

Node* removeNode (Node *tree, int value) {
    if (tree == NULL) {
        return tree;
    }

    if (value < tree->value) {
        tree->left = removeNode(tree->left, value);
    } else if (value > tree->value) {
        tree->right = removeNode(tree->right, value);
    } else {
        if (tree->left == NULL) {
            Node *temp = tree->right;
            free(tree);
            return temp;
        } else if (tree->right == NULL) {
            Node *temp = tree->left;
            free(tree);
            return temp;
        }

        Node *temp = minValueNode(tree->right);
        tree->value = temp->value;
        tree->right = removeNode(tree->right, temp->value);
    }

    return tree;
}

void inOrder (Node *tree) {
    if (tree != NULL) {
        inOrder(tree->left);
        printf("[%d]  ", tree->value);
        inOrder(tree->right);
    }
}

void preOrder (Node *tree) {
    if (tree != NULL) {
        printf("[%d]  ", tree->value);
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

void postOrder (Node *tree) {
    if (tree != NULL) {
        postOrder(tree->left);
        postOrder(tree->right);
        printf("[%d]  ", tree->value);
    }
}

void freeTree (Node *tree) {
    if(tree != NULL) {
        freeTree(tree->left);
        freeTree(tree->right);
        free(tree);
    }
}

int main() {
    Node *root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("In-order: ");
    inOrder(root);
    printf("\n");

    printf("Pre-order: ");
    preOrder(root);
    printf("\n");

    printf("Post-order: ");
    postOrder(root);
    printf("\n");

    Node *found = search(root, 40);
    if (found != NULL) {
        printf("Valor 40 encontrado.\n");
    } else {
        printf("Valor 40 nao encontrado.\n");
    }

    root = removeNode(root, 30);

    printf("In-order: ");
    inOrder(root);
    printf("\n");

    freeTree(root);

    return 0;
}