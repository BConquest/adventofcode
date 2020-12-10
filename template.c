#include <stdio.h>
#include <stdlib.h>

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

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        int test = sscanf(line, "", );

        if (test == EOF) {
            perror("(WW) Skipping line");
            fprintf(stderr, "\"%s\"\n", line);
            continue;
        }

    }



    if (line) {
        free(line);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
