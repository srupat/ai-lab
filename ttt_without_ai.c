#include <stdio.h>
#include <stdlib.h>

void play(char board[3][3], char symbol, int i, int j) {
    board[i][j] = symbol;
}

int won(char board[3][3]) {
    // Check rows, columns, and diagonals
    if((board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] != '-') ||
       (board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] != '-') ||
       (board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] != '-') ||
       (board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] != '-') ||
       (board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] != '-') ||
       (board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] != '-') ||
       (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '-') ||
       (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '-')) {
        return 1;
    }
    return 0;
}

void printBoard(char board[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char board[3][3];
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = '-';
        }
    }

    int x, y;
    for(int i = 0; i < 9; i++) {
        if(i % 2 == 0) {
            printf("Play O\n");
        } else {
            printf("Play X\n");
        }
        printBoard(board);
        printf("Enter position x (0, 1, 2): ");
        scanf("%d", &x);
        printf("Enter position y (0, 1, 2): ");
        scanf("%d", &y);

        if(x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != '-') {
            printf("Invalid move. Try again.\n");
            i--;
            continue;
        }

        if(i % 2 == 0) {
            play(board, 'O', x, y);
            if(won(board)) {
                printBoard(board);
                printf("O won\n");
                return 0;
            }
        } else {
            play(board, 'X', x, y);
            if(won(board)) {
                printBoard(board);
                printf("X won\n");
                return 0;
            }
        }
    }

    printBoard(board);
    printf("Draw\n");
    return 0;
}
