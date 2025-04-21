#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)


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

    char line[2000];  // 괄호 문자열 최대 길이 제한 2000
    
    for (int i = 0; i < N; i++) {
        fgets(line, sizeof(line), stdin);

        STACK s;
        init_STACK(&s);

        // 연산 개수
        int count = 0;

        for (int j = 0; j < strlen(line); j++) {
            if (line[j] == '\n') break; // 줄 끝


            if (line[j] == '{') {
                push_stack(&s, '{');
            }

			// 순서 맞지 않은 (예시: '}{' 
            else if (line[j] == '}') {
                if (pop_stack(&s)) {    // pop 할 괄호가 없을 때
                    count++;
                    push_stack(&s, '{');
                }
            }
        }

        if (!is_stack_empty(&s)) {
            // stack에 남은 개수 / 2 를 count에 추가
            count+=s.size/2;
            printf("%d\n", count);

        }
        else {
            printf("%d\n", count);
        }

    }

    return 0;
}
