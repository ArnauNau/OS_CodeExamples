#include <stdio.h>     // For sprintf function
#include <unistd.h>    // For write, getpid, fork and unistd functions
#include <string.h>    // For strlen function
#include <signal.h>    // For signal function

// Test that a signal reconfigured from main it is executed from the parent and
// from the child
char phrase[100];

//ISR for SIGALRM
void isr() {
    sprintf(phrase, "I'm ISR funcion with PID=%d\n", getpid());
    write(STDOUT_FILENO, phrase, strlen(phrase));

    // The signal is not reconfigured, so the following SIGALRM will terminate
    // the process (default action).
    alarm(5);
}

int main() {
    int child;

    signal(SIGALRM, isr);

    child = fork();
    if (child > 0) {
        // Parent process
        sprintf(phrase, "I am the parent! With PID=%d\n", getpid());
        write(STDOUT_FILENO, phrase, strlen(phrase));

        // Send a SIGALRM signal in 8 seconds
        alarm(8);

        while (1) {
            pause();
        }
    } else if (child == 0) {
        // Child process
        sprintf(phrase, "I am the child with PID=%d\n", getpid());
        write(STDOUT_FILENO, phrase, strlen(phrase));

        // Send a SIGALRM signal in 5 seconds
        alarm(5);

        while (1) {
            pause();
        }
    } else {
        // Error forking
        sprintf(phrase, "JARL!! ERROR\n");
        write(STDOUT_FILENO, phrase, strlen(phrase));
    }
}
