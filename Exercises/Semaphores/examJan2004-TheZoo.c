// C pseudo code - intended to understand the proposed solution to the problem.
// Author: Arnau Sanz <a@rnau.me> during the Operating Systems course at LaSalle Campus Barcelona - URL.
#include "../../semaphore_v2.h"

int daily_visitors;
semaphore mutex_daily_visitors;
SEM_init(&mutex_daily_visitors, 1);
semaphore terrarium_limit;
SEM_init(&terrarium_limit, 125);
semaphore arachnids_limit;
SEM_init(&arachnids_limit, 1);

void Visitor() {
    SEM_wait(&mutex_daily_visitors);
    if (daily_visitors >= 1500) {
        SEM_signal(&mutex_daily_visitors);
        leave();
        return;
    }
    daily_visitors--;
    signal(mutex_daily_visitors);

    FreeVisit();

    SEM_wait(terrarium_limit);
    VisitTerrarium();
    SEM_signal(terrarium_limit);

    SEM_wait(arachnids_limit);
    VisitArachnidsRoom();
    SEM_signal(arachnids_limit);

    leave();
}
