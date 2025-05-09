// 성애는 이번 학기에 전공을 정말 많이 듣는다. 이로 인해 거의 매일을 과제를 하면서 보내고 있다. 
// 그런데도 과제가 줄어들 기미가 보이지 않는데, 바로 분단위로 과제가 추가되고 있기 때문이다.
//  다행히 과제 제출 기한은 학기가 끝날 때까지이다. 너무나도 많은 과제를 하다가 미쳐버린 성애는 아래와 같은 규칙으로 과제를 해 나가고 있다.

// 과제는 가장 최근에 나온 순서대로 한다. 또한 과제를 받으면 바로 시작한다.
// 과제를 하던 도중 새로운 과제가 나온다면, 하던 과제를 중단하고 새로운 과제를 진행한다.
// 새로운 과제가 끝났다면, 이전에 하던 과제를 이전에 하던 부분부터 이어서 한다. (성애는 기억력이 좋기 때문에 아무리 긴 시간이 지나도 본인이 하던 부분을 기억할 수 있다.)
// 성애는 과제를 받자마자 이 과제가 몇 분이 걸릴지 정확하게 알 수 있고, 성애가 제출한 과제는 무조건 만점을 받는다.

// 성애는 이번 학기에 자기가 받을 과제 점수를 예상해보고 싶다. 하지만 과제 점수를 예상하는 지금도 과제가 추가되고 있기에 여유를 부릴 수가 없다. 여러분이 성애가 받을 과제 점수를 구해주자!


#include <stdio.h>

typedef struct {
    int score;
    int time;
} Task;

#define MAX 1000000

Task stack[MAX];
int top = -1;
int total_score = 0;

void push(int score, int time) {
    stack[++top].score = score;
    stack[top].time = time;
}

void pop() {
    top--;
}

int main() {
    int T;
    scanf("%d", &T);

    for (int i = 0; i < T; i++) {
        int cmd;
        scanf("%d", &cmd);

        if (cmd == 1) {
            int a, t;
            scanf("%d %d", &a, &t);
            push(a, t);
        }

        // 과제 수행
        if (top >= 0) {
            stack[top].time--;
            if (stack[top].time == 0) {
                total_score += stack[top].score;
                pop();
            }
        }
    }

    printf("%d\n", total_score);
    return 0;
}
