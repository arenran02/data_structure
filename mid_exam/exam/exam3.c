#include <stdio.h> 
#include <stdlib.h>
#pragma warning(disable:4996)

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
    QUEUE q;
    init_QUEUE(&q);  // 큐 초기화

    int N;
    int comm, id=0;

    int max_size=0;
    int max_id=0;

    scanf("%d", &N);

    for (int i=0; i<N; i++){
        scanf("%d", &comm);

        // 줄을 섰을 때
        if (comm==1){
            scanf("%d", &id);
            push(&q, id);

            if (max_size<=q.size) {
                
                if (max_id<back(&q)){
                    max_id=back(&q);
                }
                
                max_size=q.size;
            }
        }

        // 사람이 빠졌을 때
        else if (comm==2){
            pop(&q);
        }
    }
    
    printf("%d %d", max_size, max_id);

    return 0;
}
