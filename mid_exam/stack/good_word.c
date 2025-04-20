// 이번 계절학기에 심리학 개론을 수강 중인 평석이는 오늘 자정까지 보고서를 제출해야 한다. 
// 보고서 작성이 너무 지루했던 평석이는 노트북에 엎드려서 꾸벅꾸벅 졸다가 제출 마감 1시간 전에 깨고 말았다. 
// 안타깝게도 자는 동안 키보드가 잘못 눌려서 보고서의 모든 글자가 A와 B로 바뀌어 버렸다! 그래서 평석이는 보고서 작성을 때려치우고 보고서에서 '좋은 단어'나 세보기로 마음 먹었다.

// 평석이는 단어 위로 아치형 곡선을 그어 같은 글자끼리(A는 A끼리, B는 B끼리) 쌍을 짓기로 하였다. 
// 만약 선끼리 교차하지 않으면서 각 글자를 정확히 한 개의 다른 위치에 있는 같은 글자와 짝 지을수 있다면, 그 단어는 '좋은 단어'이다. 평석이가 '좋은 단어' 개수를 세는 것을 도와주자.

#include<stdio.h>
#include<string.h>

char Stack[100002];  //스택
char input[100002];  //문자열 입력받을 떄 쓸 배열
int top = -1;          //스택의 topindex를 -1로 초기화(스택의 제일 위에 있는 값)
int sum = 0;          //좋은단어의 합을 위한 변수

void Push(char data){
    Stack[++top] = data;  //스택 Push연산
}

void Pop(){

    Stack[top] = '0';  //스택 Pop연산
    top = top -1;

}
 
int main(void){
    int n;
    scanf("%d",&n);

    for(int i = 0;i<n;i++){

     scanf("%s",input);   //n번동안 문자열을 입력받는다
        int len = strlen(input);   //문자열의 길이

        for(int q = 0;q<len;q++){   //문자열의 길이만큼 반복문 실행
            if(q == 0){           //문자열의 시작(문자열의 첫 문자일때)
                Push(input[q]);   //Push연산
            }

            else if(input[q] == Stack[top]){    //스택의 꼭대기(topindex)값과 

                    Pop();//문자열의 문자(input[q])가 같다면 Pop연산

            }

            else if(input[q] !=Stack[top]){

                Push(input[q]);    //그외에는 Push연산

            }
        }

        if(top == -1){     //스택이 비어있으면 좋은단어의 개수 하나 증가시킨다.

            sum = sum + 1;

        }

        top = -1; 

        for(int h = 0;h<len;h++){   //스택의 초기화

            Stack[h] = '0';    

        }
    }

    printf("%d",sum);   //좋은단어의 개수 출력
}