#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 10000
#define MAX_PARROTS 100

char* queue[MAX_PARROTS][101];
int front[MAX_PARROTS], rear[MAX_PARROTS];

char word_map[MAX_WORDS][33]; // 단어 목록
int word_owner[MAX_WORDS];    // word_map[i]가 속한 앵무새 번호
int word_count = 0;

int find_word_index(char* word) {
    for (int i = 0; i < word_count; i++) {
        if (strcmp(word_map[i], word) == 0)
            return i;
    }
    return -1;
}

int main() {
    int N;
    scanf("%d", &N);
    getchar(); // 개행 처리

    char line[5000];

    for (int i = 0; i < N; i++) {
        fgets(line, sizeof(line), stdin);
        char* token = strtok(line, " \n");
        while (token) {
            queue[i][rear[i]++] = strdup(token);

            strcpy(word_map[word_count], token);
            word_owner[word_count] = i;
            word_count++;

            token = strtok(NULL, " \n");
        }
    }

    // L 문장 처리
    fgets(line, sizeof(line), stdin);
    char* token = strtok(line, " \n");

    int possible = 1;
    while (token) {
        int idx = find_word_index(token);
        if (idx == -1) {
            possible = 0;
            break;
        }

        int owner = word_owner[idx];
        if (front[owner] < rear[owner] && strcmp(queue[owner][front[owner]], token) == 0) {
            front[owner]++;
        } else {
            possible = 0;
            break;
        }

        token = strtok(NULL, " \n");
    }

    // 모든 앵무새가 문장을 다 말했는지 확인
    for (int i = 0; i < N && possible; i++) {
        if (front[i] != rear[i]) {
            possible = 0;
            break;
        }
    }

    printf("%s\n", possible ? "Possible" : "Impossible");
    return 0;
}
