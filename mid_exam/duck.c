#include <stdio.h>
#include <string.h>

int main() {
    char input[50];
    int stack = 0; // 스택 대신 카운터로 문제 수만 추적

    while (1) {
        scanf(" %[^\n]", input); // 줄 전체 입력 받기 (공백 포함)

        if (strcmp(input, "고무오리 디버깅 시작") == 0) {
            continue;
        } else if (strcmp(input, "고무오리 디버깅 끝") == 0) {
            break;
        } else if (strcmp(input, "문제") == 0) {
            stack++; // 문제 추가
        } else if (strcmp(input, "고무오리") == 0) {
            if (stack > 0) {
                stack--; // 최근 문제 해결
            } else {
                stack += 2; // 문제 없는데 고무오리 사용 → 벌칙
            }
        }
    }

    if (stack == 0) {
        printf("고무오리야 사랑해\n");
    } else {
        printf("힝구\n");
    }

    return 0;
}
