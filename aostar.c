#include <stdio.h>
#include <stdlib.h>

#define INF 100000  

typedef struct Node {
    int id;                  
    int isAND;               
    struct Node** children;  
    int* cost;               
    int numChildren;         
    int heuristic;           
    int solved;              
    int costToReach;         
} Node;

Node* createNode(int id, int isAND, int heuristic, int numChildren) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = id;
    node->isAND = isAND;
    node->heuristic = heuristic;
    node->numChildren = numChildren;
    node->children = (Node**)malloc(numChildren * sizeof(Node*));
    node->cost = (int*)malloc(numChildren * sizeof(int));
    node->solved = 0;
    node->costToReach = INF;
    return node;
}

int aoStar(Node* node) {
    if (node->solved) {
        return node->costToReach;  
    }

    if (node->numChildren == 0) {
        node->solved = 1;
        return node->heuristic;
    }

    int totalCost = (node->isAND) ? 0 : INF;

    for (int i = 0; i < node->numChildren; i++) {
        int childCost = aoStar(node->children[i]) + node->cost[i];

        if (node->isAND) {
            totalCost += childCost;  
        } else {
            if (childCost < totalCost) {
                totalCost = childCost;  
            }
        }
    }

    node->costToReach = totalCost;
    node->solved = 1;
    return totalCost;
}

void addChildren(Node* parent, Node* children[], int cost[], int numChildren) {
    for (int i = 0; i < numChildren; i++) {
        parent->children[i] = children[i];
        parent->cost[i] = cost[i];
    }
}

int main() {
    Node* n0 = createNode(0, 0, 0, 2);  
    Node* n1 = createNode(1, 1, 0, 2);  
    Node* n2 = createNode(2, 0, 2, 0);  
    Node* n3 = createNode(3, 0, 3, 0);  
    Node* n4 = createNode(4, 0, 5, 0);  

    Node* n1Children[] = {n2, n3};      
    int n1Costs[] = {2, 3};          
    addChildren(n1, n1Children, n1Costs, 2);

    Node* n0Children[] = {n1, n4};      
    int n0Costs[] = {4, 5};             
    addChildren(n0, n0Children, n0Costs, 2);

    int solutionCost = aoStar(n0);

    printf("Solution cost: %d\n", solutionCost);

    free(n0->children); free(n0->cost); free(n0);
    free(n1->children); free(n1->cost); free(n1);
    free(n2->children); free(n2->cost); free(n2);
    free(n3->children); free(n3->cost); free(n3);
    free(n4->children); free(n4->cost); free(n4);

    return 0;
}
