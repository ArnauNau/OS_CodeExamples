#include <stdio.h>     // For sprintf function
#include <unistd.h>    // For write, getpid and fork functions
#include <string.h>    // For strlen function
#include <stdlib.h>    // For exit function
#include <sys/wait.h>  // For wait function

int main() {
    int a, b, c;
    int child;
    char phrase[100];

    a=25;
    b=11;
    c=7;

    child = fork();
    if (child > 0) {
        // Parent process

        //wait(NULL);

        sprintf(phrase, "I am the parent! With PID=%d (child's PID=%d)\n", getpid(), child);
        write(STDOUT_FILENO, phrase, strlen(phrase));

        a++;
        b++;
        c++;

        exit(0);
    } else if (child == 0) {
        // Child process
        sprintf(phrase, "I am the child with PID=%d (parent's PID=%d)\n", getpid(), getppid());
        write(STDOUT_FILENO, phrase, strlen(phrase));

        sprintf(phrase, "a=%d, b=%d, c=%d\n", a, b, c);
        write(STDOUT_FILENO, phrase, strlen(phrase));

        exit(0);
    } else {
        // Error forking
        sprintf(phrase, "JARL!! ERROR\n");
        write(STDOUT_FILENO, phrase, strlen(phrase));

        exit(-1);
    }
}
