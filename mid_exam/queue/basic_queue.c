#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 노드 구조체
typedef struct node {
    int data;
    struct node* next;
} node;

// 큐 구조체
typedef struct {
    node* front;
    node* rear;
    int size;
} QUEUE;

// 큐 초기화
void init_QUEUE(QUEUE* q) {
    q->front = q->rear = NULL;
    q->size = 0;
}

// 큐가 비었는지 확인
int is_empty(QUEUE* q) {
    return q->size == 0;
}

// 원소 추가
void push(QUEUE* q, int data) {
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;

    if (is_empty(q)) {
        q->front = newnode;
    } else {
        q->rear->next = newnode;
    }

    q->rear = newnode;
    q->size++;
}

// 원소 제거 및 반환
int pop(QUEUE* q) {
    if (is_empty(q)) return -1;

    node* temp = q->front;
    int data = temp->data;

    q->front = temp->next;
    free(temp);
    q->size--;

    if (q->size == 0)
        q->rear = NULL;

    return data;
}

// 가장 앞 원소 확인
int front(QUEUE* q) {
    if (is_empty(q)) return -1;
    return q->front->data;
}

// 가장 뒤 원소 확인
int back(QUEUE* q) {
    if (is_empty(q)) return -1;
    return q->rear->data;
}

int main() {
    int N;
    scanf("%d", &N);
    getchar(); // 개행 제거

    QUEUE q;
    init_QUEUE(&q);

    char command[20];
    for (int i = 0; i < N; i++) {
        fgets(command, sizeof(command), stdin);

        if (strncmp(command, "push", 4) == 0) {
            int x;
            sscanf(command + 5, "%d", &x);
            push(&q, x);
        } else if (strncmp(command, "pop", 3) == 0) {
            printf("%d\n", pop(&q));
        } else if (strncmp(command, "size", 4) == 0) {
            printf("%d\n", q.size);
        } else if (strncmp(command, "empty", 5) == 0) {
            printf("%d\n", is_empty(&q));
        } else if (strncmp(command, "front", 5) == 0) {
            printf("%d\n", front(&q));
        } else if (strncmp(command, "back", 4) == 0) {
            printf("%d\n", back(&q));
        }
    }

    return 0;
}
