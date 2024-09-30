#include <stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct queue {
    int front;
    int rear;
    int size;
    int * arr;
};

struct queue * createQueue(int n){
    struct queue * q = (struct queue *)malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    q->size = n;
    q->arr = (int *)malloc(n * sizeof(int));
    return q;
}

void enqueue(struct queue * q, int x){
    if(q->rear == q->size - 1){
        printf("Queue is full\n");
    } else {
        q->rear++;
        q->arr[q->rear] = x;
    }
}

int dequeue(struct queue * q){
    if(q->front == q->rear){
        printf("Queue is empty\n");
        return -1;
    } else {
        q->front++;
        return q->arr[q->front];
    }
}

void bfs(struct Node ** A, int n, int * visited, struct queue * q){
    if(q->front == q->rear){
        return;
    }
    int x = dequeue(q);
    visited[x] = 1;
    printf("%d ", x);
    struct Node * p = A[x];
    while(p != NULL){
        if(visited[p->data] == 0){
            enqueue(q, p->data);
            visited[p->data] = 1;
        }
        p = p->next;
    }
    bfs(A, n, visited, q);
}

void createAdjList(struct Node ** A, int n){
    for(int i = 0; i < n; i++){
        A[i] = NULL;
        int m;
        printf("Enter the number of vertices adjacent to vertex %d: ", i);
        scanf("%d", &m);
        printf("Enter the vertices adjacent to vertex %d: ", i);
        for(int j = 0; j < m; j++){
            int x;
            scanf("%d", &x);
            struct Node * temp = (struct Node *)malloc(sizeof(struct Node));
            temp->data = x;
            temp->next = NULL;
            if(A[i] == NULL){
                A[i] = temp;
            } else {
                struct Node * p = A[i];
                while(p->next != NULL){
                    p = p->next;
                }
                p->next = temp;
            }
        }
    }
}

void printAdjList(struct Node ** A, int n){
    for(int i = 0; i < n; i++){
        struct Node * p = A[i];
        printf("Vertices adjacent to vertex %d: ", i);
        while(p != NULL){
            printf("%d ", p->data);
            p = p->next;
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    struct Node ** A = (struct Node **)malloc(n * sizeof(struct Node *));
    createAdjList(A, n);
    // printAdjList(A, n);

    int * visited = (int *)calloc(n, sizeof(int));

    struct queue * q = createQueue(n);

    printf("BFS traversal: ");
    int start_vertex;
    printf("Enter the start vertex: ");
    scanf("%d", &start_vertex);
    enqueue(q, start_vertex);
    bfs(A, n, visited, q);
}