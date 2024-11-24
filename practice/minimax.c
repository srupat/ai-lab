#include<stdio.h>
#include<stdlib.h>

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
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void play(char board[3][3], int x, int y, char symbol) {
    board[x][y] = symbol;
}

int isWon(char board[3][3]) {
    for(int row = 0; row < 3; row ++) {
        if(board[row][0] == board[row][1] && board[row][1] == board[row][2])
            return 1;
    }
    for(int col = 0; col < 3; col ++) {
        if(board[0][col] == board[1][col] && board[1][col] == board[2][col])
            return 1;
    }
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) return 1;
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) return 1;
    return 0;
}

int isMovesLeft(char board[3][3]) {
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(board[i][j] == '_') return 1;
        }
    }
    return 0;
}

int evaluate(char board[3][3]) {
    for(int row = 0; row < 3; row ++) {
        if(board[row][0] == board[row][1] && board[row][1] == board[row][2])
            if(board[row][0] == comp) return +10;
            else if(board[row][0] == human) return -10;
    }
    for(int col = 0; col < 3; col ++) {
        if(board[0][col] == board[1][col] && board[1][col] == board[2][col])
            if(board[0][col] == comp) return +10;
            else if(board[0][col] == human) return -10;
    }
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) 
        if(board[0][0] == comp) return +10;
        else if(board[0][0] == human) return -10;
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) 
        if(board[0][2] == comp) return +10;
        else if(board[0][2] == human) return -10;
    return 0;
}

int minimax(char board[3][3], int depth, int isMax) {
    int score = evaluate(board);

    if(score == +10 || score == -10) return score;
    if(!isMovesLeft(board)) return 0;

    if(isMax) {
        int best = -1000;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j] == '_') {
                    board[i][j] = comp;
                    int best = maxVal(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
    else {
        int best = 1000;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j] == '_') {
                    board[i][j] = human;
                    int best = minVal(best, minimax(board, depth + 1, !isMax));
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
    bestMove.x = -1;
    bestMove.y = -1;
    int score;

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(board[i][j] == '_') {
                board[i][j] = comp;
                score = minimax(board, 0, 0);
                board[i][j] = '_';
            }

            if(score > bestVal) {
                bestVal = score;
                bestMove.x = i;
                bestMove.y = j;
            }
        }
    }
    return bestMove;
}

int main() {
    char board[3][3];
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            board[i][j] = '_';
        }
    }

    for(int i=0;i<9;i++) {
        printBoard(board);
        if(i % 2 == 0) {
            printf("It is your turn. Please play O\n");
            int x, y;
            printf("Enter the x and y coordinates of where you want to play\n");
            scanf("%d %d", &x, &y);
            play(board, x, y, 'O');
            if(isWon(board)) {
                printf("Congratulations! You have won!\n");
                printBoard(board);
                return 0;
            }
        }
        else {
            printf("It is computer's turn.");
            struct Move bestMove = findBestMove(board);
            play(board, bestMove.x, bestMove.y, 'X');
            if(isWon(board)) {
                printf("The computer has won!\n");
                printBoard(board);
                return 0;
            }
        }
    }

    printf("Draw\n");
    printBoard(board);
    return 0;
}