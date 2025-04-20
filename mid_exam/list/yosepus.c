// 요세푸스 문제는 다음과 같다.

// 1번부터 N번까지 N명의 사람이 원을 이루면서 앉아있고, 양의 정수 K(≤ N)가 주어진다. 
// 이제 순서대로 K번째 사람을 제거한다. 한 사람이 제거되면 남은 사람들로 이루어진 원을 따라 이 과정을 계속해 나간다. 
// 이 과정은 N명의 사람이 모두 제거될 때까지 계속된다. 원에서 사람들이 제거되는 순서를 (N, K)-요세푸스 순열이라고 한다. 예를 들어 (7, 3)-요세푸스 순열은 <3, 6, 2, 7, 5, 1, 4>이다.

// N과 K가 주어지면 (N, K)-요세푸스 순열을 구하는 프로그램을 작성하시오.

#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    int* people = (int*)malloc(sizeof(int) * N);  // 동적 할당
    int* result = (int*)malloc(sizeof(int) * N);  // 결과 저장용

    for (int i = 0; i < N; i++) {
        people[i] = i + 1;  // 1 ~ N번 사람
    }

    int size = N;      // 현재 남은 사람 수
    int idx = 0;       // 현재 제거할 위치 인덱스
    int res_idx = 0;   // 결과 배열 인덱스

    while (size > 0) {
        idx = (idx + K - 1) % size;         // K번째 사람을 찾는다
        result[res_idx++] = people[idx];    // 제거된 사람 저장

        // 제거한 사람 이후 사람들 한 칸씩 앞으로 당기기
        for (int i = idx; i < size - 1; i++) {
            people[i] = people[i + 1];
        }

        size--;  // 인원 줄이기
        // idx는 현재 그대로 유지됨 (다음 K번째를 위한 시작점)
        // 왜냐면 위에서 해당 위치를 지웠고, 그 자리에 다음 사람이 있음
    }

    // 출력
    printf("<");
    for (int i = 0; i < N; i++) {
        if (i == N - 1)
            printf("%d", result[i]);
        else
            printf("%d, ", result[i]);
    }
    printf(">\n");

    free(people);
    free(result);
    return 0;
}
