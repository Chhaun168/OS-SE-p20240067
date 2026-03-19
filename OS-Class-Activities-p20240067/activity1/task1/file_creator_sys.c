#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    // Text to write into file
    const char *text = "Hello from Operating Systems class!\n";
    const char *msg = "File created successfully!\n";

    // 1. Open/create file
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Check error
    if (fd < 0) {
        write(2, "Error opening file\n", 19);
        return 1;
    }

    // 2. Write text to file
    write(fd, text, strlen(text));

    // 3. Close file
    close(fd);

    // 4. Print message to terminal
    write(1, msg, strlen(msg));

    return 0;
}
