#include <stdio.h>
#include <stdlib.h>

int getNumLines(FILE *);

int main(int argc, char *argv[]) {

    FILE *fp, *fpp;
    
    fp = fopen(argv[1], "r");
    fpp = fopen(argv[1], "r");
    if (fp == NULL || fpp == NULL) {
        perror("Error! opening file");
        return EXIT_FAILURE;
    }

    int size = getNumLines(fp);
    int *invoice;

    invoice = malloc(sizeof(int) * size);

    if (invoice == NULL) {
        perror("Error mallocing");
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int i = 0;
    while ((read = getline(&line, &len, fpp)) != -1) {
        invoice[i++] = atoi(line);
        printf("%s\n", line);
    }
    fclose(fp);
  
    int flag = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            printf("%5d + %5d = %5d\t", invoice[i], invoice[j], invoice[i]+invoice[j]);
            printf("%5d * %5d = %5d\n", invoice[i], invoice[j], invoice[i]*invoice[j]);
            if (invoice[i] + invoice[j] == 2020) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            break;
        }
    }

    free(invoice);
    return EXIT_SUCCESS;
}

int getNumLines(FILE *fp) {
    int numLines = 0;
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        numLines++;
    }
    
    return numLines;
}
