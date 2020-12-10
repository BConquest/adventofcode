#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int *getRow(int first, int last, char side) {
    int mid = (first + last) / 2;
    int isOdd = (first + last) % 2;
    int *arr = malloc(sizeof(int) * 2);

    if (side == 'F') {
        arr[0] = first;
        if (isOdd) {
            arr[1] = mid;
        } else {
            arr[1] = mid-1;
        }
    } else  {
        if (isOdd) {
            arr[0] = mid+1;
        } else {
            arr[0] = mid;
        }
        arr[1] = last;
    }
    return arr;
}

int *getCol(int first, int last, char side) {
    int mid = (first + last) / 2;
    int isOdd = (first + last) % 2;
    int *arr = malloc(sizeof(int) * 2);

    if (side == 'L') {
        arr[0] = first;
        if (isOdd) {
            arr[1] = mid;
        } else {
            arr[1] = mid-1;
        }
    } else  {
        if (isOdd) {
            arr[0] = mid+1;
        } else {
            arr[0] = mid;
        }
        arr[1] = last;
    }
    return arr;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./a.out <filename> <right> <down>");
        return EXIT_FAILURE;
    }

    FILE *fp;
    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        perror("(EE)");
        return EXIT_FAILURE;
    }

    int row = 128;
    int col = 8;
    int **seats = malloc(sizeof(int *) * row);
    for (size_t j = 0; j < row; j++) {
        seats[j] = malloc(sizeof(int) * col);
    }
/*
    for (size_t j = 0; j < row; j++){
        for (size_t k = 0; k < col; k++) {
            printf("%d", seats[j][k]);
        }
        printf("\n");
    }
*/
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int maxId = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        char *input = line;
        size_t i = 0;
        int *rows = malloc(sizeof(int) * 2);
        int *cols = malloc(sizeof(int) * 2);

        rows[0] = 0, rows[1] = row-1;
        cols[0] = 0, cols[1] = col-1;

        for (i = 0; i < strlen(input); i++) {
            if (input[i] == 'F' || input[i] == 'B') {
                rows = getRow(rows[0], rows[1], input[i]);
            }
            if (input[i] == 'L' || input[i] == 'R') {
                cols = getCol(cols[0], cols[1], input[i]);
            }
        }
        int id = rows[1] * col + cols[0];
        seats[rows[1]][cols[0]] = 1;
        //printf("F: %4d,%d4\tID: %5d\n", rows[1], cols[0], id);
        maxId = id > maxId ? id : maxId;
    }
    printf("Max ID: %d\n", maxId);
    fflush(stdout);
    for (size_t j = 0; j < row; j++) {
        for (size_t k = 0; k < col; k++) {
            if (seats[j][k-1] == 1 && seats[j][k] == 0 && seats[j][k+1]) {
                printf("Empty: %zu-%zu: ID: %5d\n", j, k, j * 8 + k);
            }
        }
    }

    if (line) {
        free(line);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
