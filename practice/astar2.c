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


int findMinF(int *g, int *h, int *visited, int n) {
    int min_f = INT_MAX;
    int min_node = -1;
    
    for(int j = 0; j < n; j++) {
        if(!visited[j] && g[j] != INT_MAX) {  
            int f = g[j] + h[j];
            if(f < min_f) {
                min_f = f;
                min_node = j;
            }
        }
    }
    return min_node;
}

void astar(struct Node **A, int n, int *h, int goal) {
    int *g = (int *)malloc(sizeof(int) * n);
    int *parent = (int *)malloc(sizeof(int) * n);
    int *visited = (int *)calloc(n, sizeof(int));
        
    for(int i = 0; i < n; i++) {
        g[i] = INT_MAX;
        parent[i] = -1;
    }
    g[0] = 0;    

    while(1) {        
        int current = findMinF(g, h, visited, n);        
        if(current == -1 || current == goal) {
            break;
        }     
        
        visited[current] = 1;        
        struct Node *temp = A[current];
        while(temp != NULL) {
            int neighbor = temp->ind;
            
            if(!visited[neighbor]) {
                int tentative_g = g[current] + temp->weight;
                
                if(tentative_g < g[neighbor]) {
                    parent[neighbor] = current;
                    g[neighbor] = tentative_g;
                }
            }
            temp = temp->next;
        }
    }

    if(g[goal] == INT_MAX) {
        printf("No path found\n");
    } else {
        printf("Path:\n");
        printPath(parent, goal);
        printf("\nThe cost of the path is %d\n", g[goal]);
    }

    free(g);
    free(parent);
    free(visited);    
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