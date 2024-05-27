#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};

struct stack
{
    struct Node* t;
    struct stack* next;
};

void push(struct Node* root, struct stack** top)
{
    struct stack* temp = (struct stack*)malloc(sizeof(struct stack));

    temp->t = root;
    temp->next = (*top);
    (*top) = temp;
}

struct Node* pop(struct stack** top)
{
    struct stack* temp;
    struct Node* n;

    temp = (*top);
    n = temp->t;
    (*top) = (*top)->next;

    free(temp);
    return n;
};

int emptyStack(struct stack* top)
{
    if (top == NULL)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

struct Node* topStack(struct stack** top)
{
    return ((*top)->t);
};

struct Node* createNode(int key)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
    }

    newNode->data = key;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
};

struct Node* insert(struct Node* root, int key)
{
    if (root == NULL)
    {
        root = createNode(key);
    }

    else if (key > root->data)
    {
        root->right = insert(root->right, key);
    }

    else
    {
        root->left = insert(root->left, key);
        return root;
    }
};

struct Node* findMin(struct Node* root)
{
    if (root == NULL)
    {
        return NULL;
    }

    while (root->left != NULL)
    {
        root = root->left;
    }

    return root;
};

struct Node* deletion(struct Node* root, int key)
{
    struct Node* temp;

    if (root == NULL)
    {
        return root;
    }

    else if (key > root->data)
    {
        root->right = deletion(root->right, key);
    }

    else if (key < root->data)
    {
        root->left = deletion(root->left, key);
    }

    else
    {
        if (root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }

        else if (root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }

        else if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        else
        {
            temp = findMin(root->right);

            root->data = temp->data;
            root->right = deletion(root->right, temp->data);
        }
    }
    return root;
};

void inOrder(struct Node* root)
{
    struct stack* top = NULL;

    while (root != NULL)
    {
        push(root,&top);
        root = root->left;
    }

    while (!emptyStack(top))
    {
        root = pop(&top);

        printf("%d ",root->data);

        root = root->right;

        while (root != NULL)
        {
            push(root,&top);
            root = root->left;
        }
    }
}

void preOrder(struct Node* root)
{
    struct stack* top = NULL;

    while (root != NULL)
    {
        printf("%d ",root->data);
        push(root,&top);
        root = root->left;
    }

    while (!emptyStack(top))
    {
        root = pop(&top);
        root = root->right;

        while (root != NULL)
        {
            printf("%d ",root->data);
            push(root,&top);
            root = root->left;
        }
    }
}

void postOrder(struct Node* root)
{
    struct stack* top = NULL;
    struct Node* prev = NULL;
    struct Node* t = root;

    while (t != NULL)
    {
        push(t,&top);
        t = t->left;
    }

    while (!emptyStack(top))
    {
        t = topStack(&top);

        if (t->right == NULL || t->right == prev)
        {
            printf("%d ",t->data);
            pop(&top);
            prev = t;
        }

        else
        {
            t = t->right;
            while (t != NULL)
            {
                push(t,&top);
                t = t->left;
            }
        }
    }
}

int main()
{
    struct Node* root = NULL;
    int key;

    while(1)
    {
        int choice;
        printf("\n1. Create BST \n2. Insert \n3. Delete \n4. Inorder \n5. Preorder \n6. Postorder \n7. Exit\n");
        printf("Enter your choice\n");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            printf("Enter value to create BST\n");
            scanf("%d",&key);
            root = createNode(key);
            break;
        case 2:
            printf("Enter value to insert\n");
            scanf("%d",&key);
            root = insert(root,key);
            break;
        case 3:
            printf("Enter the value you want to delete\n");
            scanf("%d",&key);
            root = deletion(root,key);
            break;
        case 4:
            inOrder(root);
            break;
        case 5:
            preOrder(root);
            break;
        case 6:
            postOrder(root);
            break;
        case 7:
            exit(0);
            break;
        }
    }
}
