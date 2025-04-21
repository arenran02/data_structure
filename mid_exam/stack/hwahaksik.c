#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 200

int get_mass(char c) {
    if (c == 'H') return 1;
    if (c == 'C') return 12;
    if (c == 'O') return 16;
    return 0;
}

int main() {
    char formula[101];
    scanf("%s", formula);

    int stack[MAX];
    int top = -1;

    for (int i = 0; formula[i]; i++) {
        char c = formula[i];

        if (c == 'H' || c == 'C' || c == 'O') {
            stack[++top] = get_mass(c);
        } else if (c == '(') {
            stack[++top] = -1; // '(' 표시용
        } else if (isdigit(c)) {
            int val = c - '0';
            if (stack[top] != -1) {
                stack[top] *= val;
            }
        } else if (c == ')') {
            int temp = 0;
            while (top >= 0 && stack[top] != -1) {
                temp += stack[top--];
            }
            top--; // '(' 제거
            stack[++top] = temp;
        }
    }

    int total = 0;
    for (int i = 0; i <= top; i++) {
        total += stack[i];
    }

    printf("%d\n", total);
    return 0;
}
