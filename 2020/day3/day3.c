#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./a.out <filename> <right> <down>");
        return EXIT_FAILURE;
    }

    int right = atoi(argv[2]);
    int down = atoi(argv[3]);

    FILE *fp;
    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        perror("(EE)");
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    size_t numberLines = 0;
    size_t lengthLines = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        numberLines += 1;
        for (size_t i = 0; i < len; i++) {
            if (line[i] == '\n') {
                if (i > lengthLines) {
                    lengthLines = i;
                }
                break;
            }
        }
    }
    printf("lengthLines: %5zu\n", lengthLines);
    printf("numberLines: %5zu\n", numberLines);

    fclose(fp);
    fp = fopen(argv[1], "r");
    char **map = calloc(numberLines, sizeof(char *));
    for (size_t i = 0; i < numberLines; i++) {
        map[i] = calloc(lengthLines, sizeof(char));
    }

    for (size_t i = 0; i < numberLines; i++) {
        if ((read = getline(&line, &len, fp)) != -1) {
            for (size_t j = 0; j < lengthLines; j++) {
                map[i][j] = line[j];
            }
        }
    }


    size_t k = 0, l = 0;
    int treeHitter = 0;
    while (k < numberLines) {
        if (map[k][l] == '#') {
            treeHitter += 1;
            map[k][l] = 'X';
        } else {
            map[k][l] = 'O';
        }
        k += down;
        l = (l + right) % lengthLines;
    }

    printf("\u250C");
    /* start at negative 2 to account for the borders */
    for(size_t i = 0; i < (lengthLines+2); i++) {
        printf("\u2500");
    }
    printf("\u2510\n");

    for (size_t i = 0; i < numberLines; i++) {
        int totalTime = 1000000;
        printf("\033[0m\u2502 ");
        for (size_t j = 0; j < lengthLines; j++) {
            register char c = map[i][j];
            if (c == '#') {
                printf("\033[32m\u234b");
            } else if (c == 'X') {
                printf("\033[31m\u25cf");
            } else if (c == 'O') {
                printf("\033[34m\u25cb");
            } else {
                printf("\033[0m ");
            }
            fflush(stdout);
            int sleepTime = 0; //rand() % (totalTime/5);
            totalTime = totalTime - sleepTime;
            usleep(sleepTime);
        }
        printf(" \033[0m\u2502");
        printf("\n");
    }
    
    printf("\u2514");
    /* start at negative 2 to account for the borders */
    for(size_t i = 0; i < (lengthLines+2); i++) {
        printf("\u2500");
    }
    printf("\u2518\n");

    printf("%d\n", treeHitter);
    for (size_t i = 0; i < numberLines; i++) {
        free(map[i]);
    }
    free(map);
    if (line) {
        free(line);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
