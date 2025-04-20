// 정수를 저장하는 스택을 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.

// 명령은 총 다섯 가지이다.

// 1 X: 정수 X를 스택에 넣는다. (1 ≤ X ≤ 100,000)
// 2: 스택에 정수가 있다면 맨 위의 정수를 빼고 출력한다. 없다면 -1을 대신 출력한다.
// 3: 스택에 들어있는 정수의 개수를 출력한다.
// 4: 스택이 비어있으면 1, 아니면 0을 출력한다.
// 5: 스택에 정수가 있다면 맨 위의 정수를 출력한다. 없다면 -1을 대신 출력한다.

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

int is_stack_empty(STACK* s) {
    return s->size == 0;
}

void push_stack(STACK* s, int data) {
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->next = s->top;
    s->top = newnode;
    s->size++;
}

int pop_stack(STACK* s) {
    if (is_stack_empty(s)) return -1;

    node* temp = s->top;
    int data = temp->data;
    s->top = temp->next;
    s->size--;
    free(temp);
    return data;
}

int peek_stack(STACK* s) {
    if (is_stack_empty(s)) return -1;
    return s->top->data;
}

int main() {
    int N;
    scanf("%d", &N);

    STACK s;
    init_STACK(&s);

    for (int i = 0; i < N; i++) {
        int cmd;
        scanf("%d", &cmd);

        if (cmd == 1) {
            int x;
            scanf("%d", &x);
            push_stack(&s, x);
        } else if (cmd == 2) {
            printf("%d\n", pop_stack(&s));
        } else if (cmd == 3) {
            printf("%d\n", s.size);
        } else if (cmd == 4) {
            printf("%d\n", is_stack_empty(&s) ? 1 : 0);
        } else if (cmd == 5) {
            printf("%d\n", peek_stack(&s));
        }
    }

    return 0;
}

