#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <string.h>
#include <assert.h>

#define PING "ping"
#define PONG "pong"

typedef volatile struct{
    volatile atomic_int val;
    volatile atomic_flag mut;
} mysem_t;

mysem_t sem;

#define lock(m) while (atomic_flag_test_and_set(m))
#define unlock(m) atomic_flag_clear(m)

int wait(mysem_t *s){
    lock(&s->mut);
    while(atomic_load(&s->val)<=0);
    atomic_fetch_sub(&s->val,1);
    unlock(&s->mut);
    return 0;
}

int post(mysem_t *s){
    return atomic_fetch_add(&s->val,1);
}


void critical(const char *str){
    size_t len = strlen(str);
    for(size_t i=0;i<len;++i){
        printf("%c",str[i]);
    }
    printf("\n");
}

void *thread(void *p){
    char *msg = (char *)p;
    for(;;){
        wait(&sem);
        critical(msg);
        post(&sem);
    }
}

int main(){
    setvbuf(stdout,NULL, _IONBF,0);
    assert(ATOMIC_INT_LOCK_FREE == 2);
    atomic_init(&sem.val,1);
    pthread_t ping;
    pthread_t pong;
    pthread_create(&ping, NULL, thread, PING);
    pthread_create(&pong, NULL, thread, PONG);
    for(;;)
    return 0;
}