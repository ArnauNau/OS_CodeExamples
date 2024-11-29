//
// Client - Server example.
// The server accepts connections and, when a connection is established, it reads the data and prints it on the screen.
// Programació en UNIX, Jordi Salvador Pont
//
// Use: server.exe <port>
// Example: server.exe 1234
//

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    // Check if the port was passed
    if (argc < 2) {
        fprintf (stderr, "Error: port not specified\n");
        exit (EXIT_FAILURE);
    }

    // Check if the port is valid
    uint16_t port;
    int aux = atoi (argv[1]);
    if (aux < 1 || aux > 65535) {
        fprintf (stderr, "Error: %s is an invalid port\n", argv[1]);
        exit (EXIT_FAILURE);
    }
    port = aux;

    // Create the socket
    int sockfd;
    sockfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0) {
        perror ("socket TCP");
        exit (EXIT_FAILURE);
    }

    // Specify the adress and port of the socket
    // We'll admit connexions to any IP of our machine in the specified port
    struct sockaddr_in s_addr;
    bzero (&s_addr, sizeof (s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons (port);
    s_addr.sin_addr.s_addr = INADDR_ANY;

    // When executing bind, we should add a cast:
    // bind waits for a struct sockaddr* and we are passing a struct sockaddr_in*
    if (bind (sockfd, (void *) &s_addr, sizeof (s_addr)) < 0) {
        perror ("bind");
        exit (EXIT_FAILURE);
    }

    // We now open the port (5 backlog queue, typical value)
    listen (sockfd, 5);

    while (1) {
        struct sockaddr_in c_addr;
        socklen_t c_len = sizeof (c_addr);

        // When executing accept we should add the same cast used in the bind function
        int newsock = accept (sockfd, (void *) &c_addr, &c_len);
        if (newsock < 0) {
            perror ("accept");
            exit (EXIT_FAILURE);
        }
        printf ("New connection from %s:%hu\n",
        inet_ntoa (c_addr.sin_addr), ntohs (c_addr.sin_port));

        // While there is data from client, read it and display it
        ssize_t len;
        char buff[513]; // extra space for \0, if needed
        do {
            len = read (newsock, buff, 512);
            buff[len] = 0;
            printf ("%s\n", buff);
        } while (len > 0);
        close (newsock);
    }
    close (sockfd);

    return EXIT_SUCCESS;
}
