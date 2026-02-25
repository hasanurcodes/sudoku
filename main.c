#include <stdio.h>

int board[9][9];

int initializeBoard(char fname[64]);
void printBoard();
int solve(int x, int y);
int placeable(int k, int x, int y);

int main()
{
    if (initializeBoard("input.txt") == 1) {
        printf("Failed to set up the board!\nPlease check input.txt file.");
        return 1;
    }
    solve(0, 0);
    printBoard();
    return 0;
}

int initializeBoard(char fname[64]) {
    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        printf("No file found\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (fscanf(file, "%1d", &board[i][j]) != 1) {
                printf("Error: Matrix file is missing data at row %d, col %d\n", i, j);
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

void printBoard() {
    for (int i = 0; i < 9; i++) {
        if (i != 0 && i % 3 == 0) printf("---+---+---\n");
        for (int j = 0; j < 9; j++) {
            if (j != 0 && j % 3 == 0) printf("|");
            printf("%d", board[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

int solve(int x, int y) {
    if (x > 8) return 0;
    if (board[x][y] == 0) {
        for (int num = 1; num < 10; num++) {
            if (placeable(num, x, y) == 0) {
                board[x][y] = num;
                int tempX = x;
                int tempY = y + 1;
                if (tempY > 8) {
                    tempY %= 9;
                    tempX += 1;
                }
                if (solve(tempX, tempY) == 0) return 0;
                board[x][y] = 0;
            }
        }
    } else {
        int tempX = x;
        int tempY = y + 1;
        if (tempY > 8) {
            tempY %= 9;
            tempX += 1;
        }
        if (solve(tempX, tempY) == 0) return 0;
    }
    return 1;
}

int placeable(int num, int x, int y) {
    for (int tx = x; tx > -1; tx--) {
        if (board[tx][y] == num) {
            return 1;
        }
    }for (int tx = x; tx < 9; tx++) {
        if (board[tx][y] == num) {
            return 1;
        }
    }
    for (int ty = y; ty > -1; ty--) {
        if (board[x][ty] == num) {
            return 1;
        }
    }
    for (int ty = y; ty < 9; ty++) {
        if (board[x][ty] == num) {
            return 1;
        }
    }

    int startRow = (x / 3) * 3;
    int startCol = (y / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == num) {
                return 1;
            }
        }
    }
    return 0;
}
