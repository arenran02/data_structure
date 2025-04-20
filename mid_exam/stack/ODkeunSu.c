#include <stdio.h>

#define MAX 1000001

int A[MAX];
int freq[MAX];     // 값 → 등장 횟수
int NGF[MAX];      // 결과 저장
int stack[MAX];    // 스택
int top = -1;

int main() {
    int N;
    scanf("%d", &N);

    int max_val = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        freq[A[i]]++;
        if (A[i] > max_val) max_val = A[i];
    }

    for (int i = N - 1; i >= 0; i--) {
        // 스택에 현재보다 freq 작은 애들 제거
        while (top >= 0 && freq[A[i]] >= freq[stack[top]]) {
            top--;
        }

        if (top == -1) NGF[i] = -1;
        else NGF[i] = stack[top];

        // 현재 값을 스택에 넣음
        stack[++top] = A[i];
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", NGF[i]);
    }

    return 0;
}
