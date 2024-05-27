#include <stdio.h>
#include <stdlib.h>

struct TBTNode
{
    int data;
    struct TBTNode* left;
    struct TBTNode* right;
    int lbit;
    int rbit;
};

struct TBTNode* create(struct TBTNode* head, int key)
{
    struct TBTNode* temp;
    struct TBTNode* p;

    temp = (struct TBTNode*)malloc(sizeof(struct TBTNode));

    temp->data = key;
    temp->lbit = temp->rbit = 0;

    if (head->lbit == 0)
    {
        head->left = temp;
        head->lbit = 1;
        temp->left = temp->right = head;

        return head;
    }

    p = head->left;

    while (1)
    {
        if (key < p->data && p->lbit == 1)
        {
            p = p->left;
        }

        else if (key > p->data && p->rbit == 1)
        {
            p = p->right;
        }

        else
        {
            break;
        }
    }

    if (key < p->data)
    {
        temp->right = p;
        temp->left = p->left;
        p->left = temp;
        p->lbit = 1;
    }

    if (key > p->data)
    {
        temp->left = p;
        temp->right = p->right;
        p->right = temp;
        p->rbit = 1;
    }

    return head;
};

void inOrder(struct TBTNode* head)
{
    struct TBTNode* temp = head->left;

    while(temp->lbit == 1)
    {
        temp = temp->left;
    }

    while (temp != head)
    {
        printf("%d ",temp->data);

        if (temp->rbit == 0)
        {
            temp = temp->right;
        }

        else if (temp->rbit == 1)
        {
            temp = temp->right;

            while(temp->lbit == 1)
            {
                temp = temp->left;
            }
        }
    }
}

void preOrder(struct TBTNode* head)
{
    struct TBTNode* temp = head->left;

    while (temp != head)
    {
        printf("%d ",temp->data);

        if (temp->lbit == 1)
        {
            temp = temp->left;
        }

        else if (temp->rbit == 1)
        {
            temp = temp->right;
        }

        else if (temp->rbit == 0)
        {
            while (temp->rbit == 0)
            {
                temp = temp->right;
            }
            temp = temp->right;
        }
    }
}

int main()
{
    struct TBTNode* head = NULL;

    int key;
    int n;

    head = (struct TBTNode*)malloc(sizeof(struct TBTNode));
    head->lbit = 0;
    head->rbit = 1;
    head->left = head->right = head;

    while(1)
    {
        int choice;
        printf("\n1. Insert \n2. Inorder \n3. Preorder \n4. Exit\n");
        printf("Enter your choice\n");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            printf("Enter number of nodes\n");
            scanf("%d",&n);

            for (int i = 0;i < n;i++)
            {
                printf("Enter value\n");
                scanf("%d",&key);
                head = create(head, key);
            }
            break;
        case 2:
            inOrder(head);
            break;
        case 3:
            preOrder(head);
            break;
        case 4:
            exit(0);
            break;
        }
    }
}
