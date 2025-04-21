// 후위 표기식 바로 계산함

#include <stdio.h>
#include <ctype.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int x) {
    stack[++top] = x;
}

int pop() {
    return stack[top--];
}

int main() {
    char expr[MAX];
    scanf("%s", expr);

    for (int i = 0; expr[i]; i++) {
        char ch = expr[i];

        if (isdigit(ch)) {
            // 문자 숫자 → 정수로 변환
            push(ch - '0');
        } else {
            int b = pop();
            int a = pop();
            switch (ch) {
                case '+': push(a + b); break;
                case '-': push(a - b); break;
                case '*': push(a * b); break;
                case '/': push(a / b); break;
            }
        }
    }

    printf("%d\n", stack[top]);
    return 0;
}
