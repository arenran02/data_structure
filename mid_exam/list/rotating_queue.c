// 지민이는 N개의 원소를 포함하고 있는 양방향 순환 큐를 가지고 있다. 지민이는 이 큐에서 몇 개의 원소를 뽑아내려고 한다.

// 지민이는 이 큐에서 다음과 같은 3가지 연산을 수행할 수 있다.

// 첫 번째 원소를 뽑아낸다. 이 연산을 수행하면, 원래 큐의 원소가 a1, ..., ak이었던 것이 a2, ..., ak와 같이 된다.
// 왼쪽으로 한 칸 이동시킨다. 이 연산을 수행하면, a1, ..., ak가 a2, ..., ak, a1이 된다.
// 오른쪽으로 한 칸 이동시킨다. 이 연산을 수행하면, a1, ..., ak가 ak, a1, ..., ak-1이 된다.
// 큐에 처음에 포함되어 있던 수 N이 주어진다. 그리고 지민이가 뽑아내려고 하는 원소의 위치가 주어진다. (이 위치는 가장 처음 큐에서의 위치이다.) 
// 이때, 그 원소를 주어진 순서대로 뽑아내는데 드는 2번, 3번 연산의 최솟값을 출력하는 프로그램을 작성하시오.

#include <stdio.h>
#include <stdlib.h>

#define MAX 10001

typedef struct {
    int data[MAX];
    int front;
    int rear;
} Deque;

// 덱 초기화
void init(Deque* dq) {
    dq->front = 0;
    dq->rear = 0;
}

// 덱 크기 반환
int size(Deque* dq) {
    return (dq->rear - dq->front + MAX) % MAX;
}

// 덱이 비어있는지 확인
int isEmpty(Deque* dq) {
    return dq->front == dq->rear;
}

// 덱 뒤에 추가
void push_back(Deque* dq, int val) {
    dq->data[dq->rear] = val;
    dq->rear = (dq->rear + 1) % MAX;
}

// 덱 앞에서 제거
int pop_front(Deque* dq) {
    int val = dq->data[dq->front];
    dq->front = (dq->front + 1) % MAX;
    return val;
}

// 덱 뒤에서 제거
int pop_back(Deque* dq) {
    dq->rear = (dq->rear - 1 + MAX) % MAX;
    return dq->data[dq->rear];
}

// 덱 앞에 추가 (오른쪽 회전 시 사용)
void push_front(Deque* dq, int val) {
    dq->front = (dq->front - 1 + MAX) % MAX;
    dq->data[dq->front] = val;
}

// 특정 값의 현재 인덱스 반환
int get_index(Deque* dq, int target) {
    int idx = 0;
    for (int i = dq->front; i != dq->rear; i = (i + 1) % MAX) {
        if (dq->data[i] == target) {
            break;
        }
        idx++;
    }
    return idx;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Deque dq;
    init(&dq);

    // 초기 큐 설정
    for (int i = 1; i <= N; i++) {
        push_back(&dq, i);
    }

    int result = 0;

    for (int i = 0; i < M; i++) {
        int target;
        scanf("%d", &target);

        int idx = get_index(&dq, target);
        int dq_size = size(&dq);

        // 어느 방향으로 회전할지 결정
        if (idx <= dq_size / 2) {
            // 왼쪽 회전
            for (int j = 0; j < idx; j++) {
                int temp = pop_front(&dq);
                push_back(&dq, temp);
                result++;
            }
        } else {
            // 오른쪽 회전
            for (int j = 0; j < dq_size - idx; j++) {
                int temp = pop_back(&dq);
                push_front(&dq, temp);
                result++;
            }
        }

        // 원하는 원소 제거
        pop_front(&dq);
    }

    printf("%d\n", result);

    return 0;
}
