#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b) {
    long long n1 = *(long long*)a;
    long long n2 = *(long long*)b;
    if (n1 > n2) return 1;
    else if (n1 < n2) return -1;
    return 0;
}

int binary_search(long long* arr, int size, long long target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == target) return 1;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return 0;
}

int main() {
    int N, M;
    scanf("%d", &N);

    long long* A = malloc(sizeof(long long) * N);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
    }

    qsort(A, N, sizeof(long long), cmp);

    scanf("%d", &M);
    long long x;
    for (int i = 0; i < M; i++) {
        scanf("%lld", &x);
        printf("%d\n", binary_search(A, N, x));
    }

    free(A);
    return 0;
}
