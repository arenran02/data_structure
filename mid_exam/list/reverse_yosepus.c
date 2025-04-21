/* 총 N명이 원을 이루며 앉아 있다. 1번부터 N번까지 번호가 매겨져 있으며, 1번 오른쪽에 2번, 2번 오른쪽에 3번, ..., N번 오른쪽에는 다시 1번이 앉아 있는 형태이다.

이제 다음과 같은 방식으로 사람을 제거한다:

처음에는 시계 방향으로 진행한다.

시작 위치에서 K번째 사람을 제거한다.

이후에는 직전에 제거된 사람의 자리 기준으로 K번째 사람을 계속해서 제거한다.

M명이 제거될 때마다 방향을 반대로 바꾼다.

이 과정을 모든 사람이 제거될 때까지 반복한다.

이렇게 제거된 사람들의 순서를 (N, K, M) 반전 요세푸스 순열이라고 한다.

예를 들어, (7, 3, 4)의 경우 제거 순서는:

<3, 6, 2, 7, 1, 5, 4>
*/


#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

int main() {
    int n, k, m;
    scanf("%d %d %d", &n, &k, &m);

    int deque[MAX];
    int front = 0, rear = n - 1;
    for (int i = 0; i < n; i++) {
        deque[i] = i + 1;
    }

    int count = 0;
    int size = n;
    int check = 1; // true

    while (size > 0) {
        if (check) {
            for (int i = 0; i < k - 1; i++) {
                deque[(rear + 1) % MAX] = deque[front];
                rear = (rear + 1) % MAX;
                front = (front + 1) % MAX;
            }
            printf("%d\n", deque[front]);
            front = (front + 1) % MAX;
        } else {
            for (int i = 0; i < k - 1; i++) {
                front = (front - 1 + MAX) % MAX;
                deque[front] = deque[rear];
                rear = (rear - 1 + MAX) % MAX;
            }
            printf("%d\n", deque[rear]);
            rear = (rear - 1 + MAX) % MAX;
        }
        size--;
        count++;
        if (count == m) {
            check = !check;
            count = 0;
        }
    }

    return 0;
}
