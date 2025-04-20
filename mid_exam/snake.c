#include <stdio.h>
#include <stdlib.h>

#define MAX 101

typedef struct {
    int x, y;
} Pos;

int board[MAX][MAX];         // 0: 빈칸, 1: 사과, 2: 뱀
Pos snake[MAX * MAX];        // 뱀 위치 큐
int front = 0, rear = 0;

int dir = 0;                 // 0:→, 1:↓, 2:←, 3:↑
int dx[] = {0, 1, 0, -1};    // x, y 바꿈: 행 중심
int dy[] = {1, 0, -1, 0};

typedef struct {
    int time;
    char turn;
} Cmd;

Cmd commands[100];
int cmd_count = 0;

int N, K, L;

int is_in_bounds(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

void turn_dir(char c) {
    if (c == 'L') dir = (dir + 3) % 4; // 왼쪽 회전
    else if (c == 'D') dir = (dir + 1) % 4; // 오른쪽 회전
}

int main() {
    scanf("%d", &N);
    scanf("%d", &K);
    
    for (int i = 0; i < K; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        board[x - 1][y - 1] = 1;  // 사과 표시 (1)
    }

    scanf("%d", &L);
    for (int i = 0; i < L; i++) {
        int t;
        char c;
        scanf("%d %c", &t, &c);
        commands[i].time = t;
        commands[i].turn = c;
    }

    int time = 0, cmd_idx = 0;

    // 초기 뱀 위치
    int head_x = 0, head_y = 0;
    snake[rear++] = (Pos){0, 0};
    board[0][0] = 2;

    while (1) {
        time++;

        int nx = head_x + dx[dir];
        int ny = head_y + dy[dir];

        // 충돌 검사
        if (!is_in_bounds(nx, ny) || board[nx][ny] == 2) break;

        // 이동
        if (board[nx][ny] == 1) {
            // 사과 있으면 먹고 꼬리 안 줄임
            board[nx][ny] = 2;
            snake[rear++] = (Pos){nx, ny};
        } else {
            // 사과 없으면 이동 + 꼬리 줄이기
            board[nx][ny] = 2;
            snake[rear++] = (Pos){nx, ny};
            Pos tail = snake[front++];
            board[tail.x][tail.y] = 0;
        }

        head_x = nx;
        head_y = ny;

        // 방향 전환
        if (cmd_idx < L && time == commands[cmd_idx].time) {
            turn_dir(commands[cmd_idx].turn);
            cmd_idx++;
        }
    }

    printf("%d\n", time);
    return 0;
}
