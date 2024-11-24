#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct Node {
    int data;
    struct Node * next;
};

void createAdjList(struct Node ** A, int n) {
    for(int i=0;i<n;i++) {
        A[i] = NULL;
        int m;
        printf("Enter the number of vertices connected to node %d ", i);
        scanf("%d", &m);
        printf("Enter the nodes connected to %d", i);
        for(int j=0;j<m;j++) {
            int x;
            scanf("%d", &x);
            struct Node * new = (struct Node *)malloc(sizeof(struct Node));
            new->data = x;
            new->next = NULL;
            if(A[i] == NULL) {
                A[i] = new;
            }
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

void printAdjList(struct Node ** A, int n) {
    for(int i=0;i<n;i++) {
        printf("%d -> ", i);
        struct Node * temp = A[i];
        while(temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}


int isSafe(struct Node **A, int c, int v, int *color) {
    struct Node * temp = A[v];
    while(temp != NULL) {
        if(color[temp->data] == c) return 0;
        temp = temp->next;
    }
    return 1;
}

int graphColoringUtil(struct Node **A, int *color, int n, int v, int m) {
    if(v == n) return 1;
    for(int c=1;c<=m;c++) {
        if(isSafe(A, c, v, color)) {
            color[v] = c;
            if(graphColoringUtil(A, color, n, v+1, m)) return 1;
            color[v] = 0;
        }
    }
    return 0;
}

void graphColoring(struct Node **A, int n, int m) {
    int * color = (int *)calloc(n, sizeof(int));
    if(!graphColoringUtil(A,color,n,0,m)) {
        printf("such a configuration does not exist\n");
        return;
    }
    else {
        printf("Graph colored successfully with the following colors\n");
        for(int i=0;i<n;i++)
            printf("vertex %d -> color %d\n", i, color[i]);
    }
}

int main() {
    int n;
    printf("Enter the number of nodes ");
    scanf("%d", &n);
    int m;
    printf("Enter the number of unique colors ");
    scanf("%d", &m);
    struct Node ** A = (struct Node **)malloc(sizeof(struct Node *) * n);
    createAdjList(A, n);
    printAdjList(A, n);
    graphColoring(A, n, m);
    return -1;
}