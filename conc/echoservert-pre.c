#include "../csapp.h"
#include "./sbuf.h"

#define NTRHEADS 4
#define SBUFSIZE 6

void echo_cnt(int connfd);
void *thread(void *vargp);

sbuf_t sbuf; // shared buffer of connected descriptor



int main(int argc, char **argv){
    int i, listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;

    if(argc!=2){
        fprintf(stderr, "usage: %s <port>\n",argv[0]);
        exit(0);
    }
    // 네트워크 프로그래밍에서 서버 소켓을 생성하고, 지정된 포트에서 연결을 대기하는 소켓 디스크립터 반환
    listenfd = Open_listenfd(argv[1]);
    sbuf_init(&sbuf, SBUFSIZE);
    for(i =0;i<NTRHEADS;i++) // create worker threads
        Ptrhead_create(&tid, NULL, thread, NULL);

    while(1){
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        sbuf_insert(&sbuf, connfd);
    }
}

void *thread(void *vargp){
    Pthread_detach(pthread_self());
    while(1){
        int connfd = sbuf_remove(&sbuf);
        echo_cnf(connfd);
        Close(connfd);
    }
}