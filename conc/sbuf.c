#include "sbuf.h"
#include <pthread.h>

// create an empty, bounded, shared FIFO buffer with n slots
void sbuf_init(sbuf_t *sp, int n){
    sp->buf = Calloc(n,sizeof(int));
    sp->n = n; // buffer holds max items
    sp->front = sp->rear = 0; // empty buffer
    sem_init(&sp->mutex, 0, 1); // binary semaphore for locking
    sem_init(&sp->slots,0,n); // initially, buf has n empty slots
    sem_init(&sp->items,0,0); // initially, buf has zero data items
}

// clean up buffer sp
void sbuf_deinit(sbuf_t *sp){
    free(sp->buf);
}

// insert item onto the rear of shared buffer sp
void sbuf_insert(sbuf_t *sp, int item){
    P(&sp->slots); // wait for available slot
    P(&sp->mutex); // lock the buffer
    sp->buf[(++sp->rear)%(sp->n)] = item;
    V(&sp->mutex); // unlock the buffer
    V(&sp->items); // announce available item
}

// remove and return the first item from buffer sp
int sbuf_remove(sbuf_t *sp){
    int item;
    P(&sp->items); // wait for available item
    P(&sp->mutex); // lock the buffer
    item = sp->buf[(++sp->front)%(sp->n)]; // remove the item
    V(&sp->mutex); // unlock the buffer
    V(&sp->slots); // announce available slot
    return item;
}
