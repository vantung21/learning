#include <stdio.h>

char board[3][3];

void initBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void printBoard() {
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
}

int checkWin(char player) {
    for (int i = 0; i < 3; i++)
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return 1;
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return 1;
    return 0;
}

int main() {
    int x, y, turn = 0;
    char player;
    initBoard();

    while (1) {
        printBoard();
        player = turn % 2 == 0 ? 'X' : 'O';
        printf("Player %c, enter row and column (0-2): ", player);
        scanf("%d %d", &x, &y);

        if (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != ' ') {
            printf("Invalid move!\n");
            continue;
        }

        board[x][y] = player;
        if (checkWin(player)) {
            printBoard();
            printf("Player %c wins!\n", player);
            break;
        }

        turn++;
        if (turn == 9) {
            printBoard();
            printf("It's a draw!\n");
            break;
        }
    }
    return 0;
}
