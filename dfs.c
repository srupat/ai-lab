#include <stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

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

void dfs(struct Node ** A, int n, int * visited, int x){
    visited[x] = 1;
    printf("%d ", x);
    struct Node * p = A[x];
    while(p != NULL){
        if(visited[p->data] == 0){
            dfs(A, n, visited, p->data);
        }
        p = p->next;
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

    printf("DFS Traversal: ");
    dfs(A, n, visited, 0);
}