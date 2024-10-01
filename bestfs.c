#include <stdio.h>
#include<stdlib.h>

struct Node * f = NULL;
struct Node * r = NULL;

struct Node {
    int val;
    int weight;
    struct Node* next;
};

void enqueue(int x, int weight) {
    struct Node * n = (struct Node*)malloc(sizeof(struct Node));
    if(n == NULL) printf("queue is full\n");
    else {
        n->val = x;
        n->weight = weight;
        n->next = NULL;
        if(f == NULL) {
            f = r = n;
        }
        else {
            struct Node * temp = f;
            struct Node * prev = NULL;
            while(temp != NULL && temp->weight < weight){
                prev = temp;
                temp = temp->next;
            }

            if(prev == NULL){
                n->next = f;
                f = n;
            } else {
                prev->next = n;
                n->next = temp;
                if(temp == NULL) r = n;
            }
        }
    }
}

int dequeue() {
    int a = -1;
    if(r == NULL) printf("queue is empty\n");
    else {
        struct Node * temp = f;
        a = temp->val;
        f = f->next;
        free(temp);
    }
    return a;
}

void bfs(struct Node ** A, int n, int * visited){
    if(f == NULL) {
        return;
    }
    int x = dequeue();
    visited[x] = 1;
    printf("%d ", x);
    struct Node * p = A[x];
    while(p != NULL){
        if(visited[p->val] == 0){
            enqueue(p->val, p->weight);
            visited[p->val] = 1;
        }
        p = p->next;
    }
    bfs(A, n, visited);
}

void createAdjList(struct Node ** A, int n){
    for(int i = 0; i < n; i++){
        A[i] = NULL;
        int m;
        printf("Enter the number of vertices adjacent to vertex %d: ", i);
        scanf("%d", &m);
        printf("Enter the vertices and their edge weights adjacent to vertex %d: ", i);
        for(int j = 0; j < m; j++){
            int x, weight;
            scanf("%d %d", &x, &weight);
            struct Node * temp = (struct Node *)malloc(sizeof(struct Node));
            temp->val = x;
            temp->weight = weight;
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
            printf("%d ", p->val);
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

    printf("BFS traversal: ");
    int start_vertex;
    printf("Enter the start vertex: ");
    scanf("%d", &start_vertex);
    enqueue(start_vertex, 0);
    bfs(A, n, visited);
}