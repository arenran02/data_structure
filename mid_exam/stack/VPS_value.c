// 괄호의 값

// 4개의 기호 ‘(’, ‘)’, ‘[’, ‘]’를 이용해서 만들어지는 괄호열 중에서 올바른 괄호열이란 다음과 같이 정의된다.

// 한 쌍의 괄호로만 이루어진 ‘()’와 ‘[]’는 올바른 괄호열이다.
// 만일 X가 올바른 괄호열이면 ‘(X)’이나 ‘[X]’도 모두 올바른 괄호열이 된다.
// X와 Y 모두 올바른 괄호열이라면 이들을 결합한 XY도 올바른 괄호열이 된다.
// 예를 들어 ‘(()[[]])’나 ‘(())[][]’ 는 올바른 괄호열이지만 ‘([)]’ 나 ‘(()()[]’ 은 모두 올바른 괄호열이 아니다. 
// 우리는 어떤 올바른 괄호열 X에 대하여 그 괄호열의 값(괄호값)을 아래와 같이 정의하고 값(X)로 표시한다.

// ‘()’ 인 괄호열의 값은 2이다.
// ‘[]’ 인 괄호열의 값은 3이다.
// ‘(X)’ 의 괄호값은 2×값(X) 으로 계산된다.
// ‘[X]’ 의 괄호값은 3×값(X) 으로 계산된다.
// 올바른 괄호열 X와 Y가 결합된 XY의 괄호값은 값(XY)= 값(X)+값(Y) 로 계산된다.
// 예를 들어 ‘(()[[]])([])’ 의 괄호값을 구해보자. ‘()[[]]’ 의 괄호값이 2 + 3×3=11 이므로 ‘(()[[]])’의 괄호값은 2×11=22 이다. 
// 그리고 ‘([])’의 값은 2×3=6 이므로 전체 괄호열의 값은 22 + 6 = 28 이다.

// 여러분이 풀어야 할 문제는 주어진 괄호열을 읽고 그 괄호값을 앞에서 정의한대로 계산하여 출력하는 것이다.

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct {
    node* top;
    int size;
} STACK;

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

int top_stack(STACK* s) {
    if (is_stack_empty(s)) return -1;
    return s->top->data;
}

int compute_bracket_value(const char* str) {
    STACK s;
    init_STACK(&s);

    for (int i = 0; str[i]; i++) {
        char ch = str[i];
        if (ch == '(') {
            push_stack(&s, -1);  // '('를 -1로
        } else if (ch == '[') {
            push_stack(&s, -2);  // '['를 -2로
        } else if (ch == ')' || ch == ']') {
            int base = (ch == ')') ? -1 : -2;
            int mul = (ch == ')') ? 2 : 3;
            int temp = 0;

            while (!is_stack_empty(&s) && top_stack(&s) > 0) {
                temp += pop_stack(&s);
            }

            if (is_stack_empty(&s) || pop_stack(&s) != base) {
                // 짝이 안 맞음
                return 0;
            }

            if (temp == 0) temp = 1;
            push_stack(&s, temp * mul);
        } else {
            return 0;  // 잘못된 문자
        }
    }

    int result = 0;
    while (!is_stack_empty(&s)) {
        int val = pop_stack(&s);
        if (val < 0) return 0;  // 괄호가 남아있으면 오류
        result += val;
    }
    return result;
}

int main() {
    char input[31];
    scanf("%s", input);

    int result = compute_bracket_value(input);
    printf("%d\n", result);

    return 0;
}
