#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define WIDTH 5
#define HEIGHT 5

struct Node {
    int x;
    int y;
};

int manhattanDistance(struct Node a, struct Node b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int isValid(struct Node node) {
    return node.x >= 0 && node.x < WIDTH && node.y >= 0 && node.y < HEIGHT;
}

void aStar(struct Node start, struct Node end, int grid[WIDTH][HEIGHT]) {
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    int openList[WIDTH][HEIGHT] = {0};
    int closedList[WIDTH][HEIGHT] = {0};

    int g[WIDTH][HEIGHT];
    int f[WIDTH][HEIGHT];

    for(int i=0;i<WIDTH;i++) {
        for(int j=0;j<HEIGHT;j++) {
            g[i][j] = INT_MAX;
            f[i][j] = INT_MAX;
        }
    }

    g[start.x][start.y] = 0;
    f[start.x][start.y] = manhattanDistance(start, end);
    struct Node parent[WIDTH][HEIGHT];

    openList[start.x][start.y] = 1;

    while(1) {
        int minF = INT_MAX;
        struct Node current;
        int found = 0;

        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                if (openList[i][j] && f[i][j] < minF) {
                    minF = f[i][j];
                    current = (struct Node){i, j};
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("Path not found\n");
            return;
        }

        if(current.x == end.x && current.y == end.y) {
            printf("Goal reached\n");

            struct Node path[WIDTH * HEIGHT];
            int pathlength = 0;
            struct Node temp = current;

            while(temp.x != start.x || temp.y != start.y) {
                path[pathlength++] = temp;
                temp = parent[temp.x][temp.y];
            }
            path[pathlength++] = start;

            for(int i=pathlength-1;i>=0;i--) {
                printf("(%d, %d) ", path[i].x, path[i].y);
                if(i > 0) {
                    printf("-> ");
                }
            }
            printf("\n");
            return;
        }

        openList[current.x][current.y] = 0;
        closedList[current.x][current.y] = 1;

        for(int i=0;i<4;i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            struct Node neighbour = (struct Node){nx, ny};
            if(isValid(neighbour) && !closedList[nx][ny] && grid[nx][ny] != 1) {
                int newG = g[current.x][current.y] + 1;
                int h = manhattanDistance(neighbour, end);
                int newF = newG + h;

                if(newF < f[nx][ny]) {
                    g[nx][ny] = newG;
                    f[nx][ny] = newF;
                    openList[nx][ny] = 1;
                    parent[nx][ny] = current;
                }
            }
        }
    }
}

int main() {
    int grid[WIDTH][HEIGHT] = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    struct Node start = (struct Node){0, 0};
    struct Node end = (struct Node){4, 4};

    aStar(start, end, grid);

    return 0;
}


