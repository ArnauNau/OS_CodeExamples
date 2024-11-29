/**********************************************************************\
*                Copyright (C) Michael Kerrisk, 2010.                  *
*                                                                      *
* This program is free software. You may use, modify, and redistribute *
* it under the terms of the GNU Affero General Public License as       *
* published by the Free Software Foundation, either version 3 or (at   *
* your option) any later version. This program is distributed without  *
* any warranty. See the file COPYING for details.                      *
\**********************************************************************/
/* threads2.c
   A simple POSIX threads example: create a thread, and then join with it.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *threadFunc (void *arg) {
    char *s = (char *) arg;

    printf("%s", s);

    return (void *) strlen (s);
}

int main () {
    pthread_t t1;
    void *res;
    int s;

    s = pthread_create(&t1, NULL, threadFunc, "Hello world\n");
    if (s != 0) {
        printf("pthread_create\n");
        exit(EXIT_FAILURE);
    }

    printf("Message from main()\n");

    s = pthread_join(t1, &res);
    if (s != 0) {
        printf("pthread_join\n");
        exit(EXIT_FAILURE);
    }
    printf("Thread returned %ld\n", (long) res);

    exit(EXIT_SUCCESS);
}
