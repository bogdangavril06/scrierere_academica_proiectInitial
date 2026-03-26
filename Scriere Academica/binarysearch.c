#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void gen_random(int arr[], long long n) {
    for(long long i = 0; i < n; i++)
        arr[i] = rand() % 10000000;
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

long long binarySearch(int arr[], long long n, int key) {
    long long left = 0, right = n - 1;
    while(left <= right) {
        long long mid = left + (right - left) / 2;
        if(arr[mid] == key) return mid;
        else if(arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void printArray(int arr[], long long n) {
    long long limit = 1000;
    if(n <= 100000) {
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

    int *arr = malloc(n * sizeof(int));
    if(!arr) { printf("Memorie insuficienta!\n"); return 1; }

    char tip[20];
    printf("Tip lista (sortat/random/invers/aproape/flat): ");
    scanf("%s", tip);

    if(strcmp(tip,"random")==0) gen_random(arr, n);
    else if(strcmp(tip,"sortat")==0) gen_sortat(arr, n);
    else if(strcmp(tip,"invers")==0) gen_invers(arr, n);
    else if(strcmp(tip,"aproape")==0) gen_aproape_sortat(arr, n);
    else if(strcmp(tip,"flat")==0) gen_flat(arr, n);
    else { printf("Tip invalid!\n"); free(arr); return 1; }

    printf("\nArray generat:\n");
    printArray(arr, n);

    int key;
    printf("\nIntroduceti elementul de cautat: ");
    scanf("%d", &key);

    long long idx = binarySearch(arr, n, key);
    if(idx != -1) printf("Elementul %d se afla pe pozitia %lld.\n", key, idx);
    else printf("Elementul %d nu a fost gasit.\n", key);

    free(arr);
    return 0;
}