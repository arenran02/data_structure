#include <stdio.h>
#include <stdlib.h>

// 🔧 이중 연결 리스트 노드
typedef struct node {
    char data;
    struct node* prev;
    struct node* next;
} node;

// 🔧 노드 생성
node* create_node(char data) {
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->prev = NULL;
    newnode->next = NULL;
    return newnode;
}

int main() {
    char str[600001];
    int M;
    scanf("%s", str);
    scanf("%d", &M);
    getchar(); // 개행 제거

    // 🔧 더미 노드 (head ↔ tail 사이에 문자가 들어감)
    node* head = create_node('\0');  // 더미 헤드
    node* tail = create_node('\0');  // 더미 테일
    head->next = tail;
    tail->prev = head;

    // 🔧 초기 문자열 넣기
    node* cursor = tail;
    for (int i = 0; str[i]; i++) {
        node* newnode = create_node(str[i]);

        // head <-> ... <-> cursor 사이에 삽입
        newnode->prev = cursor->prev;
        newnode->next = cursor;
        cursor->prev->next = newnode;
        cursor->prev = newnode;
    }

    // 🔧 명령어 처리
    for (int i = 0; i < M; i++) {
        char cmd;
        scanf("%c", &cmd);

        if (cmd == 'L') {
            if (cursor->prev != head)
                cursor = cursor->prev;
        } else if (cmd == 'D') {
            if (cursor != tail)
                cursor = cursor->next;
        } else if (cmd == 'B') {
            if (cursor->prev != head) {
                node* to_delete = cursor->prev;
                to_delete->prev->next = cursor;
                cursor->prev = to_delete->prev;
                free(to_delete);
            }
        } else if (cmd == 'P') {
            char x;
            scanf(" %c", &x);
            node* newnode = create_node(x);

            newnode->prev = cursor->prev;
            newnode->next = cursor;
            cursor->prev->next = newnode;
            cursor->prev = newnode;
        }

        getchar(); // 개행 소비
    }

    // 🔧 결과 출력
    node* cur = head->next;
    while (cur != tail) {
        putchar(cur->data);
        cur = cur->next;
    }

    // 🔧 메모리 해제
    cur = head;
    while (cur != NULL) {
        node* next = cur->next;
        free(cur);
        cur = next;
    }

    return 0;
}
