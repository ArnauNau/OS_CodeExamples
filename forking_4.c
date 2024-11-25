#include <iso646.h>
#include <stdio.h>     // For sprintf function
#include <unistd.h>    // For write, getpid and fork functions
#include <string.h>    // For strlen function
#include <stdlib.h>    // For exit function
#include <sys/wait.h>  // For wait function

int main (void) {

    printf("This is done by one process.\n");

    const int child = fork();
    if (child > 0) {
        // Parent process
        printf("I am the parent! With PID=%d (child's PID=%d)\n", getpid(), child);

        const pid_t exit_code = wait(NULL);
        if (exit_code == -1) {
            printf("Failure on waiting for child process\n");
            exit(-1);
        }
        printf("Child %d finished\n", exit_code);

        printf("Parent process finished\n");

        exit(0);
    } else if (child == 0) {
        // Child process
        printf("I am the child with PID=%d (parent's PID=%d)\n", getpid(), getppid());

        while(1) {
            char buffer, trash;
            const size_t size_read = read(STDIN_FILENO, &buffer, sizeof(char));
            read(STDIN_FILENO, &trash, sizeof(char));
            if (size_read <= 0) {
                printf("Error reading from stdin\n");
                _exit(-1);
            }
            //if char is 'q' then exit, if not ask again
            if (buffer == 'q') {
                printf("Child process finished\n");
                _exit(0);
            }
            printf("Not a valid option. Press 'q' to exit\n");
        }
    } else {
        // Error forking
        printf("JARL!! ERROR\n");
        exit(-1);
    }
}
