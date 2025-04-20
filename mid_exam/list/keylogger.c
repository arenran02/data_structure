// 창영이는 강산이의 비밀번호를 훔치기 위해서 강산이가 사용하는 컴퓨터에 키로거를 설치했다. 며칠을 기다린 끝에 창영이는 강산이가 비밀번호 창에 입력하는 글자를 얻어냈다.

// 키로거는 사용자가 키보드를 누른 명령을 모두 기록한다. 따라서, 강산이가 비밀번호를 입력할 때, 화살표나 백스페이스를 입력해도 정확한 비밀번호를 알아낼 수 있다. 

// 강산이가 비밀번호 창에서 입력한 키가 주어졌을 때, 강산이의 비밀번호를 알아내는 프로그램을 작성하시오. 강산이는 키보드로 입력한 키는 알파벳 대문자, 소문자, 숫자, 백스페이스, 화살표이다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 이중 연결 리스트 노드 정의
typedef struct node {
    char data;
    struct node* prev;
    struct node* next;
} node;

// 노드 생성
node* create_node(char data) {
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->prev = NULL;
    newnode->next = NULL;
    return newnode;
}

// 노드 삽입 (cursor 앞에)
void insert_before_cursor(node* cursor, char data) {
    node* newnode = create_node(data);
    newnode->prev = cursor->prev;
    newnode->next = cursor;
    cursor->prev->next = newnode;
    cursor->prev = newnode;
}

// 노드 삭제 (cursor 앞의 노드 삭제)
void delete_before_cursor(node* cursor) {
    if (cursor->prev->data == '\0') return;  // head 바로 뒤면 삭제 X
    node* to_delete = cursor->prev;
    to_delete->prev->next = cursor;
    cursor->prev = to_delete->prev;
    free(to_delete);
}

// 커서 왼쪽 이동
node* move_cursor_left(node* cursor, node* head) {
    if (cursor->prev != head) {
        cursor = cursor->prev;
    }
    return cursor;
}

// 커서 오른쪽 이동
node* move_cursor_right(node* cursor, node* tail) {
    if (cursor != tail) {
        cursor = cursor->next;
    }
    return cursor;
}

int main() {
    int T;
    scanf("%d", &T);
    getchar(); // 줄바꿈 제거

    while (T--) {
        char input[1000001];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // 개행 제거

        // 더미 노드 생성
        node* head = create_node('\0');
        node* tail = create_node('\0');
        head->next = tail;
        tail->prev = head;

        node* cursor = tail;

        for (int i = 0; input[i]; i++) {
            char c = input[i];
            if (c == '<') {
                cursor = move_cursor_left(cursor, head);
            } else if (c == '>') {
                cursor = move_cursor_right(cursor, tail);
            } else if (c == '-') {
                delete_before_cursor(cursor);
            } else {
                insert_before_cursor(cursor, c);
            }
        }

        // 출력
        node* cur = head->next;
        while (cur != tail) {
            putchar(cur->data);
            cur = cur->next;
        }
        putchar('\n');

        // 메모리 해제
        cur = head;
        while (cur) {
            node* next = cur->next;
            free(cur);
            cur = next;
        }
    }

    return 0;
}
