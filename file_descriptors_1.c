#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
    char string[100];
    char buffer[100];
    int n;

    write(1, "String:", 7);
    n = read(0, string, 100);
    string[n-1] = '\0';
    sprintf(buffer, "Input string: [%s] %ld characters\n", string, strlen(string));
    write(1, buffer, strlen(buffer));

    return(0);
}