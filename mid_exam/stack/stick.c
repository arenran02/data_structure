// 아래 그림처럼 높이만 다르고 (같은 높이의 막대기가 있을 수 있음) 모양이 같은 막대기를 일렬로 세운 후, 왼쪽부터 차례로 번호를 붙인다. 
// 각 막대기의 높이는 그림에서 보인 것처럼 순서대로 6, 9, 7, 6, 4, 6 이다. 
// 일렬로 세워진 막대기를 오른쪽에서 보면 보이는 막대기가 있고 보이지 않는 막대기가 있다. 
// 즉, 지금 보이는 막대기보다 뒤에 있고 높이가 높은 것이 보이게 된다. 예를 들어, 그림과 같은 경우엔 3개(6번, 3번, 2번)의 막대기가 보인다.

// N개의 막대기에 대한 높이 정보가 주어질 때, 오른쪽에서 보아서 몇 개가 보이는지를 알아내는 프로그램을 작성하려고 한다.

#include <stdio.h>
#include <stdlib.h>

// 노드 정의
typedef struct node {
    int data;
    struct node* next;
} node;

// 스택 구조체
typedef struct {
    node* top;
    int size;
} STACK;

// 스택 초기화
void init_STACK(STACK* s) {
    s->top = NULL;
    s->size = 0;
}

// 스택이 비었는지 확인
int is_stack_empty(STACK* s) {
    return s->size == 0;
}

// 스택에 데이터 추가 (push)
void push_stack(STACK* s, int data) {
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->next = s->top;
    s->top = newnode;
    s->size++;
}

// 스택에서 데이터 제거 (pop)
int pop_stack(STACK* s) {
    if (is_stack_empty(s)) {
        return -1;  // 비어있을 때는 -1 반환
    }
    node* temp = s->top;
    int data = temp->data;
    s->top = temp->next;
    s->size--;

    free(temp);
    return data;
}

// 스택의 맨 위 값 확인 (peek)
int peek_stack(STACK* s) {
    if (is_stack_empty(s)) return -1;
    return s->top->data;
}

int main() {
    int N;
    scanf("%d", &N);

    int* heights = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &heights[i]);
    }

    STACK s;
    init_STACK(&s);

    int count = 0;

    // 오른쪽에서 보기 → 뒤에서부터 순회
    for (int i = N - 1; i >= 0; i--) {
        int curr = heights[i];
        // 현재 스택 top보다 클 때만 push → 보이는 막대
        if (is_stack_empty(&s) || curr > peek_stack(&s)) {
            push_stack(&s, curr);
            count++;
        }
    }

    printf("%d\n", count);

    // 메모리 해제
    while (!is_stack_empty(&s)) pop_stack(&s);
    free(heights);
    return 0;
}
