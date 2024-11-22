#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#define PING "ping"
#define PONG "pong"

typedef struct {
    atomic_int val;
    pthread_mutex_t mut;
    pthread_cond_t cond;
} mysem_t;

mysem_t sem;

void wait(mysem_t *s) {
    pthread_mutex_lock(&s->mut);
    while (atomic_load(&s->val) <= 0) {
        pthread_cond_wait(&s->cond, &s->mut);
    }
    atomic_fetch_sub(&s->val, 1);
    pthread_mutex_unlock(&s->mut);
}

void post(mysem_t *s) {
    pthread_mutex_lock(&s->mut);
    atomic_fetch_add(&s->val, 1);
    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->mut);
}

void critical(const char *str) {
    printf("%s\n", str);
}

void *thread(void *p) {
    char *msg = (char *)p;
    for (;;) {
        wait(&sem);
        critical(msg);
        post(&sem);
    }
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    assert(ATOMIC_INT_LOCK_FREE == 2);

    // 세마포어 초기화
    atomic_init(&sem.val, 1);
    pthread_mutex_init(&sem.mut, NULL);
    pthread_cond_init(&sem.cond, NULL);

    pthread_t ping, pong;
    pthread_create(&ping, NULL, thread, PING);
    pthread_create(&pong, NULL, thread, PONG);

    // 메인 스레드 유지
    for (;;)
        sleep(1);

    return 0;
}
