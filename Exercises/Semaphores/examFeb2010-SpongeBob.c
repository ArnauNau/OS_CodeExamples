// C pseudo code - intended to understand the proposed solution to the problem.
// Author: Arnau Sanz <a@rnau.me> during the Operating Systems course at LaSalle Campus Barcelona - URL.
#include "../../semaphore_v2.h"

void leave(void);
void Enter_Restaurant(void);
void Sit(void);
void Place_Order(void);
void Watch_TV(void);
void Eat(void);
void Pay(void);

#define QUEUE_MAX 15
#define CAPACITY 65
#define WAITERS 3
#define ONE_KRAB 1
int customers_in_queue;
semaphore mutex_queue;
SEM_init(&mutex_queue, 1);
semaphore customer_inside;
SEM_init(&customer_inside, CAPACITY);
semaphore queue;
SEM_init(&queue, QUEUE_MAX);
semaphore waiter;
SEM_init(&waiter, WAITERS);
semaphore mr_krabs;
SEM_init(&mr_krabs, ONE_CRAB);

void Customer(void) {
    SEM_wait(&mutex_queue);
    if (customers_in_queue >= QUEUE_MAX) {
        SEM_signal(&mutex_queue);
        leave();
        return;
    }
    customers_in_queue++;
    SEM_signal(&mutex_queue);

    SEM_wait(&queue);

    SEM_wait(&mutex_queue);
    customers_in_queue--;
    SEM_signal(&mutex_queue);

    SEM_wait(&customer_inside);
    SEM_signal(&queue);
    Enter_Restaurant();

    Sit();
    SEM_wait(&waiter);
    Place_Order();
    SEM_signal(&waiter);
    Watch_TV();
    Eat();
    SEM_wait(&mr_krabs);
    Pay();
    SEM_signal(&mr_krabs);
    SEM_signal(&customer_inside);
}
