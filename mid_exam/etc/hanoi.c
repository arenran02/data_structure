#include <stdio.h>

// 이동 순서를 출력하는 함수
void hanoi(int n, int from, int to, int via) {
    if (n == 1) {
        printf("%d %d\n", from, to);
        return;
    }

    hanoi(n - 1, from, via, to); // n-1개를 보조 장대로 이동
    printf("%d %d\n", from, to); // 가장 큰 원판 이동
    hanoi(n - 1, via, to, from); // n-1개를 목표 장대로 이동
}

int main() {
    int n;
    scanf("%d", &n);

    // 이동 횟수는 2^n - 1
    int moves = (1 << n) - 1;
    printf("%d\n", moves);

    hanoi(n, 1, 3, 2); // 1번에서 3번으로, 2번은 보조

    return 0;
}
