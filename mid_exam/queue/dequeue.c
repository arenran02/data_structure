// 정수를 저장하는 덱(Deque)를 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.

// 명령은 총 여덟 가지이다.

// push_front X: 정수 X를 덱의 앞에 넣는다.
// push_back X: 정수 X를 덱의 뒤에 넣는다.
// pop_front: 덱의 가장 앞에 있는 수를 빼고, 그 수를 출력한다. 만약, 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
// pop_back: 덱의 가장 뒤에 있는 수를 빼고, 그 수를 출력한다. 만약, 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
// size: 덱에 들어있는 정수의 개수를 출력한다.
// empty: 덱이 비어있으면 1을, 아니면 0을 출력한다.
// front: 덱의 가장 앞에 있는 정수를 출력한다. 만약 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
// back: 덱의 가장 뒤에 있는 정수를 출력한다. 만약 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 노드 구조체
typedef struct node {
    int data;
    struct node* prev;
    struct node* next;
} node;

// 덱 구조체
typedef struct {
    node* front;
    node* back;
    int size;
} DEQUE;

void init_deque(DEQUE* d) {
    d->front = NULL;
    d->back = NULL;
    d->size = 0;
}

int is_empty(DEQUE* d) {
    return d->size == 0;
}

void push_front(DEQUE* d, int value) {
    node* newnode = malloc(sizeof(node));
    newnode->data = value;
    newnode->prev = NULL;
    newnode->next = d->front;

    if (is_empty(d)) {
        d->back = newnode;
    } else {
        d->front->prev = newnode;
    }

    d->front = newnode;
    d->size++;
}

void push_back(DEQUE* d, int value) {
    node* newnode = malloc(sizeof(node));
    newnode->data = value;
    newnode->next = NULL;
    newnode->prev = d->back;

    if (is_empty(d)) {
        d->front = newnode;
    } else {
        d->back->next = newnode;
    }

    d->back = newnode;
    d->size++;
}

int pop_front(DEQUE* d) {
    if (is_empty(d)) return -1;

    node* temp = d->front;
    int value = temp->data;

    d->front = temp->next;
    if (d->front)
        d->front->prev = NULL;
    else
        d->back = NULL;

    free(temp);
    d->size--;
    return value;
}

int pop_back(DEQUE* d) {
    if (is_empty(d)) return -1;

    node* temp = d->back;
    int value = temp->data;

    d->back = temp->prev;
    if (d->back)
        d->back->next = NULL;
    else
        d->front = NULL;

    free(temp);
    d->size--;
    return value;
}

int front(DEQUE* d) {
    return is_empty(d) ? -1 : d->front->data;
}

int back(DEQUE* d) {
    return is_empty(d) ? -1 : d->back->data;
}

int main() {
    int N;
    scanf("%d", &N);
    getchar(); // 개행 제거

    DEQUE d;
    init_deque(&d);

    char command[30];

    for (int i = 0; i < N; i++) {
        fgets(command, sizeof(command), stdin);

        if (strncmp(command, "push_front", 10) == 0) {
            int x;
            sscanf(command + 11, "%d", &x);
            push_front(&d, x);
        } else if (strncmp(command, "push_back", 9) == 0) {
            int x;
            sscanf(command + 10, "%d", &x);
            push_back(&d, x);
        } else if (strncmp(command, "pop_front", 9) == 0) {
            printf("%d\n", pop_front(&d));
        } else if (strncmp(command, "pop_back", 8) == 0) {
            printf("%d\n", pop_back(&d));
        } else if (strncmp(command, "size", 4) == 0) {
            printf("%d\n", d.size);
        } else if (strncmp(command, "empty", 5) == 0) {
            printf("%d\n", is_empty(&d));
        } else if (strncmp(command, "front", 5) == 0) {
            printf("%d\n", front(&d));
        } else if (strncmp(command, "back", 4) == 0) {
            printf("%d\n", back(&d));
        }
    }

    return 0;
}
