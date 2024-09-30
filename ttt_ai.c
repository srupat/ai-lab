#include <stdio.h>

struct Move {
    int row, col;
};

char player = 'X', opponent = 'O';

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return 1;
    return 0;
}

void play(char board[3][3], char symbol, int i, int j) {
    board[i][j] = symbol;
}

int evaluate(char b[3][3]) {
    // Check rows
    for (int row = 0; row < 3; row++) {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == player)
                return +10;
            else if (b[row][0] == opponent)
                return -10;
        }
    }

    // Check columns
    for (int col = 0; col < 3; col++) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == player)
                return +10;
            else if (b[0][col] == opponent)
                return -10;
        }
    }

    // Check diagonals
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == player)
            return +10;
        else if (b[0][0] == opponent)
            return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == player)
            return +10;
        else if (b[0][2] == opponent)
            return -10;
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

int minimax(char board[3][3], int depth, int isMax) {
    int score = evaluate(board);

    // If Maximizer has won
    if (score == 10)
        return score;

    // If Minimizer has won
    if (score == -10)
        return score;

    // If no moves left and no winner
    if (!isMovesLeft(board))
        return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = player;
                    best = max(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = opponent;
                    best = min(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

struct Move findBestMove(char board[3][3]) {
    int bestVal = -1000;
    struct Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = player;
                int moveVal = minimax(board, 0, 0);
                board[i][j] = '_';
                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

int won(char board[3][3]) {
    // Check rows, columns, and diagonals
    if ((board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] != '_') ||
        (board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] != '_') ||
        (board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] != '_') ||
        (board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] != '_') ||
        (board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] != '_') ||
        (board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] != '_') ||
        (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '_') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '_')) {
        return 1;
    }
    return 0;
}

int main() {
    char board[3][3];
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = '_';
        }
    }

    int x, y;
    for(int i = 0; i < 9; i++) {
        printBoard(board);
        if(i % 2 == 0) {
            // Player's turn (O)
            printf("Play O\n");
            printf("Enter position x (0, 1, 2): ");
            scanf("%d", &x);
            printf("Enter position y (0, 1, 2): ");
            scanf("%d", &y);
            if(x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != '_') {
                printf("Invalid move. Try again.\n");
                i--;
                continue;
            }
            play(board, 'O', x, y);
            if(won(board)) {
                printBoard(board);
                printf("O won\n");
                return 0;
            }
        } else {
            // Computer's turn (X)
            struct Move bestMove = findBestMove(board);
            printf("The Optimal Move played by computer is :\n");
            printf("row: %d col: %d\n\n", bestMove.row, bestMove.col);
            play(board, 'X', bestMove.row, bestMove.col);
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
