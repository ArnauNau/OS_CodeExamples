//
// Client - Server example.
// The client connects to the server, sends a greeting and finishes its execution.
// Programació en UNIX, Jordi Salvador Pont
//
// Use: client.exe <IP> <port>
// Example: client.exe 127.0.0.1 1234
//

#define _GNU_SOURCE

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

int main (int argc, char *argv[]) {

    // Check if the port and IP were passed
    if (argc < 3) {
        fprintf (stderr, "Error: missing arguments (IP and Port)\n");
        exit (EXIT_FAILURE);
    }

    // Check if the port is valid
    uint16_t port;
    int aux = atoi (argv[2]);
    if (aux < 1 || aux > 65535) {
        fprintf (stderr, "Error: %s is an invalid port\n", argv[1]);
        exit (EXIT_FAILURE);
    }
    port = aux;

    // Check if the IP is valid and convert it to binary format
    struct in_addr ip_addr;
    if (inet_aton (argv[1], &ip_addr) == 0) {
        fprintf (stderr, "inet_aton (%s): %s\n", argv[1], strerror (errno));
        exit (EXIT_FAILURE);
    }

    // Create the socket
    int sockfd;
    sockfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0) {
        perror ("socket TCP");
        exit (EXIT_FAILURE);
    }

    // Specify the adress and port of the remote host
    struct sockaddr_in s_addr;
    bzero (&s_addr, sizeof (s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons (port);
    s_addr.sin_addr = ip_addr;

    // We can connect to the server casting the struct:
    // connect waits for a struct sockaddr* and we are passing a struct sockaddr_in*
    if (connect (sockfd, (void *) &s_addr, sizeof (s_addr)) < 0) {
        perror ("connect");
        exit (EXIT_FAILURE);
    }

    char msg[] = "Hello!";
    // We use sizeof instead of strlen because msg is an array, but strlen would also work
    write (sockfd, msg, sizeof (msg));

    close(sockfd);

    return EXIT_SUCCESS;
}
