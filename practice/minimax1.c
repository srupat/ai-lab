#include <stdio.h>
#include <stdlib.h>

struct Move {
    int x, y;
};

int maxVal(int a, int b) {
    return a > b ? a : b;
}

int minVal(int a, int b) {
    return a < b ? a : b;
}

char comp = 'X', human = 'O';

void printBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void play(char board[3][3], int x, int y, char symbol) {
    board[x][y] = symbol;
}

int isWon(char board[3][3]) {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] != '_' && board[row][0] == board[row][1] && board[row][1] == board[row][2])
            return 1;
    }
    for (int col = 0; col < 3; col++) {
        if (board[0][col] != '_' && board[0][col] == board[1][col] && board[1][col] == board[2][col])
            return 1;
    }
    if (board[0][0] != '_' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    if (board[0][2] != '_' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;
    return 0;
}

int isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_')
                return 1;
        }
    }
    return 0;
}

int evaluate(char board[3][3]) {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] != '_' && board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == comp)
                return +10;
            else if (board[row][0] == human)
                return -10;
        }
    }
    for (int col = 0; col < 3; col++) {
        if (board[0][col] != '_' && board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == comp)
                return +10;
            else if (board[0][col] == human)
                return -10;
        }
    }
    if (board[0][0] != '_' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == comp)
            return +10;
        else if (board[0][0] == human)
            return -10;
    }
    if (board[0][2] != '_' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == comp)
            return +10;
        else if (board[0][2] == human)
            return -10;
    }
    return 0;
}

int minimax(char board[3][3], int depth, int isMax) {
    int score = evaluate(board);

    if (score == +10 || score == -10)
        return score - depth; 
    if (!isMovesLeft(board))
        return 0;

    int best = isMax ? -1000 : 1000;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = isMax ? comp : human;
                int val = minimax(board, depth + 1, !isMax);
                best = isMax ? maxVal(best, val) : minVal(best, val);
                board[i][j] = '_';
            }
        }
    }
    return best;
}

struct Move findBestMove(char board[3][3]) {
    int bestVal = -1000;
    struct Move bestMove;
    bestMove.x = -1;
    bestMove.y = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = comp;
                int moveVal = minimax(board, 0, 0);
                board[i][j] = '_';

                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    bestMove.x = i;
                    bestMove.y = j;
                }
            }
        }
    }
    return bestMove;
}

int main() {
    char board[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '_';
        }
    }

    printf("Welcome to Tic-Tac-Toe!\n");
    for (int turn = 0; turn < 9; turn++) {
        printBoard(board);
        if (turn % 2 == 0) {
            printf("It is your turn. Please play 'O'.\n");
            int x, y;
            do {
                printf("Enter the row and column (0-2): ");
                scanf("%d %d", &x, &y);
            } while (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != '_');
            play(board, x, y, 'O');
            if (isWon(board)) {
                printf("Congratulations! You have won!\n");
                printBoard(board);
                return 0;
            }
        } else {
            printf("It is the computer's turn.\n");
            struct Move bestMove = findBestMove(board);
            play(board, bestMove.x, bestMove.y, 'X');
            if (isWon(board)) {
                printf("The computer has won!\n");
                printBoard(board);
                return 0;
            }
        }
        if (!isMovesLeft(board)) {
            printf("The game is a draw!\n");
            printBoard(board);
            return 0;
        }
    }

    printf("Draw\n");
    printBoard(board);
    return 0;
}
