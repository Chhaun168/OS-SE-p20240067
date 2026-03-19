#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        write(2, "Error opening directory\n", 24);
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;
    char buffer[512];

    // Print header using write()
    const char *header1 = "Filename                         Size (bytes)\n";
    const char *header2 = "------------------------------ ----------\n";

    write(1, header1, strlen(header1));
    write(1, header2, strlen(header2));

    // Loop through directory
    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == 0) {

            // Format string into buffer
            int len = snprintf(buffer, sizeof(buffer),
                               "%-30s %10ld\n",
                               entry->d_name,
                               fileStat.st_size);

            // Write to terminal
            write(1, buffer, len);
        }
    }

    closedir(dir);
    return 0;
}
