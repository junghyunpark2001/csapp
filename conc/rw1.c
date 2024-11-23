#include <stdio.h>
#include <pthread.h>

int readcnt; // initially = 0
int mutex, w; // both initially = 1

void reader(void){
    while(1){
        P(&mutex);
        readcnt++;
        if(readcnt==1) // first in
            P(&w);
        V(&mutex);
        // critical section
        // reading happens
        P(&mutex);
        readcnt--;
        if(readcnt==0) // last out
            V(&w);
        V(&mutex);
    }
}

void writer(void){
    while(1){
        P(&w);
        // critical section
        // writing happens
        V(&w);
    }
}