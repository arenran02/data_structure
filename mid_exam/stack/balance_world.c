// 균형 잡힌 세상

// 세계는 균형이 잘 잡혀있어야 한다. 양과 음, 빛과 어둠 그리고 왼쪽 괄호와 오른쪽 괄호처럼 말이다.

// 정민이의 임무는 어떤 문자열이 주어졌을 때, 괄호들의 균형이 잘 맞춰져 있는지 판단하는 프로그램을 짜는 것이다.

// 문자열에 포함되는 괄호는 소괄호("()") 와 대괄호("[]")로 2종류이고, 문자열이 균형을 이루는 조건은 아래와 같다.

// 모든 왼쪽 소괄호("(")는 오른쪽 소괄호(")")와만 짝을 이뤄야 한다.
// 모든 왼쪽 대괄호("[")는 오른쪽 대괄호("]")와만 짝을 이뤄야 한다.
// 모든 오른쪽 괄호들은 자신과 짝을 이룰 수 있는 왼쪽 괄호가 존재한다.
// 모든 괄호들의 짝은 1:1 매칭만 가능하다. 즉, 괄호 하나가 둘 이상의 괄호와 짝지어지지 않는다.
// 짝을 이루는 두 괄호가 있을 때, 그 사이에 있는 문자열도 균형이 잡혀야 한다.
// 정민이를 도와 문자열이 주어졌을 때 균형잡힌 문자열인지 아닌지를 판단해보자.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 노드 정의
typedef struct node {
    char data;
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

void push_stack(STACK* s, char data) {
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->next = s->top;
    s->top = newnode;
    s->size++;
}

char pop_stack(STACK* s) {
    if (is_stack_empty(s)) return '\0';
    node* temp = s->top;
    char data = temp->data;
    s->top = temp->next;
    s->size--;
    free(temp);
    return data;
}

char peek_stack(STACK* s) {
    if (is_stack_empty(s)) return '\0';
    return s->top->data;
}

// 균형잡힌 괄호 검사 함수
int is_balanced(char* str) {
    STACK s;
    init_STACK(&s);

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        if (c == '(' || c == '[') {
            push_stack(&s, c);
        } else if (c == ')') {
            if (peek_stack(&s) == '(') {
                pop_stack(&s);
            } else {
                return 0;
            }
        } else if (c == ']') {
            if (peek_stack(&s) == '[') {
                pop_stack(&s);
            } else {
                return 0;
            }
        }
    }

    return is_stack_empty(&s);
}

int main() {

    // 문자열 입력
    char input[105];

    while (1) {

        // 문자열 입력
        fgets(input, sizeof(input), stdin);

        // 종료 조건: 입력이 단일 "."일 경우
        if (strcmp(input, ".\n") == 0 || strcmp(input, ".") == 0) break;

        if (is_balanced(input)) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }

    return 0;
}
