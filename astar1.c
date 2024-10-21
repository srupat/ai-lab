#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int val;
    int cost;
    struct Node* next;
};

void createAdjList(struct Node** A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = NULL;
        int m;
        printf("Enter the number of vertices adjacent to vertex %d: ", i);
        scanf("%d", &m);
        printf("Enter the vertices and their costs adjacent to vertex %d: ", i);
        for (int j = 0; j < m; j++) {
            int x, c;
            scanf("%d %d", &x, &c);
            struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
            temp->val = x;
            temp->cost = c;
            temp->next = NULL;
            if (A[i] == NULL) {
                A[i] = temp;
            } else {
                struct Node* p = A[i];
                while (p->next != NULL) {
                    p = p->next;
                }
                p->next = temp;
            }
        }
    }
}

int getMinF(int* fScore, int* openSet, int n) {
    int min = INT_MAX;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (openSet[i] && fScore[i] < min) {
            min = fScore[i];
            index = i;
        }
    }
    return index;
}

void aStar(struct Node** A, int n, int* h, int start, int goal) {
    int* openSet = (int*)calloc(n, sizeof(int));
    int* closedSet = (int*)calloc(n, sizeof(int));
    int* gScore = (int*)malloc(n * sizeof(int));
    int* fScore = (int*)malloc(n * sizeof(int));
    int* cameFrom = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        gScore[i] = INT_MAX;
        fScore[i] = INT_MAX;
        cameFrom[i] = -1;
    }

    gScore[start] = 0;
    fScore[start] = h[start];
    openSet[start] = 1;

    while (1) {
        int current = getMinF(fScore, openSet, n);

        if (current == -1) break;
        if (current == goal) {
            printf("Path found: ");
            int temp = goal;
            while (temp != -1) {
                printf("%d ", temp);
                temp = cameFrom[temp];
            }
            printf("\n");
            return;
        }

        openSet[current] = 0;
        closedSet[current] = 1;

        struct Node* p = A[current];
        while (p != NULL) {
            if (closedSet[p->val]) {
                p = p->next;
                continue;
            }

            int tentative_gScore = gScore[current] + p->cost;
            if (!openSet[p->val]) {
                openSet[p->val] = 1;
            } else if (tentative_gScore >= gScore[p->val]) {
                p = p->next;
                continue;
            }

            cameFrom[p->val] = current;
            gScore[p->val] = tentative_gScore;
            fScore[p->val] = gScore[p->val] + h[p->val];

            p = p->next;
        }
    }

    printf("No path found\n");
}

int main() {
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    struct Node** A = (struct Node**)malloc(n * sizeof(struct Node*));
    createAdjList(A, n);

    int* h = (int*)malloc(n * sizeof(int));
    printf("Enter heuristic values for each vertex: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &h[i]);
    }

    int start, goal;
    printf("Enter start and goal vertices: ");
    scanf("%d %d", &start, &goal);

    aStar(A, n, h, start, goal);

    return 0;
}
