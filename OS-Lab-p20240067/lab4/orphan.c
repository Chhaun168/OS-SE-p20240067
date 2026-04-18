#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        printf("Parent process exiting...\n");
        exit(0);
    } else if (pid == 0) {
        sleep(5);
        printf("Child process (orphan), new parent PID: %d\n", getppid());
    }

    return 0;
}
