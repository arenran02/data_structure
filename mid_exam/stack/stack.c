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

int peek_stack(STACK* s) {
    if (is_stack_empty(s)) return -1;
    return s->top->data;
}

int main() {
    STACK s;
    init_STACK(&s);

    push_stack(&s, 10);
    push_stack(&s, 20);
    push_stack(&s, 30);

    printf("Pop: %d\n", pop_stack(&s));
    printf("Pop: %d\n", pop_stack(&s));
    printf("Pop: %d\n", pop_stack(&s));
    printf("Pop (empty): %d\n", pop_stack(&s));  // 비어있을 경우

    return 0;
}
