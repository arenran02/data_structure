#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 새로운 노드 생성
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 인덱스 위치에 노드 추가
void insertAtIndex(Node** head, int index, int data) {
    Node* newNode = createNode(data);
    if (index == 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* current = *head;
    int i = 0;
    while (current && i < index - 1) {
        current = current->next;
        i++;
    }

    if (!current) {
        printf("인덱스 범위 초과\n");
        free(newNode);
        return;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// 인덱스 위치의 노드 삭제
void deleteAtIndex(Node** head, int index) {
    if (*head == NULL) {
        printf("리스트가 비어있습니다\n");
        return;
    }

    Node* temp;
    if (index == 0) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    Node* current = *head;
    int i = 0;
    while (current->next && i < index - 1) {
        current = current->next;
        i++;
    }

    if (!current->next) {
        printf("인덱스 범위 초과\n");
        return;
    }

    temp = current->next;
    current->next = temp->next;
    free(temp);
}

// 리스트 출력
void printList(Node* head) {
    Node* current = head;
    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 메모리 해제
void freeList(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// 메인 함수에서 테스트
int main() {
    Node* head = NULL;

    insertAtIndex(&head, 0, 10);  // 10
    insertAtIndex(&head, 1, 20);  // 10 -> 20
    insertAtIndex(&head, 1, 15);  // 10 -> 15 -> 20
    insertAtIndex(&head, 3, 25);  // 10 -> 15 -> 20 -> 25
    printList(head);

    deleteAtIndex(&head, 2);      // 10 -> 15 -> 25
    printList(head);

    insertAtIndex(&head, 1, 100); // 10 -> 100 -> 15 -> 25
    printList(head);

    deleteAtIndex(&head, 0);      // 100 -> 15 -> 25
    printList(head);

    freeList(head);
    return 0;
}
