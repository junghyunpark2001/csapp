#include "../csapp.h"
#include <stdio.h>   // perror 함수 정의
#include <stdlib.h>  // exit 함수 정의



void sigint_handler(int sig){
    printf("Caught SIGINT!\n");
    exit(0);
}

int main(){
    if(signal(SIGINT, sigint_handler)==SIG_ERR){
        perror("signal error");  // 시스템 에러 메시지를 출력
        exit(EXIT_FAILURE);  // 프로그램 종료
}
    pause();

    return 0;

}