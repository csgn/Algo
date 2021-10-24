#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
    // define process id
    pid_t pid;

    // fork a child process
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    } else if (pid == 0) {
        execlp("/bin/ls", "ls", NULL);
    } else {
        // parent will be wait for the child to complete
        wait(NULL);
        printf("Child Complete");
    }






    return 0;
}
