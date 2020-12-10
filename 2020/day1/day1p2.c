#include <stdio.h>
#include <stdlib.h>

/*
 * findSum
 *
 * int -> target
 * int -> amount
 * int -> length
 * int -> array
 */
int findSum(int, int, int, int *); 

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: ./a.out <filename> n\n");
        return EXIT_FAILURE;
    }

    FILE *fp;

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        perror("Error! opening file");
        return EXIT_FAILURE;
    }

    size_t size = 4;
    int *invoice;

    invoice = malloc(sizeof(int) * (size + 1));

    if (invoice == NULL) {
        perror("Error mallocing");
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if ((i>0) && (size_t)i == size-1) {
            size *= 2;
            invoice = realloc(invoice, sizeof(int) * size);
            if (invoice == NULL) {
                perror ("Error Mallocing");
                return EXIT_FAILURE;
            }
        }
        invoice[i] = atoi(line);
        i += 1;
    }

    size = i-1;
    invoice = realloc(invoice, sizeof(int)*size);
    if (invoice == NULL) {
        perror ("Error Mallocing");
        return EXIT_FAILURE;
    }

    int sw = atoi(argv[2]);
    if (sw == 0) {
        printf("Invalid Option");
        exit(EXIT_FAILURE);
    }

    switch(sw) {
        case 2:
            for (size_t i = 0; i < size; i++) {
                for ( size_t j = i; j < size; j++) {
                    printf("%05d+%05d=%05d\n", invoice[i], invoice[j], invoice[i]+invoice[j]);
                }
            }
            break;
        case 3:
            for (size_t i = 0; i < size; i++) {
                for (size_t j = i; j < size; j++) {
                    if (i + j > 2020) {
                        break;
                    }
                    for (size_t k = j; k < size; k++) {
                        printf("%05d+%05d+%05d=%05d\n", invoice[i],
                                invoice[j], invoice[k],
                                invoice[i]+invoice[j]+invoice[k]);
                        if (invoice[i]+invoice[j]+invoice[k] == 2020) {
                            printf(">%lld\n", invoice[i]*invoice[j]*invoice[k]);
                            fflush(stdout);
                        }
                    }
                }
            }
            break;
    }




    if (line) {
        free(line);
    }
    fclose(fp);
    free(invoice);
    return EXIT_SUCCESS;
}
