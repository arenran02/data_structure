// 나코더 기장 재민이는 동아리 회식을 준비하기 위해서 장부를 관리하는 중이다.

// 재현이는 재민이를 도와서 돈을 관리하는 중인데, 애석하게도 항상 정신없는 재현이는 돈을 실수로 잘못 부르는 사고를 치기 일쑤였다.

// 재현이는 잘못된 수를 부를 때마다 0을 외쳐서, 가장 최근에 재민이가 쓴 수를 지우게 시킨다.

// 재민이는 이렇게 모든 수를 받아 적은 후 그 수의 합을 알고 싶어 한다. 재민이를 도와주자!

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
    (s->size)++;
}

// 스택에서 데이터 제거 (pop)
int pop_stack(STACK* s) {
    if (is_stack_empty(s)) {
        return 1;  // 비어있을 때 1 반환 (큐와 동일하게 처리)
    }
    node* temp = s->top;
    int data = temp->data;
    s->top = temp->next;
    (s->size)--;

    free(temp);
    return data;
}

int main() {

    int N;
    int temp;

    STACK s;
    init_STACK(&s);

    scanf("%d ", &N);

    for (int i=0; i<N; i++){
        scanf("%d ", &temp);

        if (temp == 0) pop_stack(&s);
        else push_stack(&s, temp);

    }

    int total =0;

    while (!is_stack_empty(&s)){
        total+=pop_stack(&s);
    }

    printf("%d ", total);

    return 0;
}
