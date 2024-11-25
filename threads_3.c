/**********************************************************************\
*                Copyright (C) XaviC, 2013.                  *
*               Paràmetres del thread                        *
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *threadFunc(void *arg)
{
    int *number = (int *)arg;

    *number = *number + 5;

    return (void *)arg;
}

int main ()
{
    pthread_t t1;
    void *res;
    int s, x;

    x = 7;
    printf("Value of x=%d\n", x);
    s = pthread_create(&t1, NULL, threadFunc, &x);
    if(s != 0)
    {
        printf("pthread_create\n");
        exit(EXIT_FAILURE);
    }
    printf ("Message from main()\n");
    s = pthread_join(t1, &res);
    if(s != 0)
    {
        printf("pthread_join\n");
        exit(EXIT_FAILURE);
    }
    printf("Thread returns %lX\n", (long)res);
    printf("Value of x=%d\n", x);
    exit(EXIT_SUCCESS);
}
