#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **readSameWords(int *height, int *length, int mode) {
    int flag = 1;
    char buf[100];
    char c = ' ';
    char **str = (char **) malloc(sizeof(char *));
    if (mode) flag = 0;
    do {
        scanf("%s", buf);
        scanf("%c", &c);
        if (flag) {
            flag = 0;
            *length = (int) strlen(buf);
        }
        if (strlen(buf) != *length) {
            printf("Words has different length!\n");
            exit(-1);
        }
        if (mode) {
            str = (char **) realloc(str, sizeof(char *));
            *str = (char *) malloc(strlen(buf) * sizeof(char));
            strcpy(*str, buf);
            return str;
        }
        str = (char **) realloc(str, (*height + 1) * sizeof(char *));
        str[*height] = (char *) malloc(sizeof(char));
        str[*height] = (char *) realloc(str[*height], strlen(buf) * sizeof(char));
        strcpy(str[*height], buf);
        (*height)++;
    } while (c != '\n');
    return str;
}

void sameCheck(char *a, char *b, int *n, int *count, int length) {
    if (*n != length) {
        if (a[*n] != b[*n])(*count)++;
        (*n)++;
        sameCheck(a, b, n, count, length);
    }
}

char **chainBuild(char **str, char *word, const int *length, int *height, int *size) {
    int n = 0, diff = 0, flag = 0;
    char **chain = (char **) malloc(sizeof(char *));
    chain[0] = (char *) malloc(*length * sizeof(char));
    chain[0] = word;
    while (1) {
        for (int i = 0; i < *height; ++i) {
            n = 0;
            diff = 0;
            sameCheck(chain[*size], str[i], &n, &diff, *length);
            if (diff <= 2) {
                (*size)++;
                chain = (char **) realloc(chain, (*size + 1) * sizeof(char *));
                chain[*size] = (char *) malloc(*length * sizeof(char));
                chain[*size] = str[i];
                for (int j = i; j < *height; ++j) str[j] = str[j + 1];
                (*height)--;
                str = (char **) realloc(str, *height * sizeof(char *));
                flag = 0;
                break;
            } else flag = 1;
        }
        if (!*height) break;
        if (flag) break;
    }
    return chain;
}

int main() {
    int height = 0, length = 0, size = 0;
    char **str, **chain;
    char *word;
    printf("Enter the string:\n");
    str = readSameWords(&height, &length, 0);
    for (int i = 0; i < height; ++i) {
        printf("%s ", str[i]);
    }
    printf("\nEnter the word:\n");
    word = *readSameWords(&height, &length, 1);
    printf("%s\n", word);
    chain = chainBuild(str, word, &length, &height, &size);
    printf("Chain:\n");
    for (int i = 0; i <= size; ++i) {
        printf("%s ", chain[i]);
    }
    return 0;
}
//барак баран банан дурак бутон бутан питон барин