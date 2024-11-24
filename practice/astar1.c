#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct Node {
    int ind;
    int weight;
    struct Node * next;
};

void createAdjList(struct Node ** A, int n) {
    for(int i=0;i<n;i++) {
        A[i] = NULL;
        int m;
        printf("Enter the number of nodes connected to %d ", i);
        scanf("%d", &m);
        for(int j=0;j<m;j++) {
            int x, w;
            printf("Enter the data and weight of the node\n");
            scanf("%d %d", &x, &w);
            struct Node * new = (struct Node*)malloc(sizeof(struct Node));
            new->ind = x;
            new->weight = w;
            new->next = NULL;
            if(A[i] == NULL) A[i] = new;
            else {
                struct Node * temp = A[i];
                while(temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = new;
            }
        }
    }
}

void printAdjList(struct Node **A, int n) {
    for(int i=0;i<n;i++) {
        printf("%d -> ", i);
        struct Node * temp = A[i];
        while(temp != NULL) {
            printf("%d ", temp->ind);
            temp = temp->next;
        }
        printf("\n");
    }
}

void printPath(int * parent, int current) {
    if(current == -1) return;
    printPath(parent, parent[current]);
    printf("%d ", current);
}

void astar(struct Node **A, int n, int *h, int goal) {
    int *g = (int *)malloc(sizeof(int) * n);
    int *parent = (int *)malloc(sizeof(int) * n);
    int *visited = (int *)calloc(n, sizeof(int));

    for(int i=0;i<n;i++) {
        g[i] = INT_MAX;
        parent[i] = -1;
    }
    g[0] = 0;

    for(int i=0;i<n;i++) {
        int min_dist = INT_MAX;
        int current = -1;

        for(int j=0;j<n;j++) {
            if(!visited[j] && g[j] + h[j] < min_dist) {
                min_dist = g[j] + h[j];
                current = j;
            }
        }

        if(current == -1) break;
        
        if(current == goal) {
            printf("Path:\n");
            printPath(parent, current);
            printf("The cost of the path is %d", g[current]);
            return;
        }

        visited[current] = 1;

        struct Node * temp = A[current];
        while(temp != NULL) {
            if(!visited[temp->ind] && g[current] + temp->weight < g[temp->ind]) {
                g[temp->ind] = g[current] + temp->weight;
                parent[temp->ind] = current;
            }
            temp = temp->next;
        }
    }

    if (!visited[goal]) {
    printf("No path found\n");
    }
}

int main() {
    int n; 
    printf("Enter the number of nodes present in the graph\n");
    scanf("%d", &n);
    struct Node ** A = (struct Node **)malloc(sizeof(struct Node*) * n);
    createAdjList(A, n);
    printAdjList(A, n);
    int *h = (int *)malloc(sizeof(int) * n);
    printf("Enter the heuristic values for %d nodes\n", n);
    for(int i=0;i<n;i++){
        scanf("%d", &h[i]);
    }
    int goal;
    printf("Enter the goal node\n");
    scanf("%d", &goal);
    astar(A, n, h, goal);
    return -1;
}