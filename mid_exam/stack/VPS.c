// 괄호

// 괄호 문자열(Parenthesis String, PS)은 두 개의 괄호 기호인 ‘(’ 와 ‘)’ 만으로 구성되어 있는 문자열이다. 
// 그 중에서 괄호의 모양이 바르게 구성된 문자열을 올바른 괄호 문자열(Valid PS, VPS)이라고 부른다. 
// 한 쌍의 괄호 기호로 된 “( )” 문자열은 기본 VPS 이라고 부른다. 만일 x 가 VPS 라면 이것을 하나의 괄호에 넣은 새로운 문자열 “(x)”도 VPS 가 된다. 
// 그리고 두 VPS x 와 y를 접합(concatenation)시킨 새로운 문자열 xy도 VPS 가 된다. 
// 예를 들어 “(())()”와 “((()))” 는 VPS 이지만 “(()(”, “(())()))” , 그리고 “(()” 는 모두 VPS 가 아닌 문자열이다. 

// 여러분은 입력으로 주어진 괄호 문자열이 VPS 인지 아닌지를 판단해서 그 결과를 YES 와 NO 로 나타내어야 한다. 

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

// 스택이 비었는지 확인
int is_stack_empty(STACK* s) {
    return s->size == 0;
}

// push
void push_stack(STACK* s, char data) {
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->next = s->top;
    s->top = newnode;
    (s->size)++;
}

// pop
int pop_stack(STACK* s) {
    if (is_stack_empty(s)) return 1; // 실패 시 1 반환

    node* temp = s->top;
    s->top = temp->next;
    (s->size)--;

    free(temp);
    return 0; // 성공
}

int main() {
    int N;
    scanf("%d", &N);
    getchar();  // 줄바꿈 소비

    char line[110];  // 괄호 문자열 최대 길이 제한
    for (int i = 0; i < N; i++) {
        fgets(line, sizeof(line), stdin);

        STACK s;
        init_STACK(&s);

        int valid = 1;
        for (int j = 0; j < strlen(line); j++) {
            if (line[j] == '\n') break; // 줄 끝

            if (line[j] == '(') {
                push_stack(&s, '(');
            }
			// 순서 맞지 않은 (예시: ')(' ) 괄호 조기 판단
            else if (line[j] == ')') {
                if (pop_stack(&s)) {
                    valid = 0;
                    break;
                }
            }
        }

        if (!is_stack_empty(&s)) valid = 0;

        printf(valid ? "YES\n" : "NO\n");
    }

    return 0;
}
