#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

void * printf_xs(__attribute__((unused)) void *unused){

    while (1){
      fputc('x', stderr);
    }

    return NULL;
}

int main() {
    pthread_t thread_id;
    int status;

    status = pthread_create(&thread_id, NULL, printf_xs, NULL);

    if (status != 0) exit(-1);

    while (1){
        fputc('o', stderr);
    }

    return 0;
}
