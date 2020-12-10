#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./a.out <filename>");
        return EXIT_FAILURE;
    }

    FILE *fp;
    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        perror("(EE)");
        return EXIT_FAILURE;
    }

    size_t maxSize = 4;
    size_t curSize = 0;
    int *array = calloc(maxSize, sizeof(int)); 

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        size_t newSize = 0;
        for (size_t j = 0; j < len; j++) {
            if (line[j] == '\n') {
                break;
            }
            if (line[j] == ',') {
                newSize++;
            }
        }
        len = ++newSize;

        for (size_t j = 0; j < len; j++) {
            char *token = strtok(line, ",");
            do {
                array[curSize] = atoi(token);
                if (curSize + 1 == maxSize) {
                    maxSize *= 2;
                    array = realloc(array, sizeof(int)*maxSize);
                }
                
                curSize++;

                token = strtok(NULL, ",\n");
            } while (token != NULL);
        }
    }
    array = realloc(array, sizeof(int)*curSize);
    int *array2 = calloc(curSize, sizeof(int));

    for (int k = 0; k < 100; k++) {
        for (int l = 0; l < 100; l++) {
            for (size_t i = 0; i < len; i++) {
                array2[i] = array[i];
            }

            array2[1] = k;
            array2[2] = l;

            for (size_t i = 0; i < len; i += 4) {
                int opcode = array2[i];
                int pos1 = array2[i+1];
                int pos2 = array2[i+2];
                int pos3 = array2[i+3];

                if (opcode == 1) {
                    printf("+ ");
                    array2[pos3] = array2[pos1] + array2[pos2];
                } else if (opcode == 2) {
                    printf("* ");
                    array2[pos3] = array2[pos1] * array2[pos2];
                } else if (opcode == 99) {
                    break;
                } else {
                    fprintf(stderr, "(WW) Invalid opcode");
                }

                printf("POS1: %5d, POS2: %5d, POS3: %5d, NEW POS3: %15d\n",
                        pos1, pos2, pos3, array2[pos3]);
            }

            printf("ANS1: %5d\n", array2[0]);
            printf("ANS2: %5d\n", 100*array2[1]+array2[2]);
        }
    }

    free(array);
    free(array2);
    if (line) {
        free(line);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
