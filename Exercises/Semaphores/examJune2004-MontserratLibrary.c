// C pseudo code - intended to understand the proposed solution to the problem.
// Author: Arnau Sanz <a@rnau.me> during the Operating Systems course at LaSalle Campus Barcelona - URL.
#include "../../semaphore_v2.h"

/*
* - General public
* - Person of culture
* - Virtual
*/
void leave();
void PublicPartView();

#define MAXVISITORS 2000
#define NUM_AREAS 20

int monthly_visitors;
semaphore mutex_monthly_visitors;
SEM_init(&mutex_monthly_visitors, 1);
int monthly_online;
semaphore mutex_monthly_online;
SEM_init(&mutex_monthly_online, 1);
semaphore area_semaphore[NUM_AREAS];
for (int i = 0; i < NUM_AREAS; i++) {
    SEM_init(&area_semaphore[i], MaxCapacity[i]);
}

void Public(void) {
    SEM_wait(&mutex_monthly_visitors);

    if (monthly_visitors >= MAXVISITORS) {
        SEM_signal(&mutex_monthly_visitors);
        leave();
        return;
    }

    monthly_visitors++;
    SEM_signal(&mutex_monthly_visitors);

    PublicPartView();
}


void Erudite() {
    int num_of_sections;
    int *sections_to_visit = NULL;
    ReadSectionsFromUser(&num_of_sections, &sections_to_visit);

    SEM_wait(&mutex_monthly_visitors);

    if (monthly_visitors >= MAXVISITORS) {
        SEM_signal(&mutex_monthly_visitors);
        leave();
        return;
    }

    monthly_visitors++;
    SEM_signal(&mutex_monthly_visitors);

    for (int i = 0; i < num_of_sections; i++) {
        SEM_wait(&sections_to_visit[i]);
        SectionCheck(sections_to_visit[i]);
        SEM_signal(&sections_to_visit[i]);
    }
}


void Browser() {
    SEM_wait(&mutex_monthly_online);
    monthly_online++;
    SEM_signal(&mutex_monthly_online);

    VirtualView();
}
