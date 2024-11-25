#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void kctrlc(int signum)
{
    char buffer[100];

    sprintf(buffer, "I received a Ctrl+C (%d). I should abort!\n", signum);
    write(STDOUT_FILENO, buffer, strlen(buffer));
}

void ksigalrm(int signum)
{
    char buffer[100];

    sprintf(buffer, "I received a SIGALRM (%d)\n", signum);
    write(STDOUT_FILENO, buffer, strlen(buffer));
}

void kgeneric(int signum)
{
    char buffer[100];

    sprintf(buffer, "I received other signal (%d)\n", signum);
    write(STDOUT_FILENO, buffer, strlen(buffer));
}

/* This function catches all the signals and, depending which one arrives,
 * calls one function or another.
 */
void ksighandler(int signum)
{
	switch (signum)
	{
		case SIGINT:
			kctrlc(signum);
			break;
		case SIGALRM:
			ksigalrm(signum);
			break;
		default:
			kgeneric(signum);
			break;
	}
	// Reprogram the executed signal to perform the same operation again
	signal(signum, ksighandler);
}

int main()
{
    char buffer[100];
	int i;
	long result;

	/* By executing 'kill -l' we'll see that there are 64 signals... we'll reprogram all of them
	 * so when one is executed, ksighandler function is executed
	 */

    write(STDOUT_FILENO, "Reconfigure all signals\n", 24);
	for (i = 1; i <= 64; i++)
	{
		result = (long)signal(i, ksighandler);
        // The result equals to the previous configured function of that signal (0=SIG_DFL, -1=error)
        sprintf(buffer, "Signal %i result: %ld\n", i, result);
        write(STDOUT_FILENO, buffer, strlen(buffer));
	}

	// Program an alarm so SIGALRM (14) is sent to this process in 30 seconds
	alarm(30);

	/* Perform an infinite loop to see our process PID, so we'll be able to
	 * send signals with 'kill -num $PID' or 'kill -name $PID'
	 */
	while (1)
	{
        sprintf(buffer, "I am PID %d and I wait for signals\n", getpid());
        write(STDOUT_FILENO, buffer, strlen(buffer));

		sleep(2);
	}
}
