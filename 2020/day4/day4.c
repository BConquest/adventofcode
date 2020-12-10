#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

typedef struct passport {
    char *byr;
    char *iyr;
    char *eyr;
    char *hgt;
    char *hcl;
    char *ecl;
    char *pid;
    char *cid;
} passport;

void printPassport(passport *p) {
    printf("\tBirth Year: %s\n", p->byr);
    fflush(stdout);
    printf("\tIssue Year: %s\n", p->iyr);
    fflush(stdout);
    printf("\tExpiration Year: %s\n", p->eyr);
    fflush(stdout);
    printf("\tHeight: %s\n", p->hgt);
    fflush(stdout);
    printf("\tHair Color: %s\n", p->hcl);
    fflush(stdout);
    printf("\tEye Color: %s\n", p->ecl);
    fflush(stdout);
    printf("\tPassport ID: %s\n", p->pid);
    fflush(stdout);
    printf("\tCountry ID: %s\n", p->cid);
    fflush(stdout);
}

passport *newPassport() {
    passport *p = malloc(sizeof(passport));
    p->byr = NULL;
    p->iyr = NULL;
    p->eyr = NULL;
    p->hgt = NULL;
    p->hcl = NULL;
    p->ecl = NULL;
    p->pid = NULL;
    p->cid = NULL;
    return p;
}

void cpyPassport(passport *p, passport *dst) {
    dst->byr = p->byr;
    dst->iyr = p->iyr;
    dst->eyr = p->eyr;
    dst->hgt = p->hgt;
    dst->hcl = p->hcl;
    dst->ecl = p->ecl;
    dst->pid = p->pid;
    dst->cid = p->cid;
}

void destroyPassport(passport *p) {
    free(p->byr);
    free(p->iyr);
    free(p->eyr);
    free(p->hgt);
    free(p->hcl);
    free(p->ecl);
    free(p->pid);
    free(p->cid);
    free(p);
}

int checkECL(char *ecl) {
    if (strcmp(ecl, "amb") == 0) {
        return 1;
    } else if (strcmp(ecl, "blu") == 0) {
        return 1;
    } else if (strcmp(ecl, "brn") == 0) {
        return 1;
    } else if (strcmp(ecl, "gry") == 0) {
        return 1;
    } else if (strcmp(ecl, "grn") == 0) {
        return 1;
    } else if (strcmp(ecl, "hzl") == 0) {
        return 1;
    } else if (strcmp(ecl, "oth") == 0) {
        return 1;
    }
    return 0;
}

int checkHCL(char *hcl) {
    int rv = 0;
    size_t length = sizeof(hcl);

    if (hcl[0] != '#') return rv;

    for (size_t i = 1; i < length-1; i++) {
        if (!isdigit(hcl[i]) && !(hcl[i] >= 97 && hcl[i] <=102)) {
            return rv;
        }
    }
    return 1;
}

int checkHGT(char *hgt) {
    if (hgt[3] == 'c' && hgt[4] == 'm') {
        char height[4] = {hgt[0], hgt[1], hgt[2]};
        int h = atoi(height);
        
        if (h >= 150 && h <=193) {
            return 1;
        }
    }
    
    if (hgt[2] == 'i' && hgt[3] == 'n') {
        char height[3] = {hgt[0], hgt[1]};
        int h = atoi(height);

        if (h >= 59 && h <= 76) {
            return 1;
        }
    }

    return 0;
}

int checkPID(char *pid) {
    int rv = 0;
    size_t size = strlen(pid);
    if (size == (size_t)9) {
        for (size_t i = 0; i < size; i++) {
            if (isdigit(pid[i]) == 0) {
                rv = 0;
            }
        }
        rv = 1;
    }
    return rv;
}

