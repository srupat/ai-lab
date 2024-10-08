#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node* next;
};

void createAdjList(struct Node ** A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = NULL;
        int m;
        printf("Enter the number of vertices adjacent to vertex %d: ", i);
        scanf("%d", &m);
        printf("Enter the vertices adjacent to vertex %d: ", i);
        for (int j = 0; j < m; j++) {
            int x;
            scanf("%d", &x);
            struct Node * temp = (struct Node *)malloc(sizeof(struct Node));
            temp->val = x;
            temp->next = NULL;
            if (A[i] == NULL) {
                A[i] = temp;
            } else {
                struct Node * p = A[i];
                while (p->next != NULL) {
                    p = p->next;
                }
                p->next = temp;
            }
        }
    }
}

void printAdjList(struct Node ** A, int n) {
    for (int i = 0; i < n; i++) {
        struct Node * p = A[i];
        printf("Vertices adjacent to vertex %d: ", i);
        while (p != NULL) {
            printf("%d ", p->val);
            p = p->next;
        }
        printf("\n");
    }
}

int isSafe(struct Node ** A, int v, int color[], int c) {
    struct Node * p = A[v];
    while (p != NULL) {
        if (color[p->val] == c) {
            return 0; 
        }
        p = p->next;
    }
    return 1;
}

int graphColoringUtil(struct Node ** A, int n, int m, int color[], int v) {
    if (v == n) {
        return 1; 
    }

    for (int c = 1; c <= m; c++) {
        if (isSafe(A, v, color, c)) {
            color[v] = c; 

            if (graphColoringUtil(A, n, m, color, v + 1)) {
                return 1;
            }

            color[v] = 0;
        }
    }

    return 0;
}

int graphColoring(struct Node ** A, int n, int m) {
    int * color = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        color[i] = 0;
    }

    if (graphColoringUtil(A, n, m, color, 0) == 0) {
        printf("Solution does not exist\n");
        return 0;
    }

    printf("Solution exists with the following coloring:\n");
    for (int i = 0; i < n; i++) {
        printf("Vertex %d --> Color %d\n", i, color[i]);
    }

    free(color);
    return 1;
}

int main() {
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    struct Node ** A = (struct Node **)malloc(n * sizeof(struct Node *));
    createAdjList(A, n);
    // printAdjList(A, n); 

    int m = 4; 

    graphColoring(A, n, m);

    for (int i = 0; i < n; i++) {
        struct Node * temp = A[i];
        while (temp != NULL) {
            struct Node * next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(A);

    return 0;
}
