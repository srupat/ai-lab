#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    int weight;
    struct Node* next;
};

void displayAdjMatrix(int ** G, int n)
{
    printf("The matrix is as follows\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d  ",G[i][j]);
        }
        printf("\n");
    }
}

void displayAdjList(struct Node * A[],int n)
{
    printf("The adjacency list is as follows\n");
    for(int i=0;i<n;i++)
    {
        struct Node * temp = A[i];
        while(temp!=NULL)
        {
            printf("%d | ",temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void createAdjList(struct Node* A[], int n) 
{
    char ch;
    int num,weight;
    for (int i = 0; i < n; i++) {
        A[i] = (struct Node*)malloc(sizeof(struct Node));
        A[i]->data = i;  
        A[i]->next = NULL;
    }
    for (int i = 0; i < n; i++) 
    {
        printf("Is there any node connected to node %d [y/n]\n", i);
        scanf(" %c", &ch);
        while (ch == 'y') 
        {
            printf("Enter the connected node (vertex number)\n");
            scanf("%d", &num);

            printf("Enter the weight between %d and %d\n",i,num);
            scanf("%d",&weight);

            struct Node* ptr = (struct Node*)malloc(sizeof(struct Node));
            struct Node* temp = A[i]->next;

            ptr->data = num;
            ptr->weight = weight;
            ptr->next = NULL;

            if (A[i]->next == NULL) 
            {
                A[i]->next = ptr;
            } 
            else 
            {
                while (temp->next != NULL) 
                {
                    temp = temp->next;
                }

                temp->next = ptr;
            }
            printf("Do you wish to continue?[y/n]\n");
            scanf(" %c", &ch);
        }
    }
    displayAdjList(A,n);
}

void createAdjMatrix(int** G, int n)
{
    int bit;
    int weight;
    for(int j = 0;j<n;j++)
    {
        for(int k=0;k<n;k++)
        {
            if(j==k) 
            {
                G[j][k] = 99;
                continue;
            }
            printf("Enter 1 if there exists an edge from %d to %d\t",j,k);
            scanf("%d",&bit);
            if(bit==1) 
            {
                printf("Enter the weight of the edge from %d to %d\t",j,k);
                scanf("%d",&weight);
                G[j][k] = weight;
            }
            else G[j][k] = 99;            
        }
    }
    displayAdjMatrix(G,n);
}

void Djikstra_adj_mat(int ** G, int n)
{
    int * previous_node = (int *)calloc(n, sizeof(int));
    int * shortest_distance = (int *)calloc(n, sizeof(int));
    int * visited = (int *)calloc(n, sizeof(int));

    for(int i = 0;i<n;i++)
    {
        if(i==0)
        {
            shortest_distance[i] = 0;
        }
        else shortest_distance[i] = 99;
    }
    
    for(int i = 0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(visited[j]!=1 && G[i][j]!=99 && G[i][j]<shortest_distance[j])
            {
                shortest_distance[j] = shortest_distance[i] + G[i][j];
                previous_node[j] = i;
            }

        }
        visited[i] = 1;
    }

    for(int i = 0;i<n;i++)
    {
        printf("node : %d\tshortest distance : %d\tprevious node : %d\t\n", i, shortest_distance[i], previous_node[i]);
    }
}

void Djikstra_adj_list(struct Node **A, int n)
{
    int * previous_node = (int *)calloc(n, sizeof(int));
    int * shortest_distance = (int *)calloc(n, sizeof(int));
    int * visited = (int *)calloc(n, sizeof(int));
    int current_node = -1;

    for(int i = 0;i<n;i++)
    {
        if(i==0)
        {
            shortest_distance[i] = 0;
        }
        else shortest_distance[i] = 99;
    }

    for(int i =0;i<n;i++)
    {
        struct Node * temp = A[i]->next;
        while(temp!=NULL)
        {
            if(visited[temp->data]!=1 && temp->weight<shortest_distance[temp->data])
            {
                shortest_distance[temp->data] = shortest_distance[i] + temp->weight;
                previous_node[temp->data] = i;
                current_node = temp->data;
            }
            temp = temp->next;
        }
        visited[current_node] = 1;
    }

    for(int i = 0;i<n;i++)
    {
        printf("node : %d\tshortest distance : %d\tprevious node : %d\t\n", A[i]->data, shortest_distance[i], previous_node[i]);
    }
}

int main()
{
    int n,ch;
    printf("Enter the number of vertices\n");
    scanf("%d", &n);

    printf("Adjacency matrix or adjacency list? enter 1 or 2");
    scanf("%d",&ch);

    if (ch==1)
    {
        int ** G;
        G = (int **)calloc(n, sizeof(int *));
        for(int i=0;i<n;i++)
        {
            G[i] = (int*)calloc(n, sizeof(int));
        }
        createAdjMatrix(G,n);
        printf("The minimum cost spanning tree using Djikstra's algorithm and adjancency matrix is \n");
        Djikstra_adj_mat(G,n);
    }

    else 
    {
        struct Node** A = (struct Node**)malloc(sizeof(struct Node*) * n);
        createAdjList(A, n);
        printf("The minimum cost spanning tree using Djikstra's algorithm and adjancency list is \n");
        Djikstra_adj_list(A,n);
    }
}