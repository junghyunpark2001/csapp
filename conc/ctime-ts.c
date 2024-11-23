#include "../csapp.h"

int mutex;

char *ctime_ts(const time_t *timep, char *privatep){
    char *sharedp;
    p(&mutex);
    sharedp = ctime(timep);
    strcpy(privatep, sharedp); // copy string from shared to private
    V(&mutex);
    return privatep;
}