
// 수현이는 카드 기술을 연습하고 있다. 수현이의 손에 들린 카드를 하나씩 내려놓아 바닥에 쌓으려고 한다. 수현이가 쓸 수 있는 기술은 다음 3가지다.

// 제일 위의 카드 1장을 바닥에 내려놓는다.
// 위에서 두 번째 카드를 바닥에 내려놓는다. 카드가 2장 이상일 때만 쓸 수 있다.
// 제일 밑에 있는 카드를 바닥에 내려놓는다. 카드가 2장 이상일 때만 쓸 수 있다.
// 수현이는 처음에 카드 N장을 들고 있다. 카드에는 1부터 N까지의 정수가 중복되지 않게 적혀 있다. 
// 기술을 N번 사용하여 카드를 다 내려놓았을 때, 놓여 있는 카드들을 확인했더니 위에서부터 순서대로 1, 2, …, N이 적혀 있었다!

// 놀란 수현이는 처음에 카드가 어떻게 배치되어 있었는지 궁금해졌다. 처음 카드의 상태를 출력하여라.

// 출력
// 초기 카드의 상태를 위에서부터 순서대로 출력하여라.

// 예제 입력 1 
// 5
// 1 1 1 1 1

// 예제 출력 1 
// 5 4 3 2 1

// 예제 입력 2 
// 5
// 2 3 3 2 1

// 예제 출력 2 
// 1 5 2 3 4

#include <stdio.h>

#define MAX 2000000

int deque[MAX];
int front, back;

int main() {
    int N;
    scanf("%d", &N);

    int op[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &op[i]);
    }

    front = back = MAX / 2;

    for (int i = N - 1; i >= 0; i--) {
        int card = N - i;

        if (op[i] == 1) {
            deque[--front] = card;
        } else if (op[i] == 2) {
            int temp = deque[front];
            deque[--front] = temp;    // 원래 첫 번째 값 복제해서 앞으로 밀기
            deque[front + 1] = card;  // 두 번째 자리에 새 카드 삽입
        } else if (op[i] == 3) {
            deque[back++] = card;
        }
    }

    for (int i = front; i < back; i++) {
        printf("%d ", deque[i]);
    }
    printf("\n");

    return 0;
}
