#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 1000

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

bool findPair(struct Node* root, int sum, int* visited, int* foundA, int* foundB) {
    if (root == NULL) return false;

    if (findPair(root->left, sum, visited, foundA, foundB)) return true;

    int complement = sum - root->data;
    if (visited[complement]) {
        *foundA = complement;
        *foundB = root->data;
        return true;
    }

    visited[root->data] = 1; 

    return findPair(root->right, sum, visited, foundA, foundB);
}

int main() {
    struct Node* root = NULL;
    int values[] = {10, 5, 15, 3, 7, 12, 18};
    int n = sizeof(values)/sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    int target;
    printf("Enter the target sum: ");
    scanf("%d", &target);

    int visited[MAX_NODES] = {0};
    int a = -1, b = -1;

    if (findPair(root, target, visited, &a, &b)) {
        printf("Found nodes with values %d and %d that sum to %d\n", a, b, target);
    } else {
        printf("No such pair found.\n");
    }

    return 0;
}
