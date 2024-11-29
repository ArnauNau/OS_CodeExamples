#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    char string[100];
    char buffer[200];
    int fd_file;
    int n;

    write(STDOUT_FILENO, "String:", 7);
    n = read(STDIN_FILENO, string, 100);
    string[n-1] = '\0';
    sprintf(buffer, "Input string: [%s] %ld characters\n", string, strlen(string));
    write(STDOUT_FILENO, buffer, strlen(buffer));

    //Create output file
    fd_file = open("output.txt", O_WRONLY|O_CREAT|O_TRUNC, 0600);
    if (fd_file == -1) {
        sprintf(buffer, "Unable to create file!\n");
        write(STDERR_FILENO, buffer, strlen(buffer));
    } else {
        // Redirect stdout to file (it closes stdout file descriptor)
        //dup2(fd_file, STDOUT_FILENO);

        sprintf(buffer, "File created with file descriptor = %d\n", fd_file);
        write(STDOUT_FILENO, buffer, strlen(buffer));

        // Write content to file
        write(fd_file, string, strlen(string));

        // Close opened file
        close(fd_file);
    }

    return(0);
}
