// 선영이는 주말에 할 일이 없어서 새로운 언어 AC를 만들었다. AC는 정수 배열에 연산을 하기 위해 만든 언어이다. 이 언어에는 두 가지 함수 R(뒤집기)과 D(버리기)가 있다.

// 함수 R은 배열에 있는 수의 순서를 뒤집는 함수이고, D는 첫 번째 수를 버리는 함수이다. 배열이 비어있는데 D를 사용한 경우에는 에러가 발생한다.

// 함수는 조합해서 한 번에 사용할 수 있다. 예를 들어, "AB"는 A를 수행한 다음에 바로 이어서 B를 수행하는 함수이다. 예를 들어, "RDD"는 배열을 뒤집은 다음 처음 두 수를 버리는 함수이다.

// 배열의 초기값과 수행할 함수가 주어졌을 때, 최종 결과를 구하는 프로그램을 작성하시오.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100001

int deque[MAX];
int front = 0, rear = 0;

void reset_deque() {
    front = 0;
    rear = 0;
}

void push_back(int x) {
    deque[rear++] = x;
}

int size() {
    return rear - front;
}

int is_empty() {
    return front == rear;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        char p[100001];
        int n;
        char input[400001];
        
        scanf("%s", p);
        scanf("%d", &n);
        scanf("%s", input);

        reset_deque();

        // 배열 파싱
        int num = 0;
        int i = 0;
        if (n > 0) {
            while (input[i] != '\0') {
                if (input[i] >= '0' && input[i] <= '9') {
                    num = num * 10 + (input[i] - '0');
                } else if (input[i] == ',' || input[i] == ']') {
                    push_back(num);
                    num = 0;
                }
                i++;
            }
        }

        int reversed = 0;
        int error = 0;

        for (int j = 0; p[j]; j++) {
            if (p[j] == 'R') {
                reversed = !reversed;
            } else if (p[j] == 'D') {
                if (is_empty()) {
                    error = 1;
                    break;
                }
                if (!reversed) front++;
                else rear--;
            }
        }

        if (error) {
            printf("error\n");
        } else {
            printf("[");
            if (!is_empty()) {
                if (!reversed) {
                    for (int i = front; i < rear; i++) {
                        printf("%d", deque[i]);
                        if (i < rear - 1) printf(",");
                    }
                } else {
                    for (int i = rear - 1; i >= front; i--) {
                        printf("%d", deque[i]);
                        if (i > front) printf(",");
                    }
                }
            }
            printf("]\n");
        }
    }

    return 0;
}
