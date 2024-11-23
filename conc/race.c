// this code is buggy

#include "../csapp.h"
#include <pthread.h>
#define N 4

void *thread(void *vargp);
int main(){
    pthread_t tid[N];
    int i;

    for(i=0;i<N;i++){
        pthread_create(&tid[i], NULL, thread,&i);
    }

    for(i=0;i<N;i++){
        pthread_join(tid[i],NULL);
    }
    return 0;
}

// thread routine
void *thread(void *vargp){
    int myid = *((int *)vargp);
    printf("Hello from thread %d\n",myid);
    return NULL;
}

/*
문제 분석
pthread_create의 네 번째 인자로 &i 전달. 
이는 i의 주소를 전달하는 것이므로, 모든 스레드가 동일한 메모리 위치 참조.
스레드들이 생성된 시점에서 i의 값을 읽기 위해 동시에 경쟁.
*/