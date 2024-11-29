#include <stdio.h>
#include "../csapp.h"

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