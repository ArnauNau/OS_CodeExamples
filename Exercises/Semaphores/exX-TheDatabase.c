// C pseudo code - intended to understand the proposed solution to the problem.
// Author: Arnau Sanz <a@rnau.me> during the Operating Systems course at LaSalle Campus Barcelona - URL.
#include "../../semaphore_v2.h"

//only one concurrent Write, no limit on Reads.
//no Reads can be performed while performing a Write

semaphore mutex_write;
SEM_init(&mutex_write, 1);

void Reader() {
    SEM_wait(&mutex_write);
    SEM_signal(&mutex_write);

    Read();
}

void Writer() {
    SEM_wait(&mutex_write);

    Write();

    SEM_signal(&mutex_write);
}
