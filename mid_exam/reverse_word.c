// 스페이스로 띄어쓰기 된 단어들의 리스트가 주어질때, 단어들을 반대 순서로 뒤집어라. 
// 각 라인은 w개의 영단어로 이루어져 있으며, 총 L개의 알파벳을 가진다. 각 행은 알파벳과 스페이스로만 이루어져 있다. 단어 사이에는 하나의 스페이스만 들어간다.

// 예제 입력 1
// 3
// this is a test
// foobar
// all your base

// 예제 출력 1 
// Case #1: test a is this
// Case #2: foobar
// Case #3: base your all

#include <stdio.h>
#include <string.h>

#define MAX_LINE 110
#define MAX_WORDS 50

void reverse_words_and_print(char *line, int case_num) {
    char *words[MAX_WORDS];
    int count = 0;

    char *token = strtok(line, " ");
    while (token != NULL) {
        words[count++] = token;
        token = strtok(NULL, " ");
    }

    printf("Case #%d: ", case_num);
    for (int i = count - 1; i >= 0; i--) {
        printf("%s", words[i]);
        if (i > 0) printf(" ");
    }
    printf("\n");
}

int main() {
    int N;
    char line[MAX_LINE];

    scanf("%d", &N);
    getchar(); // 개행문자 제거

    for (int i = 1; i <= N; i++) {
        fgets(line, sizeof(line), stdin);

        // 줄바꿈문자 제거
        size_t len = strlen(line);
        if (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '.' || line[len - 1] == '!')) {
            line[len - 1] = '\0';
        }

        reverse_words_and_print(line, i);
    }

    return 0;
}
