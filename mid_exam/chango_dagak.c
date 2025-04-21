#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, h;
} Pillar;

int cmp(const void* a, const void* b) {
    Pillar* p1 = (Pillar*)a;
    Pillar* p2 = (Pillar*)b;
    return p1->x - p2->x;
}

int main() {
    int N;
    scanf("%d", &N);

    Pillar p[1001];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &p[i].x, &p[i].h);
    }

    // x 좌표 기준 정렬
    qsort(p, N, sizeof(Pillar), cmp);

    // 가장 높은 기둥 찾기
    int max_idx = 0;
    for (int i = 1; i < N; i++) {
        if (p[i].h > p[max_idx].h) {
            max_idx = i;
        }
    }

    int area = 0;
    int highest = p[0].h;
    int left = p[0].x;

    // 왼쪽 → 가장 높은 기둥까지
    for (int i = 1; i <= max_idx; i++) {
        if (p[i].h >= highest) {
            area += (p[i].x - left) * highest;
            highest = p[i].h;
            left = p[i].x;
        }
    }

    // 가장 높은 기둥 넓이 더함
    area += p[max_idx].h;

    // 오른쪽 → 가장 높은 기둥까지
    highest = p[N - 1].h;
    int right = p[N - 1].x;

    for (int i = N - 2; i >= max_idx; i--) {
        if (p[i].h >= highest) {
            area += (right - p[i].x) * highest;
            highest = p[i].h;
            right = p[i].x;
        }
    }

    printf("%d\n", area);
    return 0;
}
