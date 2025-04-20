// 정수를 저장하는 스택을 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.

// 명령은 총 다섯 가지이다.

// push X: 정수 X를 스택에 넣는 연산이다.
// pop: 스택에서 가장 위에 있는 정수를 빼고, 그 수를 출력한다. 만약 스택에 들어있는 정수가 없는 경우에는 -1을 출력한다.
// size: 스택에 들어있는 정수의 개수를 출력한다.
// empty: 스택이 비어있으면 1, 아니면 0을 출력한다.
// top: 스택의 가장 위에 있는 정수를 출력한다. 만약 스택에 들어있는 정수가 없는 경우에는 -1을 출력한다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// 스택 함수
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
    getchar(); // 개행 제거

    STACK s;
    init_STACK(&s);

    char command[100];

    for (int i = 0; i < N; i++) {
        fgets(command, sizeof(command), stdin);

        if (strncmp(command, "push", 4) == 0) {
            int x;
            sscanf(command + 5, "%d", &x); // "push X"에서 X 읽기
            push_stack(&s, x);
        } else if (strncmp(command, "pop", 3) == 0) {
            printf("%d\n", pop_stack(&s));
        } else if (strncmp(command, "size", 4) == 0) {
            printf("%d\n", s.size);
        } else if (strncmp(command, "empty", 5) == 0) {
            printf("%d\n", is_stack_empty(&s) ? 1 : 0);
        } else if (strncmp(command, "top", 3) == 0) {
            printf("%d\n", peek_stack(&s));
        }
    }

    return 0;
}