int checkPassport(passport *p) {
    int total = 0;

    if (p->byr != NULL) {
        int byr = atoi(p->byr);
        if (byr >= 1920 && byr <= 2002) {
            total += 1;
        }
    }

    if (p->iyr != NULL) {
        int iyr = atoi(p->iyr);
        if (iyr >= 2010 && iyr <= 2020) {
            total += 1;
        }
    }

    if (p->eyr != NULL) {
        int eyr = atoi(p->eyr);
        if (eyr >= 2020 && eyr <= 2030) {
            total += 1;
        }
    }

    if (p->hgt != NULL) {
        if (checkHGT(p->hgt) == 1) {
            total += 1;
        }
    }

    if (p->hcl != NULL) {
        if (checkHCL(p->hcl) == 1) {
            total += 1;
        }
    }

    if (p->ecl != NULL) {
        if (checkECL(p->ecl) == 1) {
            total += 1;
        }
    }

    if (p->pid != NULL) {
        if (checkPID(p->pid) == 1) {
            total += 1;
        }
    }

    if (p->cid != NULL || p->cid == NULL) {
        total += 1;
    }
    return total;
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

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int numberOfPeople = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (strcmp(line, "\n") == 0) {
            numberOfPeople += 1;
        }
    }
    if (strcmp(line, "\n") != 0) {
        numberOfPeople += 1;
    }
    printf("Number of Passports to verify: %d\n", numberOfPeople);

    fclose(fp);
    fp = fopen(argv[1], "r");

    int currentPassports = 0;

    passport **arrayPassports;
    arrayPassports = malloc(numberOfPeople * sizeof(passport *));
    for (int i = 0; i < numberOfPeople; i++) {
        arrayPassports[i] = newPassport();
    }

    passport *curPassport = newPassport();
    int correctPassports = 0;
    while (currentPassports < numberOfPeople) {
        if ((read = getline(&line, &len, fp)) != -1) {
            if (strcmp(line, "\n") == 0) {
                cpyPassport(curPassport, arrayPassports[currentPassports]);
                currentPassports += 1;
                int l = checkPassport(curPassport);
                if (l == 8) {
                    correctPassports += 1;
                }
                curPassport = newPassport();
            }
            for (size_t i = 0; i < len; i++) {
                if (line[i] == ' ') {
                    line[i] = ':';
                }
                if (line[i] == '\n') {
                    line[i] = '\0';
                }
                if (line[i] == '\0') {
                    break;
                }
            }

            char *token = strtok(line, ":");
            while (token != NULL) {
                char *subtoken = strtok(NULL, ":");
                size_t size = strlen(subtoken)+1;
                if (strcmp(token, "byr") == 0) {
                    curPassport->byr = malloc(sizeof(char)*size);
                    strncpy(curPassport->byr, subtoken, size);
                } else if (strcmp(token, "iyr") == 0) {
                    curPassport->iyr = malloc(sizeof(char)*size);
                    strncpy(curPassport->iyr, subtoken, size);
                } else if (strcmp(token, "eyr") == 0) {
                    curPassport->eyr = malloc(sizeof(char)*size);
                    strncpy(curPassport->eyr, subtoken, size);
                } else if (strcmp(token, "hgt") == 0) {
                    curPassport->hgt = malloc(sizeof(char)*size);
                    strncpy(curPassport->hgt, subtoken, size);
                } else if (strcmp(token, "hcl") == 0) {
                    curPassport->hcl = malloc(sizeof(char)*size);
                    strncpy(curPassport->hcl, subtoken, size);
                } else if (strcmp(token, "ecl") == 0) {
                    curPassport->ecl = malloc(sizeof(char)*size);
                    strncpy(curPassport->ecl, subtoken, size);
                } else if (strcmp(token, "pid") == 0) {
                    curPassport->pid = malloc(sizeof(char)*size);
                    strncpy(curPassport->pid, subtoken, size);
                } else if (strcmp(token, "cid") == 0) {
                    curPassport->cid = malloc(sizeof(char)*size);
                    strncpy(curPassport->cid, subtoken, size);
                } else {
                    printf("%s\n", token);
                }
                token = strtok(NULL, ":");
            }
        }

        if (read == EOF) {
            break;
        }
    }
    int l = checkPassport(curPassport);
    if (l == 8) {
        correctPassports++;
    }
    printf("%d\n", correctPassports);
    cpyPassport(curPassport, arrayPassports[currentPassports]);

    for (int i = 0; i < numberOfPeople; i++) {
        destroyPassport(arrayPassports[i]);
    }
    free(arrayPassports);
    if (line != NULL) {
        free(line);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
