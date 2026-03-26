#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void gen_random(int arr[], long long n) {
    for(long long i = 0; i < n; i++)
        arr[i] = rand() % 1000;
}

void gen_sortat(int arr[], long long n) {
    for(long long i = 0; i < n; i++)
        arr[i] = i;
}

void gen_invers(int arr[], long long n) {
    for(long long i = 0; i < n; i++)
        arr[i] = n - i - 1;
}

void gen_aproape_sortat(int arr[], long long n) {
    for(long long i = 0; i < n; i++)
        arr[i] = i;
    long long swaps = n * 0.05;
    for(long long i = 0; i < swaps; i++) {
        long long a = rand() % n;
        long long b = rand() % n;
        int tmp = arr[a]; arr[a] = arr[b]; arr[b] = tmp;
    }
}

void gen_flat(int arr[], long long n) {
    int values[] = {1, 2, 3, 4, 5};
    for(long long i = 0; i < n; i++)
        arr[i] = values[rand() % 5];
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void slowSort(int arr[], long long i, long long j) {
    if(i >= j) return;
    long long m = (i + j) / 2;
    slowSort(arr, i, m);
    slowSort(arr, m + 1, j);
    if(arr[j] < arr[m])
        swap(&arr[j], &arr[m]);
    slowSort(arr, i, j - 1);
}

void printArray(int arr[], long long n) {
    long long limit = 1000;
    if(n <= 1000) {
        for(long long i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
    } else {
        for(long long i = 0; i < limit; i++) printf("%d ", arr[i]);
        printf("... (%lld elemente total)\n", n);
    }
}

int main() {
    srand(time(NULL));

    long long n;
    printf("Introduceti numarul de elemente: ");
    scanf("%lld", &n);

    if(n > 5000) {
        printf("SlowSort e foarte lent! Foloseste un numar mai mic de 5000 pentru a nu dura milioane de ani !\n");
        return 1;
    }

    int *arr = malloc(n * sizeof(int));
    if(!arr) { printf("Memorie insuficienta!\n"); return 1; }

    char tip[20];
    printf("Tip lista (random/sortat/invers/aproape/flat): ");
    scanf("%s", tip);

    if(strcmp(tip,"random")==0) gen_random(arr, n);
    else if(strcmp(tip,"sortat")==0) gen_sortat(arr, n);
    else if(strcmp(tip,"invers")==0) gen_invers(arr, n);
    else if(strcmp(tip,"aproape")==0) gen_aproape_sortat(arr, n);
    else if(strcmp(tip,"flat")==0) gen_flat(arr, n);
    else { printf("Tip invalid!\n"); free(arr); return 1; }

    printf("\nArray nesortat:\n");
    printArray(arr, n);

    clock_t start = clock();
    slowSort(arr, 0, n - 1);
    clock_t end = clock();

    printf("\nArray sortat:\n");
    printArray(arr, n);

    printf("Timp sortare: %f secunde\n", (double)(end - start)/CLOCKS_PER_SEC);

    free(arr);
    return 0;
}