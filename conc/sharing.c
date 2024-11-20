#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>


/*
cnt++
movl cnt(%rip), %eax   # 1. cnt 값을 %eax 레지스터로 로드
addl $1, %eax          # 2. %eax 레지스터 값에 1을 더함
movl %eax, cnt(%rip)   # 3. 결과를 cnt에 저장

문제 상황!!
1. 스레드 A : eax에 cnt 값 0으로 로드
2. 스레드 B: eax에 cnt 값 0으로 로드
3. 스레드 A : eax -> 1, cnt = eax
4. 스레드 B : eax -> 1, cnt = eax
*/
#define N 2

void *thread(void *vargp);

char **ptr;

int main(){
    long i;
    pthread_t tid;
    char*msgs[N] = {
        "Hello from foo",
        "Hello from bar"
    };

    ptr = msgs;
    for(i=0;i<N;i++)
        pthread_create(&tid, NULL, thread, (void*)i);

    pthread_exit(NULL);
}

void *thread(void *vargp){
    long myid = (long)vargp;
    static int cnt = 0;
    printf("[%ld]: %s (cnt=%d)\n", myid, ptr[myid],++cnt);
    return NULL;
}