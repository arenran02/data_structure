// 어떤 수식이 주어졌을 때, 괄호를 제거해서 나올 수 있는 서로 다른 식의 개수를 계산하는 프로그램을 작성하시오.

// 이 수식은 괄호가 올바르게 쳐져 있다. 예를 들면, 1+2, (3+4), (3+4*(5+6))와 같은 식은 괄호가 서로 쌍이 맞으므로 올바른 식이다.

// 하지만, 1+(2*3, ((2+3)*4 와 같은 식은 쌍이 맞지 않는 괄호가 있으므로 올바른 식이 아니다.

// 괄호를 제거할 때는, 항상 쌍이 되는 괄호끼리 제거해야 한다.

// 예를들어 (2+(2*2)+2)에서 괄호를 제거하면, (2+2*2+2), 2+(2*2)+2, 2+2*2+2를 만들 수 있다. 
// 하지만, (2+2*2)+2와 2+(2*2+2)는 만들 수 없다. 그 이유는 쌍이 되지 않는 괄호를 제거했기 때문이다.

// 어떤 식을 여러 쌍의 괄호가 감쌀 수 있다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 201

typedef struct {
    int open, close;
} Pair;

char expr[MAX];
Pair pairs[MAX];
int pair_count = 0;
int used[MAX];
char results[100000][MAX];
int result_count = 0;

void find_pairs() {
    int stack[MAX], top = -1;
    int len = strlen(expr);

    for (int i = 0; i < len; i++) {
        if (expr[i] == '(') {
            stack[++top] = i;
        } else if (expr[i] == ')') {
            if (top >= 0) {
                pairs[pair_count].open = stack[top--];
                pairs[pair_count].close = i;
                pair_count++;
            }
        }
    }
}

int is_unique(char* s) {
    for (int i = 0; i < result_count; i++) {
        if (strcmp(results[i], s) == 0)
            return 0;
    }
    return 1;
}

void generate(int idx) {
    if (idx == pair_count) {
        int len = strlen(expr);
        int skip[MAX] = {0};

        // 제거할 괄호 표시
        for (int i = 0; i < pair_count; i++) {
            if (used[i]) {
                skip[pairs[i].open] = 1;
                skip[pairs[i].close] = 1;
            }
        }

        // 새 문자열 생성
        char new_expr[MAX];
        int pos = 0;
        for (int i = 0; i < len; i++) {
            if (!skip[i]) {
                new_expr[pos++] = expr[i];
            }
        }
        new_expr[pos] = '\0';

        // 원본과 다르고 중복이 아니면 저장
        if (strcmp(new_expr, expr) != 0 && is_unique(new_expr)) {
            strcpy(results[result_count++], new_expr);
        }
        return;
    }

    // 현재 괄호쌍 제거 안 함
    used[idx] = 0;
    generate(idx + 1);

    // 현재 괄호쌍 제거
    used[idx] = 1;
    generate(idx + 1);
}

int main() {
    scanf("%s", expr);
    find_pairs();

    generate(0);

    // 결과 정렬
    qsort(results, result_count, sizeof(results[0]), (int (*)(const void*, const void*)) strcmp);

    for (int i = 0; i < result_count; i++) {
        printf("%s\n", results[i]);
    }

    return 0;
}
