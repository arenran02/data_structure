#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct Node {
    Point data;
    struct Node* next;
} Node;

// 노드 생성
Node* createNode(Point p) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = p;
    newNode->next = NULL;
    return newNode;
}

// 좌표 비교 (정렬 기준)
int compare(Point a, Point b) {
    if (a.y != b.y)
        return a.y - b.y;
    return a.x - b.x;
}

// 정렬 삽입
void insertSorted(Node** head, Point p) {
    Node* newNode = createNode(p);

    if (*head == NULL || compare(p, (*head)->data) < 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* curr = *head;
    while (curr->next != NULL && compare(p, curr->next->data) > 0) {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
}

// 인덱스 찾기
int findIndex(Node* head, Point p) {
    int index = 0;
    while (head != NULL) {
        if (head->data.x == p.x && head->data.y == p.y)
            return index;
        head = head->next;
        index++;
    }
    return -1;
}

// 리스트 출력
void printList(Node* head) {
    while (head != NULL) {
        printf("(%d, %d) -> ", head->data.x, head->data.y);
        head = head->next;
    }
    printf("NULL\n");
}

// 메모리 해제
void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int n, x, y;
    Node* head = NULL;

    printf("입력할 좌표 개수: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("좌표 %d 입력 (x y): ", i + 1);
        scanf("%d %d", &x, &y);
        Point p = {x, y};
        insertSorted(&head, p);
    }

    printf("\n정렬된 리스트:\n");
    printList(head);

    printf("\n찾을 좌표 입력 (x y): ");
    scanf("%d %d", &x, &y);
    Point target = {x, y};
    int index = findIndex(head, target);

    if (index != -1)
        printf("해당 좌표는 리스트의 %d번째에 있습니다.\n", index);
    else
        printf("해당 좌표는 리스트에 없습니다.\n");

    freeList(head);
    return 0;
}
