// 카드2

// N장의 카드가 있다. 각각의 카드는 차례로 1부터 N까지의 번호가 붙어 있으며, 1번 카드가 제일 위에, N번 카드가 제일 아래인 상태로 순서대로 카드가 놓여 있다.

// 이제 다음과 같은 동작을 카드가 한 장 남을 때까지 반복하게 된다. 우선, 제일 위에 있는 카드를 바닥에 버린다. 
// 그 다음, 제일 위에 있는 카드를 제일 아래에 있는 카드 밑으로 옮긴다.

// 예를 들어 N=4인 경우를 생각해 보자. 카드는 제일 위에서부터 1234 의 순서로 놓여있다. 1을 버리면 234가 남는다. 
// 여기서 2를 제일 아래로 옮기면 342가 된다. 3을 버리면 42가 되고, 4를 밑으로 옮기면 24가 된다. 마지막으로 2를 버리고 나면, 남는 카드는 4가 된다.

// N이 주어졌을 때, 제일 마지막에 남게 되는 카드를 구하는 프로그램을 작성하시오.

#include <stdio.h>
#include <stdlib.h>

// 노드 정의
typedef struct node {
    int data;
    struct node* next;
} node;

// 큐 구조체
typedef struct {
    node* front;
    node* rear;
    int size;
} QUEUE;

// 큐 초기화
void init_QUEUE(QUEUE* q) {
    q->front = q->rear = NULL;
    q->size = 0;
}

// 큐가 비었는지 확인
int is_empty(QUEUE* q) {
    return q->size == 0;
}

// 큐에 삽입
void push(QUEUE* q, int data) {
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;

    if (is_empty(q)) {
        q->front = newnode;
    } else {
        q->rear->next = newnode;
    }

    q->rear = newnode;
    q->size++;
}

// 큐에서 꺼내기
int pop(QUEUE* q) {
    if (is_empty(q)) return -1;

    node* temp = q->front;
    int data = temp->data;

    q->front = temp->next;
    q->size--;

    if (q->size == 0) {
        q->rear = NULL;
    }

    free(temp);
    return data;
}

int main() {
    int N;
    scanf("%d", &N);

    QUEUE q;
    init_QUEUE(&q);

    // 1부터 N까지 큐에 넣기
    for (int i = 1; i <= N; i++) {
        push(&q, i);
    }

    // 카드 처리
    while (q.size > 1) {
        pop(&q);             // 맨 위 카드 버리기
        int move = pop(&q);  // 그 다음 카드를 꺼내서
        push(&q, move);      // 맨 뒤로 넣기
    }

    // 마지막 남은 카드 출력
    printf("%d\n", pop(&q));

    return 0;
}
