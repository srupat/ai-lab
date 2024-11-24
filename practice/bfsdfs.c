#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int weight;
    struct Node *next;
};

struct Node *f = NULL;
struct Node *r = NULL;

void enqueue(int x) {
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));
    new->data = x;
    new->next = NULL;
    if (f == NULL) {
        f = r = new;
    } else {
        r->next = new;
        r = new;
    }
}

struct Node *dequeue() {
    if (f == NULL) {
        printf("Queue is empty\n");
        return NULL;
    }
    struct Node *temp = f;
    f = f->next;
    if (f == NULL) {
        r = NULL; 
    }
    return temp;
}

void priorityEnqueue(int x, int weight) {
    struct Node * new = (struct Node *)malloc(sizeof(struct Node));
    new->data = x;
    new->weight = weight;
    new->next = NULL;
    if(f == NULL) {
        f = r = new;
    }
    else {
        struct Node * temp = f;
        while(temp != NULL && temp->weight <= new->weight) {
            temp = temp->next;
        }
        if(temp == r) temp->next = new;
        else {
            new->next = temp->next;
            temp->next = new;
        }
    }
}

void bfs(struct Node **A, int n, int *visited) {
    printf("BFS Traversal: ");
    while (f != NULL) {
        struct Node *curr = dequeue();
        printf("%d ", curr->data);
        struct Node *temp = A[curr->data];
        while (temp != NULL) {
            if (!visited[temp->data]) {
                enqueue(temp->data);
                visited[temp->data] = 1;
            }
            temp = temp->next;
        }
        free(curr); 
    }
    printf("\n");
}

void dfs(struct Node **A, int n, int *visited, int x) {
    visited[x] = 1;
    printf("%d ", x);
    struct Node *temp = A[x];
    while (temp != NULL) {
        if (!visited[temp->data]) {
            dfs(A, n, visited, temp->data);
        }
        temp = temp->next;
    }
}

void createAdjList(struct Node **A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = NULL;
        int m;
        printf("Enter the number of nodes connected to node %d: ", i);
        scanf("%d", &m);
        printf("Enter the nodes connected to %d: ", i);
        for (int j = 0; j < m; j++) {
            int x;
            scanf("%d", &x);
            struct Node *new = (struct Node *)malloc(sizeof(struct Node));
            new->data = x;
            new->next = NULL;
            if (A[i] == NULL) {
                A[i] = new;
            } else {
                struct Node *temp = A[i];
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = new;
            }
        }
    }
}

void printAdjList(struct Node **A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d -> ", i);
        struct Node *temp = A[i];
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void freeAdjList(struct Node **A, int n) {
    for (int i = 0; i < n; i++) {
        struct Node *temp = A[i];
        while (temp != NULL) {
            struct Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
}

int main() {
    int n;
    printf("Enter the number of nodes in your graph: ");
    scanf("%d", &n);
    struct Node **A = (struct Node **)malloc(n * sizeof(struct Node *));
    int *visited = (int *)calloc(n, sizeof(int));

    createAdjList(A, n);
    printAdjList(A, n);

    printf("\n");
    visited[0] = 1; // Start BFS from node 0
    enqueue(0);
    bfs(A, n, visited);

    // Reset visited array
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
    printf("DFS Traversal: ");
    dfs(A, n, visited, 0);
    printf("\n");

    // Free memory
    freeAdjList(A, n);
    free(A);
    free(visited);

    return 0;
}
