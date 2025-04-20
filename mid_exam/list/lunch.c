// 점심시간이 되면 반 학생 모두가 한 줄로 줄을 서서 급식을 탄다. 그런데 매일 같이 앞자리에 앉은 학생들이 앞에 줄을 서 먼저 점심을 먹고, 
// 뒷자리에 앉은 학생들은 뒤에 줄을 서 늦게 점심을 먹게 된다. 어떻게 하면 이러한 상황을 바꾸어 볼 수 있을까 고민하던 중 선생님이 한 가지 방법을 내 놓았다. 그 방법은 다음과 같다.

// 학생들이 한 줄로 줄을 선 후, 첫 번째 학생부터 차례로 번호를 뽑는다. 첫 번째로 줄을 선 학생은 무조건 0번 번호를 받아 제일 앞에 줄을 선다. 
// 두 번째로 줄을 선 학생은 0번 또는 1번 둘 중 하나의 번호를 뽑는다. 0번을 뽑으면 그 자리에 그대로 있고, 1번을 뽑으면 바로 앞의 학생 앞으로 가서 줄을 선다. 세 번째로 줄을 선 학생은 0, 1 또는 2 중 하나의 번호를 뽑는다. 그리고 뽑은 번호만큼 앞자리로 가서 줄을 선다. 마지막에 줄을 선 학생까지 이와 같은 방식으로 뽑은 번호만큼 앞으로 가서 줄을 서게 된다. 각자 뽑은 번호는 자신이 처음에 선 순서보다는 작은 수이다.

// 예를 들어 5명의 학생이 줄을 서고, 첫 번째로 줄을 선 학생부터 다섯 번째로 줄을 선 학생까지 차례로 0, 1, 1, 3, 2번의 번호를 뽑았다고 하자, 
// 첫 번째 학생부터 다섯 번째 학생까지 1부터 5로 표시하면 학생들이 줄을 선 순서는 다음과 같이 된다.

// 첫 번째 학생이 번호를 뽑은 후 : 1
// 두 번째 학생이 번호를 뽑은 후 : 2 1
// 세 번째 학생이 번호를 뽑은 후 : 2 3 1
// 네 번째 학생이 번호를 뽑은 후 : 4 2 3 1
// 다섯 번째 학생이 번호를 뽑은 후 : 4 2 5 3 1
// 따라서 최종적으로 학생들이 줄을 선 순서는 4, 2, 5, 3, 1이 된다.

// 줄을 선 학생들이 차례로 뽑은 번호가 주어질 때 학생들이 최종적으로 줄을 선 순서를 출력하는 프로그램을 작성하시오.

#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int student;
    struct Node* next;
} Node;

// 새로운 노드 생성 함수
Node* create_node(int student) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->student = student;
    new_node->next = NULL;
    return new_node;
}

// 연결 리스트에 특정 위치에 노드 삽입
void insert_node(Node** head, int index, int student) {
    Node* new_node = create_node(student);

    // 맨 앞에 삽입하는 경우
    if (index == 0) {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    // 중간이나 끝에 삽입
    Node* temp = *head;
    for (int i = 0; i < index - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp != NULL) {
        new_node->next = temp->next;
        temp->next = new_node;
    }
}

// 연결 리스트 출력
void print_list(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->student);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n); // 학생 수 입력

    int* nums = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]); // 각 학생이 뽑은 번호 입력
    }

    Node* head = NULL;

    for (int i = 0; i < n; i++) {
        insert_node(&head, i - nums[i], i + 1);
    }

    print_list(head);

    // 메모리 해제
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    free(nums);
    return 0;
}
