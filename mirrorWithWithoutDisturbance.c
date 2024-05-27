#include <stdio.h>
#include <stdlib.h>

// Definition of a tree node
struct TreeNode {
    int key;
    struct TreeNode *left, *right;
};

// Function to create a new tree node
struct TreeNode* newNode(int key) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Function to insert a new key into the BST
struct TreeNode* insert(struct TreeNode* node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    return node;
}

// Function to create the mirror image of a tree without disturbing the original tree
struct TreeNode* mirror(struct TreeNode* node) {
    if (node == NULL) return NULL;
    struct TreeNode* mirrorNode = newNode(node->key);
    mirrorNode->left = mirror(node->right);
    mirrorNode->right = mirror(node->left);
    return mirrorNode;
}

// Function to create the mirror image of a tree by modifying the original tree
void mirrorInPlace(struct TreeNode* node) {
    if (node == NULL) return;
    struct TreeNode* temp;
    mirrorInPlace(node->left);
    mirrorInPlace(node->right);
    temp = node->left;
    node->left = node->right;
    node->right = temp;
}

// Function to print inorder traversal of a tree
void inorder(struct TreeNode* node) {
    if (node != NULL) {
        inorder(node->left);
        printf("%d ", node->key);
        inorder(node->right);
    }
}

// Function to calculate the height of the tree using a non-recursive approach
int height(struct TreeNode* root) {
    if (root == NULL) return 0;

    int height = 0;
    struct TreeNode* queue[1000]; // Assumes the tree has at most 1000 nodes
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front != rear) {
        int nodeCount = rear - front;
        height++;

        while (nodeCount > 0) {
            struct TreeNode* node = queue[front++];

            if (node->left)
                queue[rear++] = node->left;
            if (node->right)
                queue[rear++] = node->right;

            nodeCount--;
        }
    }

    return height;
}

int main() {
    struct TreeNode* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder traversal of the original tree:\n");
    inorder(root);
    printf("\n");

    // Creating a mirror image without disturbing the original tree
    struct TreeNode* mirrorRoot = mirror(root);
    printf("Inorder traversal of the mirror image tree without disturbing the original tree:\n");
    inorder(mirrorRoot);
    printf("\n");

    // Creating a mirror image by modifying the original tree
    mirrorInPlace(root);
    printf("Inorder traversal of the mirror image tree by modifying the original tree:\n");
    inorder(root);
    printf("\n");

    // Calculate and print the height of the original tree (before it was modified)
    int treeHeight = height(root);
    printf("Height of the modified tree: %d\n", treeHeight);

    return 0;
}
