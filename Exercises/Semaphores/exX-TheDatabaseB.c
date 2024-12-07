// C pseudo code - intended to understand the proposed solution to the problem.
// Author: Arnau Sanz <a@rnau.me> during the Operating Systems course at LaSalle Campus Barcelona - URL.
#include "../../semaphore_v2.h"

//only one concurrent Write, no limit on Reads.
//no Reads can be performed while performing a Write

int read_count = 0;
int waiting_writers = 0;
semaphore mutex;
SEM_init(&mutex, 1);
semaphore write;
SEM_init(&write, 1);
semaphore reader_queue;
SEM_init(&reader_queue, 1);

void Reader() {
    SEM_wait(&reader_queue);
    SEM_wait(&mutex);

    if (waiting_writers > 0) {
        SEM_signal(&mutex);
        SEM_signal(&reader_queue);
        SEM_wait(&reader_queue);
        SEM_wait(&mutex);
    }

    read_count++;
    if (read_count == 1) {
        //first reader blocks following writes (lock on write) and
        //following reads (mutex still locked) if writer is still writing
        SEM_wait(&write);
    }
    SEM_signal(&mutex);
    SEM_signal(&reader_queue);

    Read();

    SEM_wait(&mutex);
    read_count--;
    if (read_count == 0) {
        SEM_signal(&write);
    }
    SEM_signal(&mutex);
}

void Writer() {
    SEM_wait(&mutex);
    waiting_writers++;
    SEM_signal(&mutex);

    SEM_wait(&write);

    SEM_wait(&mutex);
    waiting_writers--;
    SEM_signal(&mutex);

    Write();

    SEM_signal(&write);
}
