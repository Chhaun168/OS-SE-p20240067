#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define SHM_NAME "/my_shared_memory"
#define SIZE 1024

int main() {
    int fd;
    char *ptr;

    // create shared memory
    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open failed");
        return 1;
    }

    ftruncate(fd, SIZE);

    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // CHILD
        sleep(1);
        printf("Child reading from shared memory: %s\n", ptr);
    }
    else {
        // PARENT
        strcpy(ptr, "Hello from Parent Process!");
        printf("Parent wrote to shared memory\n");

        wait(NULL);

        shm_unlink(SHM_NAME);
    }

    return 0;
}
