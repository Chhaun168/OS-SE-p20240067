#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("Parent process (PID: %d) — creating child...\n", getpid());

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        printf("Child process (PID: %d, Parent PID: %d)\n", getpid(), getppid());

        printf("Child sleeping 30 seconds...\n");
        sleep(30);

        printf("Child executing 'ls -la'\n");

        execlp("ls", "ls", "-la", NULL);

        perror("execlp failed");
        exit(EXIT_FAILURE);
    }
    else {
        int status;
        printf("Parent waiting for child (PID: %d)...\n", pid);

        waitpid(pid, &status, 0);

        printf("Parent: child finished with status %d\n", WEXITSTATUS(status));
    }

    return 0;
}
