#include <stdio.h>
#include <stdlib.h>

int
getVal(int array[4][4], int i, int j, int len, int height)
{
    if ((i < 0) || (i >= len) || (j < 0) || (j >= height)) {
        return 0;
    } else {
        return array[i][j];
    }
}

void
findMaxBlock(int array[4][4], int row, int col, int len, int height, int size, int cntarr[4][4], int *maxsize)
{
    if (row > len || col > height) {
        return;
    }

    /* current index being checked */
    cntarr[row][col] = 1;

    size++;
    if (size > *maxsize) {
        *maxsize = size;
    }

    // search in eight directions
    int direction[][2] = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};
    int i = 0;
    for (i = 0; i < 8; i++) {
        int newi = row + direction[i][0];
        int newj = col + direction[i][1];
        int val = getVal(array, newi, newj, len, height);

        if ((val > 0) && (cntarr[newi][newj] == 0)) {
            findMaxBlock(array, newi, newj, len, height, size, cntarr, maxsize);
        }
    }

    /* index no longer part of check */
    cntarr[row][col] = 0;
}

int
getMaxOnes(int array[4][4], int len, int height)
{
    int maxsize;
    int cntarr[len][height];

    int i = 0, j = 0;
    for (i = 0; i < len; i++) {
        for (j = 0; j < height; j++) {
            cntarr[i][j] = 0;
        }
    }

    for (i = 0; i < len; i++) {
        for (j = 0; j < height; j++) {
            if (array[i][j] == 1) {
                findMaxBlock(array, i, j, len, height, 0, cntarr, &maxsize);
            }
        }
    }
    return maxsize;
}

void
func(int **array, int len, int height)
{
    int i = 0, j = 0;
    for (i = 0; i < len; i++) {
        for (j = 0; j < height; j++) {
            printf("%d ", array[i][j]);
        }
    }
    printf("\n");
}

int
main(int argc, char *argv[])
{
//    int test[4][4] = {{1, 0, 1, 0},
//                      {0, 1, 1, 0},
//                      {0, 0, 1, 0},
//                      {1, 0, 0, 1}};
//    printf("Max chain of 1s = %d\n", getMaxOnes(test, 4, 4));

    int **test;
    int len = 4, height = 4, i = 0, j = 0;

    test = malloc(len * sizeof(*test));
    for (i = 0; i < len; i++)
    {
        test[i] = malloc(height * sizeof (*test[i]));
    }

    for (i = 0; i < len; i++) {
        for (j = 0; j < height; j++) {
            test[i][j] = i;
        }
    }
    func(test, len, height);
}
