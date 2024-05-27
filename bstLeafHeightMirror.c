#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};

struct Queue
{
    struct Node* data;
    struct Queue* next;
};

struct Queue* front;
struct Queue* rear;

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

    struct Queue* temp = front;

    if (front == rear)
    {
        front = NULL;
        rear = NULL;
    }

    else
    {
        front = front->next;
    }

    free(temp);
}

struct Node* getFront()
{
    if (isEmpty())
    {
        printf("Queue is empty\n");
    }

    else
    {
        return (front->data);
    }
};

struct Node*createNode(int key)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory Allocation failed\n");
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

    else if(key > root->data)
    {
        root->right = insert(root->right, key);
    }

    else
    {
        root->left = insert(root->left, key);
        return root;
    }
};

int treeHeight(struct Node* root)
{
    if (root == NULL)
    {
        return 0;
    }

    Enqueue(root);
    int height = 0;

    while(!isEmpty())
    {
        int nodeCount = 0;

        for(struct Queue* temp = front;temp != NULL;temp = temp->next)
        {
            nodeCount++;
        }

        while (nodeCount > 0)
        {
            struct Node* node = getFront();
            Dequeue();

            if (node->left != NULL)
            {
                Enqueue(node->left);
            }

            if (node->right != NULL)
            {
                Enqueue(node->right);
            }
            nodeCount--;
        }
        height++;
    }
    return height;
}

void mirror(struct Node* root)
{
    struct Node* temp;
    struct stack* top = NULL;

    push(root,&top);

    while (!emptyStack(top))
    {
        root = pop(&top);

        temp = root->left;
        root->left = root->right;
        root->right = temp;

        if (root->left != NULL)
        {
            push(root->left,&top);
        }

        if (root->right != NULL)
        {
            push(root->right,&top);
        }
    }
}

void leafNodes(struct Node* root)
{
    struct Node* temp;
    struct stack* top = NULL;

    push(root,&top);

    while (!emptyStack(top))
    {
        root = pop(&top);

        if (root->left == NULL && root->right == NULL)
        {
            printf("%d ",root->data);
        }

        if (root->left != NULL)
        {
            push(root->left,&top);
        }

        if (root->right != NULL)
        {
            push(root->right,&top);
        }
    }
}

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

    while(1)
    {
        int choice;

        printf("\n1. Create BST \n2. Insert \n3. Height of tree \n4. Leaf Nodes \n5. Mirror \n6. Level Order\n 7.Exit\n");
        printf("Enter your choice\n");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            printf("Enter value\n");
            scanf("%d",&key);
            root = createNode(key);
            break;
        case 2:
            printf("Enter value\n");
            scanf("%d",&key);
            root = insert(root,key);
            break;
        case 3:
            key = treeHeight(root);
            printf("Height of tree is: %d\n",key);
            break;
        case 4:
            leafNodes(root);
            break;
        case 5:
            mirror(root);
            break;
        case 6:
            levelOrder(root);
            break;
        case 7:
            exit(0);
            break;
        }
    }
}
