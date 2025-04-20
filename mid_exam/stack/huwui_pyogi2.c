// 후위 표기식과 각 피연산자에 대응하는 값들이 주어져 있을 때, 그 식을 계산하는 프로그램을 작성하시오.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 🔧 실수(double)를 저장하는 연결 리스트 노드
typedef struct node {
    double data;
    struct node* next;
} node;

// 🔧 스택 구조체
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

// push
void push_stack(STACK* s, double data) {
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->next = s->top;
    s->top = newnode;
    s->size++;
}

// pop
double pop_stack(STACK* s) {
    if (is_stack_empty(s)) return 0.0;
    node* temp = s->top;
    double data = temp->data;
    s->top = temp->next;
    s->size--;
    free(temp);
    return data;
}

int main() {
    int N;
    char expr[101];
    double values[26];  // A-Z에 대응하는 값 저장

    scanf("%d", &N);
    scanf("%s", expr);

    // A~Z에 해당하는 값 입력
    for (int i = 0; i < N; i++) {
        scanf("%lf", &values[i]);
    }

    STACK s;
    init_STACK(&s);

    for (int i = 0; expr[i]; i++) {
        char c = expr[i];

        if (isalpha(c)) {
            // 피연산자 → 대응 값 push
            push_stack(&s, values[c - 'A']);
        } else {
            // 연산자 → 두 개 pop 후 계산
            double b = pop_stack(&s);
            double a = pop_stack(&s);
            double res = 0.0;

            switch (c) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
            }

            push_stack(&s, res);
        }
    }

    // 최종 결과 출력
    printf("%.2lf\n", pop_stack(&s));
    return 0;
}
