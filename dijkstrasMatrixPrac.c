#include <stdio.h>
#include <stdlib.h>

int findMinDist(int dist[10], int visited[10], int v)
{
    int min = 999;
    int index;

    for (int i = 0;i < v;i++)
    {
        if (visited[i] == 0 && dist[i] < min)
        {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void display(int dist[10], int v)
{
    printf("Vertex\t Distance from source\n");

    for (int i = 0;i < v;i++)
    {
        printf("%d\t %d\n",i, dist[i]);
    }
}

void Dijkstras(int G[10][10], int src, int v)
{
    int dist[10];
    int visited[10];
    int u;

    for (int i = 0;i < v;i++)
    {
        dist[i] = 999;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int i = 0;i < v - 1;i++)
    {
        u = findMinDist(dist, visited, v);

        visited[u] = 1;

        for (int j = 0;j < v;j++)
        {
            if (visited[j] == 0 && G[u][j] && dist[u] != 999 && dist[u] + G[u][j] < dist[j])
            {
                dist[j] = G[u][j] + dist[u];
            }
        }
    }

    display(dist, v);
}

int main()
{
    int G[10][10], vertex, e, i, j, u, v, weight, src;

    printf("Enter number of vertices\n");
    scanf("%d",&vertex);

    for (i = 0;i < vertex;i++)
    {
        for (j = 0;j < vertex;j++)
        {
            G[i][j] = 9999;
        }
    }

    printf("Enter the number of edges\n");
    scanf("%d",&e);

    for (i = 0;i < e;i++)
    {
        printf("Enter edge\n");
        scanf("%d",&u);
        scanf("%d",&v);

        printf("Enter weight\n");
        scanf("%d",&weight);

        G[u][v] = G[v][u] = weight;
    }

    for (int k = 0;k < vertex;k++)
    {
        for (int l = 0;l < vertex;l++)
        {
            printf("%d ",G[k][l]);
        }
        printf("\n");
    }

    printf("Enter starting vertex\n");
    scanf("%d",&src);

    Dijkstras(G, src, vertex);
}
