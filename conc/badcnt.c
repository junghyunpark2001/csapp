#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>


/*
for(i=0;i<niters;i++)
    cnt++;

ASM
// H : Head
    movq (%rdi), %rcx
    testq %rcx, %rcx
    jle .L2
    movl $0, %eax
.L3:
    movq cnt(%rip), %rdx // L : Load cnt
    addq $1, %rdx // U : Update cnt
    movq %rdx, cnt(%rip) // S : Store cnt
    // T : Tail
    add1 $1, %rax
    cmpq %rcx, %rax
    jne .L3
.L2:

*/

void *thread(void *vargp);

volatile long cnt = 0;

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

    if(cnt!=(2*niters))
        printf("BOOM! cnt=%ld\n",cnt);
    else    
        printf("OK cnt=%ld\n",cnt);

    exit(0);
}

void *thread(void *vargp){
    long i, niters = *((long *)vargp);
    
    for(i=0;i<niters;i++)
        cnt++;
    
    return NULL;
}