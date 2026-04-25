#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node *right;
    struct Node *left;
} Node;

typedef struct QueueNode {
    Node *treeNode;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
} Queue;

Node* createNode (int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

Queue* createQueue () {
    Queue *q = malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enqueue (Queue *q, Node *treeNode) {
    QueueNode *newNode = malloc(sizeof(QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

Node* dequeue (Queue *q) {
    if (q->front == NULL) return NULL;

    QueueNode *temp = q->front;
    Node *treeNode = temp->treeNode;

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return treeNode;
}

int isEmpty (Queue *q) {
    return q->front == NULL;
}

Node* insert(Node *tree, int value) {
    Node *newNode = createNode(value);

    if (tree == NULL) {
        return newNode;
    }

    Queue *q = createQueue();
    enqueue(q, tree);

    while (!isEmpty(q)) {
        Node *current = dequeue(q);

        if (current->left == NULL) {
            current->left = newNode;
            free(q);
            return tree;
        } else {
            enqueue(q, current->left);
        }

        if (current->right == NULL) {
            current->right = newNode;
            free(q);
            return tree;
        } else {
            enqueue(q, current->right);
        }
    }

    return tree;
}

void preOrder (Node *tree) {
    if (tree == NULL) return;

    printf("[%d]  ", tree->value);
    preOrder(tree->left);
    preOrder(tree->right);
}

void inOrder (Node *tree) {
    if (tree == NULL) return;

    inOrder(tree->left);
    printf("[%d]  ", tree->value);
    inOrder(tree->right);
}

void postOrder (Node *tree) {
    if (tree == NULL) return;

    postOrder(tree->left);
    postOrder(tree->right);
    printf("[%d]  ", tree->value);
}

int main () {
    Node *tree = NULL;

    tree = insert(tree, 1);
    tree = insert(tree, 2);
    tree = insert(tree, 3);
    tree = insert(tree, 4);
    tree = insert(tree, 5);
    tree = insert(tree, 6);
    tree = insert(tree, 7);

    inOrder(tree);
    printf("\n");
    preOrder(tree);
    printf("\n");
    postOrder(tree);
}