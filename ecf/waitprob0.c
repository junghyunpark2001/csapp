#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h> 
#include <unistd.h>

int main(){
    if(fork()==0){
        printf("a"); fflush(stdout);
    }
    else{
        printf("b"); fflush(stdout);
        waitpid(-1,NULL,0);
    }
    printf("c");fflush(stdout);
    exit(0);
}