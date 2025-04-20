// 단어 뒤집기 2

// 문자열 S가 주어졌을 때, 이 문자열에서 단어만 뒤집으려고 한다.

// 먼저, 문자열 S는 아래와과 같은 규칙을 지킨다.

// 알파벳 소문자('a'-'z'), 숫자('0'-'9'), 공백(' '), 특수 문자('<', '>')로만 이루어져 있다.
// 문자열의 시작과 끝은 공백이 아니다.
// '<'와 '>'가 문자열에 있는 경우 번갈아가면서 등장하며, '<'이 먼저 등장한다. 또, 두 문자의 개수는 같다.
// 태그는 '<'로 시작해서 '>'로 끝나는 길이가 3 이상인 부분 문자열이고, '<'와 '>' 사이에는 알파벳 소문자와 공백만 있다. 
// 단어는 알파벳 소문자와 숫자로 이루어진 부분 문자열이고, 연속하는 두 단어는 공백 하나로 구분한다. 태그는 단어가 아니며, 태그와 단어 사이에는 공백이 없다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// 스택 함수 정의
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

void flush_stack(STACK* s) {
    while (!is_stack_empty(s)) {
        printf("%c", pop_stack(s));
    }
}

int main() {
    char str[100001];
    fgets(str, sizeof(str), stdin);

    STACK s;
    init_STACK(&s);

    int in_tag = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        if (c == '<') {
            // 단어 뒤집기 마무리하고 태그 출력 시작
            flush_stack(&s);
            in_tag = 1;
            printf("%c", c);
        }
        else if (c == '>') {
            in_tag = 0;
            printf("%c", c);
        }
        else if (in_tag) {
            // 태그 안: 그대로 출력
            printf("%c", c);
        }
        else {
            // 태그 밖
            if (c == ' ' || c == '\n') {
                flush_stack(&s);
                printf("%c", c);
            } else {
                push_stack(&s, c);
            }
        }
    }

    // 마지막 남은 단어 뒤집기
    flush_stack(&s);

    return 0;
}
