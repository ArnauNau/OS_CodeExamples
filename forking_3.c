#include <stdio.h>     // For sprintf function
#include <unistd.h>    // For write, getpid and fork functions
#include <string.h>    // For strlen function
#include <stdlib.h>    // For exit function
#include <sys/wait.h>  // For wait function
#include <fcntl.h>     // For open function

int main() {
    int a, b, c;
    int child;
    char phrase[100];
    int fd_file;

    a=25;
    b=11;
    c=7;

    child = fork();
    if (child > 0) {
        // Parent process
        sprintf(phrase, "I am the parent! With PID=%d (child's PID=%d)\n", getpid(), child);
        write(STDOUT_FILENO, phrase, strlen(phrase));

        // Wait for the child process to finish
        //wait(NULL);

        a++;
        b++;
        c++;

        // Pause the process forever
        //pause();

        // Finish the process
        exit(0);
    } else if (child == 0) {
        // Child process
        sprintf(phrase, "I am the child with PID=%d (parent's PID=%d)\n", getpid(), getppid());
        write(STDOUT_FILENO, phrase, strlen(phrase));

        // Sleep so the parent process finishes
        sleep(5);

        // The screen file descriptor is closed because the parent process
        sprintf(phrase, "a=%d, b=%d, c=%d\n", a, b, c);
        write(STDOUT_FILENO, phrase, strlen(phrase));

        ////////// Write the parent PID (1) in a file
        fd_file = open ("output.txt", O_WRONLY|O_CREAT|O_TRUNC, 0600);
        if (fd_file == -1) {
            sprintf(phrase, "Unable to create file!\n");
            write(STDERR_FILENO, phrase, strlen(phrase));
        } else {
            sprintf(phrase, "File created from child (parent PID=%d)\n", getppid());
            write(fd_file, phrase, strlen(phrase));

            // Close opened file
            close(fd_file);
        }
        //////////

        // Pause the process forever
        pause();

        // Finish the process
        //exit(0);
    } else {
        // Error forking
        sprintf(phrase, "JARL!! ERROR\n");
        write(STDOUT_FILENO, phrase, strlen(phrase));

        exit(-1);
    }
}
