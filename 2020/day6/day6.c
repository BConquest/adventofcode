#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int numberOfGroups = 0;
    int *ans = calloc(26, sizeof(int));
    int sumOfYes = 0;
    int numPeople = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        if (strcmp(line, "\n") == 0) {
            numberOfGroups += 1;
        }
    }

    fclose(fp);
    fp = fopen(argv[1], "r");
    int sumOfYes2 = 0, part2 = 0;
    int part1 = 0;
    for (int i = 0; i <= numberOfGroups;) {
        if ((read = getline(&line, &len, fp)) != -1) {
            for (size_t j = 0; j < len; j++) {
                if (line[j] == '\n') {
                    numPeople++;
                    break;
                }
                ans[line[j]-97] += 1;
            }

            if (strcmp(line, "\n") == 0) {
                i += 1;
                printf("Group %02d:%02d\t\t\t", i, numPeople);
                for (int j = 0; j < 26; j++) {
                    printf("%d,", ans[j]);
                    if (ans[j] != 0) {
                        sumOfYes += 1;
                    }
                    if (ans[j] == numPeople-1) {
                        sumOfYes2 += 1;
                    }
                }
                printf("\n");
                printf("\t\t%d\n", part2);
                part1 += sumOfYes;
                part2 += sumOfYes2;
                printf("Group %02d-> (%02d,%02d) yes\n", i, sumOfYes, sumOfYes2); 
                printf("\t\t%d\n\n", part2);
                sumOfYes = 0;
                sumOfYes2 = 0;
                numPeople = 0;
                ans = calloc(26, sizeof(int));
            }

        } else {
            i += 1;
            break;
        }
    }


    printf("Number of groups: %d\n", numberOfGroups);
    printf("Sum of Yes's:     %d\n", part1);
    printf("Sum of Yes's:     %d\n", part2);

    return EXIT_SUCCESS;
}
