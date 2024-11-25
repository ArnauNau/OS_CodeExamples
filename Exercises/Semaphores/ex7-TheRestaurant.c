// C pseudo code - intended to understand the proposed solution to the problem.
// Author: Arnau Sanz <a@rnau.me> during the Operating Systems course at LaSalle Campus Barcelona - URL.

int free_chairs;
SEM sem_anyone_there;
SEM_init(&sem_anyone_there, 0);
SEM sem_barber;
SEM_init(&sem_barber, 1);
SEM mutex_chairs;
SEM_init(&mutex_chairs, 1);

void manageBarber () {
    while(1) {
        wait(sem_anyone_there);

        cutHair();
        signal(sem_barber);
    }
}

void manageCustomer () {
        wait(&mutex_chairs);
        if (free_chairs > 0) {
            free_chairs--;
            signal(&mutex_chairs);

            signal(sem_anyone_there);

            wait(sem_barber);
            getHairCut();

            wait(&mutex_chairs);
            free_chairs++;
            signal(&mutex_chairs);
        } else {
            signal(&mutex_chairs);
        }
        leave();
}
