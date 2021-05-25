#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int LIMIT = 300000;
const int STEP = 100;
const int CALL_COUNT = 10;
const int RAND_LIMITS = 1000;


void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify(int arr[], int n, int i, int *rec_count, int *swap_count) {
    int largest = i;
    (*rec_count)++;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        (*swap_count)++;
        swap(&arr[i], &arr[largest]);

        heapify(arr, n, largest, rec_count, swap_count);
    }
}

void heapSort(int arr[], int n, int *rec_count, int *swap_count) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, rec_count, swap_count);

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        (*swap_count)++;
        heapify(arr, i, 0, rec_count, swap_count);
    }
}

void call(int len) {
    int *arr;
    int rec_count = 0, swap_count = 0;
    long time_start, time_finish;
    arr = (int *) malloc(len * sizeof(int));
    if (!arr)exit(-1);
    FILE *fp1;
    FILE *fp2;
    if ((fp1 = fopen("write.txt", "a")) == NULL) {
        printf("Can't open file 'write.txt'\n");
        exit(-1);
    }
    if ((fp2 = fopen("write_without_time.txt", "a")) == NULL) {
        printf("Can't open file 'write.txt'\n");
        exit(-1);
    }
    for (int i = 0; i < len; ++i) {
        arr[i] = rand() % RAND_LIMITS;
    }

    time_start = clock();
    heapSort(arr, len, &rec_count, &swap_count);
    time_finish = clock();

    fprintf(fp1, "%d %d %d %li\n", len, rec_count, swap_count, time_finish - time_start);
    fprintf(fp2, "%d %d\n", len, rec_count + swap_count);
    fclose(fp1);
    fclose(fp2);
    free(arr);
}

void call_cycle(int len) {
    for (int i = 0; i < CALL_COUNT; ++i) {
        call(len);
    }
}

int main() {
    srand(time(NULL));
    for (int i = 0; i < LIMIT; i += STEP) {
        call_cycle(i);
    }
    return 0;
}
