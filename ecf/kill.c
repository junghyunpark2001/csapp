#include <stdio.h>
#include "../csapp.h"

/*
자식 프로세스는 pause()로 신호를 받을 때까지 대기하는데.
자식 프로세스는 부모가 보낸 SIGKILL 신호를 받으면 강제로 종료.
부모 프로세스는 kill()로 자식 프로세스에 SIGKILL 신호 전송.
자식 프로세스는 강제종료. printf, exit 는 실행되지 않음.냐
*/
int main(){
    pid_t pid;

    // child sleeps until SIGKILL signal received, then dies
    if((pid=fork())==0){
        pause();
        printf("control should never reach here!\n");
        exit(0);
    }
    //parent sends a SIGKILL signal to a child
    kill(pid,SIGKILL);
    exit(0);

}