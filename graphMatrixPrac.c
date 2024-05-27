#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int stack[MAX];
int top = -1;

struct Queue
{
    int data;
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

void Enqueue(int key)
{
    struct Queue* p = (struct Queue*)malloc(sizeof(struct Queue));

    p->data = key;
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

int Dequeue()
{
    if (isEmpty())
    {
        printf("Queue is empty\n");
        return -1;
    }

    struct Queue* p = front;
    int key = p->data;

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
    return key;
}

int emptyStack()
{
    if (top == -1)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

void push(int key)
{
    if (top >= MAX - 1)
    {
        printf("Stack overflow\n");
        return;
    }

    stack[++top] = key;
}

int pop()
{
    if (emptyStack())
    {
        printf("Stack underflow\n");
        return -1;
    }

    return stack[top--];
}

void BFS(int G[10][10], int vertex)
{
    int visited[vertex], u, i, st;

    for (i = 0;i < vertex;i++)
    {
        visited[i] = 0;
    }

    printf("Enter the starting vertex\n");
    scanf("%d",&st);

    visited[st] = 1;
    Enqueue(st);

    while (!isEmpty())
    {
        u = Dequeue();
        printf("%d ",u);

        for (i = 0;i < vertex;i++)
        {
            if (G[u][i] == 1 && visited[i] == 0)
            {
                Enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

void DFS(int G[10][10], int vertex)
{
    int visited[vertex], u, st, i;

    for (i = 0;i < vertex;i++)
    {
        visited[i] = 0;
    }

    printf("Enter starting vertex\n");
    scanf("%d",&st);

    visited[st] = 1;
    push(st);

    printf("%d ",st);

    u = st;

    while (!emptyStack())
    {
        for (i = 0;i < vertex;i++)
        {
            if (G[u][i] == 1 && visited[i] == 0)
            {
                push(i);
                visited[i] = 1;
                printf("%d ",i);
                u = i;
                break;
            }
        }

        if (i == vertex)
        {
            pop();
            u = stack[top];
        }
    }
}

int main()
{
    int G[10][10], v, u, i, j, e, vertex;

    printf("Enter the number of vertices\n");
    scanf("%d",&vertex);

    for (i = 0;i < vertex;i++)
    {
        for (j = 0;j < vertex;j++)
        {
            G[i][j] = 0;
        }
    }

    printf("Enter the number of edges\n");
    scanf("%d",&e);

    for (i = 0;i < e;i++)
    {
        printf("Enter edge\n");
        scanf("%d",&u);
        scanf("%d",&v);

        G[u][v] = G[v][u] = 1;
    }

    printf("\n");

    for (i = 0;i < vertex;i++)
    {
        for (j = 0;j < vertex;j++)
        {
            printf("%d ",G[i][j]);
        }
        printf("\n");
    }

    while(1)
    {
        int choice;
        printf("\n1. BFS \n2. DFS \n3. Exit\n");
        printf("Enter your choice\n");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            BFS(G, vertex);
            break;
        case 2:
            DFS(G, vertex);
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
