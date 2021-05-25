#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void list_print(char ***arr, const int *height, const int *width) {
    for (int i = 0; i <= *height; ++i) {
        printf("\n");
        for (int j = 0; j <= width[i]; ++j) {
            printf("%s ", arr[i][j]);
        }
    }
}

char ***File_read(char ***arr) {
    FILE *fp;
    char buf1[100], buf2[100];
    char c;
    int height = 0, len = 0, heightSize = 1;
    int *width = (int *) malloc(sizeof(int));
    if ((fp = fopen("read.txt", "r")) == NULL) {
        printf("Can't open file 'read.txt'\n");
    }

    arr = (char ***) malloc(sizeof(char **));
    arr[0] = (char **) malloc(sizeof(char *));

    while (fscanf(fp, "%s", buf1) == 1) {
        width = (int *) realloc(width, (height + 1) * sizeof(int));
        width[height] = len;
        arr[height] = (char **) realloc(arr[height], (len + 1) * sizeof(char *));
        arr[height][len] = (char *) malloc(sizeof(char));
        arr[height][len] = (char *) realloc(arr[height][len], strlen(buf1) * sizeof(char));
        if ((int) arr[height][0][0] >= (int) buf1[0]) {
            for (int i = 0; i <= len; ++i) {
                strcpy(buf2, arr[height][i]);
                arr[height][i] = (char *) malloc(strlen(buf1) * sizeof(char));
                strcpy(arr[height][i], buf1);
                strcpy(buf1, buf2);
            }
        } else strcpy(arr[height][len], buf1);
        len++;
        fscanf(fp, "%c", &c);
        if (c == '\n') {
            height++;
            len = 0;
            if (height == heightSize) {
                arr = (char ***) realloc(arr, 2 * height * sizeof(char **));
                heightSize = 2 * height;
            }
            arr[height] = (char **) malloc(sizeof(char *));
        }
    }
    list_print(arr, &height, width);
    fclose(fp);
    return arr;
}

int main() {
    char ***arr = NULL;
    arr = File_read(arr);
    return 0;
}
