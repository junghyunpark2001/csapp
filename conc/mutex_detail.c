#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>


/*
atomic_flag_test_and_set의 m은 현재 값을 반환하고, 동시에 m을 true로 설정
- m이 이미 true라면, 다른 스레드가 임계구역 점유
- while 루프에서 대기(busy-wait)하며 잠금 해제 기다림
- m이 false라면 스레드가 임계 구역 점유
*/
#define lock(m) while(atomic_flag_test_and_set(m))

/*
atomic_flag_clear는 m을 false로 설정하여 다른 스레드가 임계 구역에 진입할 수 있도록 함
*/
#define unlock(m) atomic_flag_clear(m)

volatile atomic_flag mutex;
volatile long cnt = 0;

void *thread(void *vagrp){
    lock(&mutex);
    cnt++;
    unlock(&mutex);

    return 0;
}


int main(int argc, char **argv){
    long niters;
    pthread_t tid1, tid2;

    if(argc!=2){
        printf("usage : %s <niters>\n", argv[0]);
        exit(0);
    }

    niters = atoi(argv[1]);

    pthread_create(&tid1, NULL, thread, &niters);
    pthread_create(&tid2, NULL, thread, &niters);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    if(cnt!=(2))
        printf("BOOM! cnt=%ld\n",cnt);
    else    
        printf("OK cnt=%ld\n",cnt);

    exit(0);
}