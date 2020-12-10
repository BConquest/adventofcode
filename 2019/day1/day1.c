#include <stdio.h>
#include <stdlib.h>

int calculateFuel(int fuel) {
    return fuel/3 - 2;
}

int recursiveFuel(int fuel) {
    if (calculateFuel(fuel) <= 0) {
        return 0;
    } else {
        int next = calculateFuel(fuel);
        return next + recursiveFuel(next);
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

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int totalFuel = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        int i;
        int test = sscanf(line, "%d\n", &i);
        if (test == EOF) {
            perror("(WW) Skipping line");
            fprintf(stderr, "\"%s\"\n", line);
            continue;
        }

        int fuel = recursiveFuel(i);
        printf("mass: %15d\tfuel: %15d\n", i, fuel);
        totalFuel += fuel;
    }
    printf("total fuel: %d\n", totalFuel);

    if (line) {
        free(line);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
