// 올해 Z대학 컴퓨터공학부에 새로 입학한 민욱이는 학부에 개설된 모든 전공과목을 듣고 졸업하려는 원대한 목표를 세웠다. 
// 어떤 과목들은 선수과목이 있어 해당되는 모든 과목을 먼저 이수해야만 해당 과목을 이수할 수 있게 되어 있다. 
// 공학인증을 포기할 수 없는 불쌍한 민욱이는 선수과목 조건을 반드시 지켜야만 한다. 
// 민욱이는 선수과목 조건을 지킬 경우 각각의 전공과목을 언제 이수할 수 있는지 궁금해졌다. 
// 계산을 편리하게 하기 위해 아래와 같이 조건을 간소화하여 계산하기로 하였다.

// 한 학기에 들을 수 있는 과목 수에는 제한이 없다.
// 모든 과목은 매 학기 항상 개설된다.
// 모든 과목에 대해 각 과목을 이수하려면 최소 몇 학기가 걸리는지 계산하는 프로그램을 작성하여라.


#include <stdio.h>

#define MAX 1001

int prev[MAX][MAX];  // 각 노드의 후속 노드들을 저장
int prev_count[MAX]; // 각 노드의 후속 노드 수
int degree[MAX];     // 진입 차수
int result[MAX];     // 각 노드까지 도달하는 데 걸리는 최소 시간

int queue[MAX];      // 간단한 큐 구현
int front = 0, rear = 0;

void push(int x) {
    queue[rear++] = x;
}

int pop() {
    return queue[front++];
}

int empty() {
    return front == rear;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        result[i] = 1; // 기본값: 과목을 듣는 데 1학기 소요
    }

    for (int i = 0; i < M; i++) {
        int first, second;
        scanf("%d %d", &first, &second);

        prev[first][prev_count[first]++] = second;
        degree[second]++;
    }

    for (int i = 1; i <= N; i++) {
        if (degree[i] == 0) {
            push(i);
        }
    }

    while (!empty()) {
        int cur = pop();

        for (int i = 0; i < prev_count[cur]; i++) {
            int next = prev[cur][i];
            degree[next]--;
            if (result[next] < result[cur] + 1) {
                result[next] = result[cur] + 1;
            }
            if (degree[next] == 0) {
                push(next);
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}