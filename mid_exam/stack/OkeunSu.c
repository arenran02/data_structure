// 크기가 N인 수열 A = A1, A2, ..., AN이 있다. 수열의 각 원소 Ai에 대해서 오큰수 NGE(i)를 구하려고 한다. 
// Ai의 오큰수는 오른쪽에 있으면서 Ai보다 큰 수 중에서 가장 왼쪽에 있는 수를 의미한다. 그러한 수가 없는 경우에 오큰수는 -1이다.

// 예를 들어, A = [3, 5, 2, 7]인 경우 NGE(1) = 5, NGE(2) = 7, NGE(3) = 7, NGE(4) = -1이다. 
// A = [9, 5, 4, 8]인 경우에는 NGE(1) = -1, NGE(2) = 8, NGE(3) = 8, NGE(4) = -1이다.

#include <stdio.h>
#include <stdlib.h>

// 연결 리스트 노드 정의
typedef struct node {
    int data;
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

int is_stack_empty(STACK* s) {
    return s->size == 0;
}

void push_stack(STACK* s, int data) {
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->next = s->top;
    s->top = newnode;
    s->size++;
}

int pop_stack(STACK* s) {
    if (is_stack_empty(s)) return -1;
    node* temp = s->top;
    int data = temp->data;
    s->top = temp->next;
    s->size--;
    free(temp);
    return data;
}

int peek_stack(STACK* s) {
    if (is_stack_empty(s)) return -1;
    return s->top->data;
}

int main() {
    int N;
    scanf("%d", &N);
    
    int A[1000000];
    int result[1000000];

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        result[i] = -1; // 초기값: 오큰수가 없는 경우
    }

    STACK s;
    init_STACK(&s);

    for (int i = 0; i < N; i++) {
        // 현재 수가 스택 top이 가리키는 값보다 크면 -> 오큰수 발견
        while (!is_stack_empty(&s) && A[peek_stack(&s)] < A[i]) {
            int index = pop_stack(&s);
            result[index] = A[i];
        }
        push_stack(&s, i);  // 인덱스 저장
    }

    // 결과 출력
    for (int i = 0; i < N; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
