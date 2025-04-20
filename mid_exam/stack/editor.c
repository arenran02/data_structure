// 한 줄로 된 간단한 에디터를 구현하려고 한다. 이 편집기는 영어 소문자만을 기록할 수 있는 편집기로, 최대 600,000글자까지 입력할 수 있다.

// 이 편집기에는 '커서'라는 것이 있는데, 커서는 문장의 맨 앞(첫 번째 문자의 왼쪽), 문장의 맨 뒤(마지막 문자의 오른쪽),
//  또는 문장 중간 임의의 곳(모든 연속된 두 문자 사이)에 위치할 수 있다. 즉 길이가 L인 문자열이 현재 편집기에 입력되어 있으면, 커서가 위치할 수 있는 곳은 L+1가지 경우가 있다.

// 이 편집기가 지원하는 명령어는 다음과 같다.

// L	커서를 왼쪽으로 한 칸 옮김 (커서가 문장의 맨 앞이면 무시됨)
// D	커서를 오른쪽으로 한 칸 옮김 (커서가 문장의 맨 뒤이면 무시됨)
// B	커서 왼쪽에 있는 문자를 삭제함 (커서가 문장의 맨 앞이면 무시됨)
// 삭제로 인해 커서는 한 칸 왼쪽으로 이동한 것처럼 나타나지만, 실제로 커서의 오른쪽에 있던 문자는 그대로임
// P $	$라는 문자를 커서 왼쪽에 추가함
// 초기에 편집기에 입력되어 있는 문자열이 주어지고, 그 이후 입력한 명령어가 차례로 주어졌을 때, 
// 모든 명령어를 수행하고 난 후 편집기에 입력되어 있는 문자열을 구하는 프로그램을 작성하시오. 
// 단, 명령어가 수행되기 전에 커서는 문장의 맨 뒤에 위치하고 있다고 한다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 🔧 노드 정의
typedef struct node {
    char data;
    struct node* next;
} node;

// 🔧 스택 구조체 정의
typedef struct {
    node* top;
    int size;
} STACK;

// 🔧 스택 초기화
void init_STACK(STACK* s) {
    s->top = NULL;
    s->size = 0;
}

// 🔧 스택이 비었는지 확인
int is_stack_empty(STACK* s) {
    return s->size == 0;
}

// 🔧 스택에 데이터 추가
void push_stack(STACK* s, char data) {
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->next = s->top;
    s->top = newnode;
    s->size++;
}

// 🔧 스택에서 데이터 제거
char pop_stack(STACK* s) {
    if (is_stack_empty(s)) return '\0';

    node* temp = s->top;
    char data = temp->data;
    s->top = temp->next;
    s->size--;
    free(temp);
    return data;
}

// 🔧 스택 뒤집어서 출력 (왼쪽 스택 출력용)
void reverse_and_print(STACK* s) {
    STACK temp;
    init_STACK(&temp);

    while (!is_stack_empty(s)) {
        push_stack(&temp, pop_stack(s));
    }

    while (!is_stack_empty(&temp)) {
        putchar(pop_stack(&temp));
    }
}

int main() {
    char initial[600001];
    int N;
    scanf("%s", initial);
    scanf("%d", &N);
    getchar(); // 개행 제거

    // 스택 두 개: 커서 왼쪽, 오른쪽
    STACK left, right;
    init_STACK(&left);
    init_STACK(&right);

    // 초기 문자열은 전부 왼쪽 스택에 push
    for (int i = 0; initial[i] != '\0'; i++) {
        push_stack(&left, initial[i]);
    }

    for (int i = 0; i < N; i++) {
        char cmd;
        scanf("%c", &cmd);

        if (cmd == 'L') {
            if (!is_stack_empty(&left)) {
                push_stack(&right, pop_stack(&left));
            }
        } else if (cmd == 'D') {
            if (!is_stack_empty(&right)) {
                push_stack(&left, pop_stack(&right));
            }
        } else if (cmd == 'B') {
            if (!is_stack_empty(&left)) {
                pop_stack(&left);
            }
        } else if (cmd == 'P') {
            char x;
            scanf(" %c", &x);
            push_stack(&left, x);
        }

        getchar(); // 개행 소비
    }

    // 왼쪽 스택 출력 (역순으로 뒤집어 출력)
    reverse_and_print(&left);

    // 오른쪽 스택 출력 (그대로 pop)
    while (!is_stack_empty(&right)) {
        putchar(pop_stack(&right));
    }

    return 0;
}
