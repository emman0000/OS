
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define MESSAGE "Processed by child process\n"

int main() {
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    // Open input.txt for reading
    fd = open("input.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read contents of input.txt into buffer
    bytesRead = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytesRead == -1) {
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer[bytesRead] = '\0'; // Null-terminate buffer

    printf("Parent Process Read:\n%s\n", buffer);
    close(fd); // Close file after reading

    // Fork a new child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        // Open input.txt for writing (overwrite existing content)
        fd = open("input.txt", O_WRONLY | O_TRUNC);
        if (fd == -1) {
            perror("Error opening file for writing");
            exit(EXIT_FAILURE);
        }

        // Write new message to input.txt
        if (write(fd, MESSAGE, sizeof(MESSAGE) - 1) == -1) {
            perror("Error writing to file");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd); // Close file after writing

        // Replace child process with "cat input.txt" to display updated content
        execlp("cat", "cat", "input.txt", NULL);

        // If execlp fails
        perror("execlp failed");
        exit(EXIT_FAILURE);
    } else {  // Parent process
        wait(NULL); // Wait for child to finish
        printf("Parent Process: Child process completed.\n");
    }

    return 0;
}
