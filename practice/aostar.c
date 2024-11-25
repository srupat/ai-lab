#include<stdio.h>
#include<stdlib.h>

#define inf 10000

struct Node {
    int id;
    int numChildren;
    struct Node ** children;
    int * cost;
    int heuristic;
    int isAnd;
    int costToReach;
    int solved;
};

struct Node * createNode(int id, int heuristic, int isAnd, int numChildren) {
    struct Node * new = (struct Node *)malloc(sizeof(struct Node));
    new->id = id;
    new->heuristic = heuristic;
    new->isAnd = isAnd;
    new->numChildren = numChildren;
    new->children = (struct Node **)malloc(numChildren * sizeof(struct Node *));
    new->cost = (int *)malloc(numChildren * sizeof(int));
    new->solved = 0;
    new->costToReach = inf;
    return new;
}

int aostar(struct Node * node) {
    if(node->solved) return node->costToReach;
    if(node->numChildren == 0) {
        node->solved = 1;
        return node->heuristic;
    }
    int totalCost = node->isAnd ? 0 : inf;
    for(int i=0;i<node->numChildren;i++) {
        int childCost = aostar(node->children[i]) + node->cost[i];

        if(node->isAnd) totalCost += childCost;
        else {
            if(childCost < totalCost) totalCost = childCost;
        }
    }

    node->solved = 1;
    node->costToReach = totalCost;
    return totalCost;
}

void addChildren(struct Node * parent, struct Node ** children, int * cost, int numChildren) {
    for(int i=0;i<numChildren;i++) {
        parent->children[i] = children[i];
        parent->cost[i] = cost[i];
    }
}

int main() {
    struct Node* n0 = createNode(0, 0, 0, 2);  
    struct Node* n1 = createNode(1, 1, 0, 2);  
    struct Node* n2 = createNode(2, 0, 2, 0);  
    struct Node* n3 = createNode(3, 0, 3, 0);  
    struct Node* n4 = createNode(4, 0, 5, 0);  

    struct Node* n1Children[] = {n2, n3};      
    int n1Costs[] = {2, 3};          
    addChildren(n1, n1Children, n1Costs, 2);

    struct Node* n0Children[] = {n1, n4};      
    int n0Costs[] = {4, 5};             
    addChildren(n0, n0Children, n0Costs, 2);

    int solutionCost = aostar(n0);

    printf("Solution cost: %d\n", solutionCost);
}

