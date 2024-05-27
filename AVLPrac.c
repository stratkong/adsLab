#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

struct Queue
{
    struct Node* data;
    struct Queue* next;
};

struct Queue* front;
struct Queue* rear;

int isEmpty()
{
    if (front == NULL && rear == NULL)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

void Enqueue(struct Node* node)
{
    struct Queue* p = (struct Queue*)malloc(sizeof(struct Queue));

    p->data = node;
    p->next = NULL;

    if (isEmpty())
    {
        front = p;
        rear = p;
    }

    else
    {
        rear->next = p;
        rear = p;
    }
}

void Dequeue()
{
    if (isEmpty())
    {
        printf("Queue is empty\n");
    }

    struct Queue* p = front;

    if (front == rear)
    {
        front = NULL;
        rear = NULL;
    }

    else
    {
        front = front->next;
    }

    free(p);
}

int height(struct Node* root)
{
    if (root == NULL)
    {
        return 0;
    }

    return root->height;
}

int max (int a, int b)
{
    return (a > b)? a : b;
}

struct Node* createNode(int key)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;

    return newNode;
};

struct Node* rightRotate(struct Node* y)
{
    struct Node* x = y->left;
    struct Node* t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
};

struct Node* leftRotate(struct Node* x)
{
    struct Node* y = x->right;
    struct Node* t2 = y->left;

    y->left = x;
    x->right = t2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(y->right)) + 1;

    return y;
};

int getBalance(struct Node* root)
{
    if (root == NULL)
    {
        return 0;
    }

    return height(root->left) - height(root->right);
}

struct Node* insert(struct Node* root, int key)
{
    if (root == NULL)
    {
        root = createNode(key);
    }

    if (key < root->data)
    {
        root->left= insert(root->left, key);
    }

    else if (key > root->data)
    {
        root->right = insert(root->right, key);
    }

    else
    {
        return root;
    }

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    if (balance > 1 && key < root->left->data)
    {
        return rightRotate(root);
    }

    if (balance < -1 && key > root->right->data)
    {
        return leftRotate(root);
    }

    if (balance > 1 && key > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && key < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
};

void levelOrder(struct Node* root)
{
    Enqueue(root);
    Enqueue(NULL);

    while (!isEmpty())
    {
        struct Node* current = front->data;
        Dequeue();

        if (current == NULL)
        {
            printf("\n");

            if (!isEmpty())
            {
                Enqueue(NULL);
            }
        }

        else
        {
            printf("%d ",current->data);

            if (current->left != NULL)
            {
                Enqueue(current->left);
            }

            if (current->right != NULL)
            {
                Enqueue(current->right);
            }
        }
    }
}

int main()
{
    struct Node* root = NULL;
    int key;

    while (1)
    {
        int choice;
        printf("\n1. Create \n2. Insert \n3. Level Order \n4. Exit\n");
        printf("Enter your choice\n");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            printf("Enter value\n");
            scanf("%d",&key);
            root = createNode (key);
            break;
        case 2:
            printf("Enter value\n");
            scanf("%d",&key);
            root = insert(root, key);
            break;
        case 3:
            levelOrder(root);
            break;
        case 4:
            exit(0);
            break;
        }
    }
}
