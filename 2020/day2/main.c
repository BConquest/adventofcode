#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int checkPassword(char *password, size_t size, int min, int max, char character) {
    int count = 0;
    for (size_t i = 0; i < size; i++) {
        if (password[i] == character) {
            count += 1;
        }
        if (count < min && password[i] == character) {
            printf("\033[34;40m%c", password[i]);
        } else if (count > max && password[i] == character) {
            printf("\033[31;40m%c", password[i]);
        } else if (count >= min && count <= max && password[i] == character) {
            printf("\033[32;40m%c", password[i]);
        } else {
            printf("\033[0m%c", password[i]);
        }
        printf("\033[0m");
        fflush(stdout);
        usleep((rand() % 1000) + 100);
    }
    printf("\033[0m");
    if (count >= min && count <= max) {
        return 1;
    } else {
        return 0;
    }
}

int checkPassword2(char *password, size_t size, int min, int max, char character) {
    int count = 0;
    for (size_t i = 0; i < size; i++) {
        if (password[i] == character && i == min-1) {
            if (count == 0) {
                printf("\033[32;40m%c", password[i]);
            } else {
                printf("\033[31;40m%c", password[i]);
            }
            count += 1;
        } else if (password[i] == character && i == max-1) {
            if (count == 0) {
                printf("\033[32;40m%c", password[i]);
            } else {
                printf("\033[31;40m%c", password[i]);
            }
            count += 1;
        } else {
            printf("\033[0m%c", password[i]);
        }
        printf("\033[0m");
        fflush(stdout);
        usleep((rand() % 1000) + 100);
    }
    printf("\033[0m");
    if (count == 1) {
        return 1;
    } else {
        return 0;
    }
}


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

    size_t maxPSize = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int correctPasswords = 0;
    int correctPasswords2 = 0;
    printf("\033[2J\033[0;0H");
    int lines = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        int min, max;
        char character;
        size_t size = 200;
        char *password = calloc(size, sizeof(char));

        sscanf(line, "%d-%d %c: %s\n", &min, &max, &character, password);

        size_t i = 0;
        size = 0;
        while(i < 200) {
            if (password[i] == '\0') {
                break;
            }
            size += 1;
            i++;
        }
        password = realloc(password, size*sizeof(char));

        if (size > maxPSize) {
            maxPSize = size;
        }
        free(password);
    }

    maxPSize += 4;
    fclose(fp);
    fp = fopen(argv[1], "r");

    while ((read = getline(&line, &len, fp)) != -1) {
        int min, max;
        char character;
        size_t size = maxPSize;
        char *password = malloc(size * sizeof(char));
        for (size_t i = 0; i < size; i++) {
            password[i] = ' ';
        }

        sscanf(line, "%d-%d %c: %s\n", &min, &max, &character, password);

        printf("%04d\t%3d -%3d (%c)\t", lines++, min, max, character); 
        int valid = checkPassword(password, size, min, max, character);
        if (valid) {
            correctPasswords += 1;
            printf(" \033[30;42m%4s\033[0m", "PASS");
        } else {
            printf(" \033[30;41m%4s\033[0m", "FAIL");
        }
        printf("\t");
        valid = checkPassword2(password, size, min, max, character);
        if (valid) {
            correctPasswords2 += 1;
            printf(" \033[30;42m%4s\033[0m", "PASS");
        } else {
            printf(" \033[30;41m%4s\033[0m", "FAIL");
        }
        printf("\033[0m\n");
        free(password);
        //usleep((rand() % 1200) + 100);
    }
    printf("CORRECT PASSWORDS: %d\n", correctPasswords);
    printf("CORRECT PASSWORDS: %d\n", correctPasswords2);

    if (line) {
        free(line);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
