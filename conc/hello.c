#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>


// 스레드로 실행될 함수를 선언
// 인자 : 스레드 함수에 전달할 데이터를 받는 포인터
void *thread(void *vargp);

int main(){
    pthread_t tid; // 스레드 식별자를 저장하는 자료형. tid는 새로 생성된 스레드를 식별하기 위한 변수
    // 스레드 생성
    // &tid : 새로 생성된 스레드의 식별자 저장
    // NULL : 스레드 속성을 기본값으로 설정
    // thread : 스레드가 실행할 함수의 포인터
    // NULL : 스레드 함수에 전달할 인자(여기서는 없음)
    pthread_create(&tid, NULL, thread, NULL); 
    // 스레드 종료 대기
    // tid : 종료를 기다릴 스레드의 식별자
    // NULL : 스레드의 반환값을 무시
    pthread_join(tid, NULL);
    exit(0);
}

void *thread(void *vargp){
    printf("Hello, world!\n");
    return NULL;
}