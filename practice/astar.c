#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int data;
    int weight;
    struct Node *next;
};

void createAdjList(struct Node **A, int n) {
    for (int i = 0; i < n; i++) {
        int m;
        A[i] = NULL;
        printf("Enter the number of nodes connected to node %d: ", i);
        scanf("%d", &m);
        printf("Enter the vertex and weight of the nodes connected to node %d:\n", i);
        for (int j = 0; j < m; j++) {
            int x, w;
            scanf("%d %d", &x, &w);

            struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
            newNode->data = x;
            newNode->weight = w;
            newNode->next = NULL;

            if (A[i] == NULL) {
                A[i] = newNode;
            } else {
                struct Node *temp = A[i];
                while (temp->next != NULL) temp = temp->next;
                temp->next = newNode;
            }
        }
    }
}

void displayAdjList(struct Node **A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ->", i);
        struct Node *temp = A[i];
        while (temp != NULL) {
            printf(" (%d, %d)", temp->data, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

void printCostPath(int current, int *parent, int *g) {
    if (current == -1) return;

    printCostPath(parent[current], parent, g);
    printf("%d ", current);
}

void astar(struct Node **A, int n, int *h, int goal, int *g) {
    int *parent = (int *)calloc(n, sizeof(int));
    int *visited = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        g[i] = INT_MAX;
        parent[i] = -1;
    }
    g[0] = 0;

    for (int i = 0; i < n; i++) {
        int min_dist = INT_MAX;
        int current = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && g[j] + h[j] < min_dist) {
                min_dist = g[j] + h[j];
                current = j;
            }
        }

        if (current == -1) {
            printf("No path found.\n");
            return;
        }

        if (current == goal) {
            printf("Path: ");
            printCostPath(current, parent, g);
            printf("\nCost: %d\n", g[current]);
            return;
        }

        visited[current] = 1;

        struct Node *temp = A[current];
        while (temp != NULL) {
            if (!visited[temp->data]) {
                int new_dist = g[current] + temp->weight;
                if (new_dist < g[temp->data]) {
                    g[temp->data] = new_dist;
                    parent[temp->data] = current;
                }
            }
            temp = temp->next;
        }
    }
    printf("No path found.\n");
}

int main() {
    int n;
    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &n);

    struct Node **A = (struct Node **)malloc(n * sizeof(struct Node *));
    createAdjList(A, n);
    displayAdjList(A, n);

    int *g = (int *)malloc(sizeof(int) * n);
    int *h = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        printf("Enter the heuristic value (h) for node %d: ", i);
        scanf("%d", &h[i]);
    }

    int goal;
    printf("Enter the goal node: ");
    scanf("%d", &goal);

    astar(A, n, h, goal, g);

    free(g);
    free(h);
    free(A);
    return 0;
}
