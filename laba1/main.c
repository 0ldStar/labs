#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readln(int *counter, int *size) {
    char c = ' ';
    char *str = (char *) malloc(10 * sizeof(char));
    for (int i = 0; c != '\n'; i++) {
        str = (char *) realloc(str, (i + 2) * sizeof(char));
        scanf("%c", &c);
        (*size)++;
        if (c != '\n') {
            str[i] = c;
            str[i + 1] = '\0';
            if (c == ' ')(*counter)++;
        } else { str[i] = '\0'; }
    }
    return str;
}


void dynamic_array_print(int **matrix, size_t N, size_t M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%*d", 5, matrix[i][j]);
        }
        printf("\n");
    }
}

void bubbleSort(int **num, int size, char *str,const int *arr_size) {
    int temp1, temp2, len;
    char buf[*arr_size];
    for (int i = 0; i < size - 1; i++) {
        for (int j = (size - 1); j > i; j--) {
            if (num[1][j - 1] > num[1][j]) {
                temp1 = num[1][j - 1];
                temp2 = num[2][j - 1];
                len = num[0][j] - num[0][j - 1] + num[2][j];
                for (int m = 0; m < len; m++) {
                    buf[m] = ' ';
                }
                buf[len] = '\0';
                //IT works)
                for (int k = 0, l = 0; k < len; k++) {
                    if (k <= num[2][j - 1] - 1) {
                        buf[len + k - num[2][j - 1]] = str[num[0][j - 1] + k];
                    }
                    if (k + num[0][j - 1] >= num[0][j]) {
                        buf[l++] = str[k + num[0][j - 1]];
                    }
                }
                for (int k = num[0][j - 1]; k < len + num[0][j - 1]; k++) {
                    str[k] = buf[k - num[0][j - 1]];
                }
                num[0][j] = num[0][j - 1] + len - num[2][j - 1];
                num[1][j - 1] = num[1][j];
                num[2][j - 1] = num[2][j];
                num[1][j] = temp1;
                num[2][j] = temp2;
            }
        }
    }
}

int **alloc(const int *size) {
    int **num;
    num = (int **) malloc(3 * sizeof(int *));
    num[0] = (int *) malloc(sizeof(int));
    num[1] = (int *) malloc(sizeof(int));
    num[2] = (int *) malloc(sizeof(int));
    num[0] = (int *) realloc(num[0], (*size + 1) * sizeof(int));
    num[1] = (int *) realloc(num[1], (*size + 1) * sizeof(int));
    num[2] = (int *) realloc(num[2], (*size + 1) * sizeof(int));
    return num;
}

void counter(char *str, int **num, int *arr_size) {
    int n = 0;
    for (int i = 0; i < strlen(str) - 1; i++) {
        if ((str[i - 1] == ' ') || (i == 0)) {
            if (str[i] == ' ') continue;
            num[0][n] = i;
            num[1][n] = (int) str[i];
            n++;
        }
    }
    int j = 0, l = 0;
    for (int i = 0; i <= strlen(str); i++) {
        j++;
        if (str[i] == ' ' || str[i] == '\0') {
            num[2][l] = j - 1;
            l++;
            j = 0;
        }
    }
    bubbleSort(num, n, str, arr_size);
}

int main() {
    int count = 1, size =0;
    char *str = readln(&count,&size);
    int **num = alloc(&count);
    counter(str, num,&size);
    printf("String = %s\n", str);
    return 0;
}
