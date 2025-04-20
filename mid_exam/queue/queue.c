#include <stdio.h> 
#include <stdlib.h>

typedef struct
{
	struct node* next;
	int data;
}node;

typedef struct
{
	node* rear;
	node* front;
	int size;
} QUEUE;

void init_QUEUE(QUEUE* q)
{
	q->front = q->rear = NULL;
	q->size = 0;
}

int is_empty(QUEUE* q)
{
	if (q->size <= 0)
		return 1;
	else
		return 0;
}

void push(QUEUE* q, int data)
{
	node* newnode = malloc(sizeof(node));
	newnode->data = data;
	newnode->next = NULL;
	if (is_empty(q))
	{
		q->front = newnode;
	}
	else
	{
		q->rear->next = newnode;
	}
	q->rear = newnode;
	(q->size)++;
}

int pop(QUEUE* q)
{
	if (!is_empty(q))
	{
		node* temp;
		temp = q->front;
		int data = temp->data;
		q->front = temp->next;
		(q->size)--;

		free(temp);

		return data;
	}
	else
		return 1;
}


int main()
{
    QUEUE q;
    init_QUEUE(&q);  // 큐 초기화

    // 큐에 데이터 넣기 (push)
    push(&q, 10);
    push(&q, 20);
    push(&q, 30);
    printf("3개의 데이터를 큐에 삽입했습니다.\n");

    // 큐에서 데이터 꺼내기 (pop)
    while (!is_empty(&q)) {
        int value = pop(&q);
        printf("pop: %d\n", value);
    }

    // 빈 큐 상태 확인
    if (is_empty(&q)) {
        printf("큐가 비어 있습니다.\n");
    }

    return 0;
}
