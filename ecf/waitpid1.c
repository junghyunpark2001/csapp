#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h> 
#include <unistd.h>
#include <errno.h>

#define N 2

void unix_error(const char *msg) {
    perror(msg);  // 시스템 에러 메시지를 출력
    exit(EXIT_FAILURE);  // 프로그램 종료
}

int main(){
    int status , i;
    pid_t pid;

    // parent creates N children
    for(i=0;i<N;i++){
        if((pid=fork())==0) exit(100+i);
    }

    // parent reaps N children in no particular order
    while((pid==waitpid(-1,&status,0))>0){
        if(WIFEXITED(status)) printf("child %d terminated normally with exit status=%d\n",pid,WEXITSTATUS(status));
        else printf("child %d terminated abnormally",pid);
    }
    // the only normal termination is if there are no more children
    if(errno!=ECHILD) unix_error("waitpid error");

    exit(0);
}