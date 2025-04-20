// 한가롭게 방학에 놀고 있던 도현이는 갑자기 재밌는 자료구조를 생각해냈다. 그 자료구조의 이름은 queuestack이다.

// queuestack의 구조는 다음과 같다.
// 1번, 2번, ..., N번의 자료구조(queue 혹은 stack)가 나열되어 있으며, 각각의 자료구조에는 한 개의 원소가 들어있다.

// queuestack의 작동은 다음과 같다.

// x0을 입력받는다.
// x0을 1번 자료구조에 삽입한 뒤, 1번 자료구조에서 원소를 pop한다. 그때 pop된 원소를 x1이라 한다.
// x1을 2번 자료구조에 삽입한 뒤, 2번 자료구조에서 원소를 pop한다. 그때 pop된 원소를 x2라 한다.

// ...

// x_{N-1}을 N번 자료구조에 삽입한 뒤, N번 자료구조에서 원소를 pop한다. 그때 pop된 원소를 xN이라 한다. xN을 리턴한다.

// 도현이는 길이 M의 수열 C를 가져와서 수열의 원소를 앞에서부터 차례대로 queuestack에 삽입할 것이다. 이전에 삽입한 결과는 남아 있다. (예제 1 참고)
// queuestack에 넣을 원소들이 주어졌을 때, 해당 원소를 넣은 리턴값을 출력하는 프로그램을 작성해보자.

#include <stdio.h>

#define MAX_SIZE 100000
#define QUEUE 0

int main(void)
{
    int qs_size;
    scanf("%d", &qs_size);

    int qs_types[MAX_SIZE];
    int qs_elements[MAX_SIZE];

    for (int i = 0; i < qs_size; i++)
    {
        scanf("%d", &qs_types[i]);
    }
    for (int i = 0; i < qs_size; i++)
    {
        scanf("%d", &qs_elements[i]);
    }

    int insert_count;
    scanf("%d", &insert_count);

    for (int i = qs_size - 1; insert_count != 0 && i >= 0; i--)
    {
        if (qs_types[i] == QUEUE)
        {
            printf("%d ", qs_elements[i]);
            insert_count--;
        }
    }

    for (; insert_count != 0; insert_count--)
    {
        int append_element;
        scanf("%d", &append_element);
        printf("%d ", append_element);
    }
}