// 상근이는 문자열에 폭발 문자열을 심어 놓았다. 폭발 문자열이 폭발하면 그 문자는 문자열에서 사라지며, 남은 문자열은 합쳐지게 된다.

// 폭발은 다음과 같은 과정으로 진행된다.

// 문자열이 폭발 문자열을 포함하고 있는 경우에, 모든 폭발 문자열이 폭발하게 된다. 남은 문자열을 순서대로 이어 붙여 새로운 문자열을 만든다.
// 새로 생긴 문자열에 폭발 문자열이 포함되어 있을 수도 있다.
// 폭발은 폭발 문자열이 문자열에 없을 때까지 계속된다.
// 상근이는 모든 폭발이 끝난 후에 어떤 문자열이 남는지 구해보려고 한다. 남아있는 문자가 없는 경우가 있다. 이때는 "FRULA"를 출력한다.

// 폭발 문자열은 같은 문자를 두 개 이상 포함하지 않는다.

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

// 스택 내용을 문자열로 변환 (역순이므로 뒤집기 필요)
void to_string(STACK* s, char* result) {
    int i = 0;
    node* cur = s->top;
    while (cur) {
        result[i++] = cur->data;
        cur = cur->next;
    }
    result[i] = '\0';

    // 뒤집기
    for (int j = 0; j < i / 2; j++) {
        char temp = result[j];
        result[j] = result[i - j - 1];
        result[i - j - 1] = temp;
    }
}

int main() {
    char str[1000001], bomb[37];
    scanf("%s", str);
    scanf("%s", bomb);
    int len_bomb = strlen(bomb);

    STACK s;
    init_STACK(&s);

    // 임시 배열로 폭발 검사용
    char check[37];

    for (int i = 0; str[i]; i++) {
        push_stack(&s, str[i]);

        // 폭발 문자열과 길이가 같아졌을 때만 검사
        // cur을 이용해서 글자를 순회하며 폭탄 글자와 같은지 비교함
        if (s.size >= len_bomb) {
            node* cur = s.top;
            int match = 1;
            for (int j = len_bomb - 1; j >= 0; j--) {
                if (!cur || cur->data != bomb[j]) {
                    match = 0;
                    break;
                }
                cur = cur->next;
            }

            if (match) {
                // 폭발 발생: 스택에서 제거
                for (int j = 0; j < len_bomb; j++) {
                    pop_stack(&s);
                }
            }
        }
    }

    char result[1000001];
    to_string(&s, result);

    if (strlen(result) == 0)
        printf("FRULA\n");
    else
        printf("%s\n", result);

    return 0;
}
