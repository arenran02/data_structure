#include <stdio.h>

#define MAX 80001

int main() {
    int N;
    scanf("%d", &N);

    int h[MAX];
    for (int i = 0; i < N; i++) {
        scanf("%d", &h[i]);
    }

    long long answer = 0;
    int stack[MAX];
    int top = -1;

    for (int i = 0; i < N; i++) {
        // 스택에서 현재보다 높거나 같은 빌딩을 만날 때까지 pop
        while (top >= 0 && h[stack[top]] <= h[i]) {
            top--;
        }
        // 현재 스택에 남아있는 요소가 현재 빌딩에서 볼 수 있는 옥상의 수
        answer += top + 1;
        stack[++top] = i;
    }

    printf("%lld\n", answer);
    return 0;
}
