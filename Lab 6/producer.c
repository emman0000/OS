#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>   // For open()
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define FIFO_PATH "myfifo"
#define BUFFER_SIZE 100

int main() {
    int fd;
    char message[BUFFER_SIZE];

    // Ensure the FIFO exists
    mkfifo(FIFO_PATH, 0666);  // Create FIFO if not exists

    // Open the FIFO for writing
    fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("Error opening FIFO for writing");
        exit(1);
    }

    // Get user input
    printf("Enter a message: ");
    fflush(stdout);  // Ensure prompt is displayed immediately

    if (fgets(message, BUFFER_SIZE, stdin) == NULL) {
        perror("Error reading input");
        close(fd);
        exit(1);
    }

    message[strcspn(message, "\n")] = 0;  // Remove newline character

    // Write to FIFO
    if (write(fd, message, strlen(message) + 1) == -1) {
        perror("Error writing to FIFO");
        close(fd);
        exit(1);
    }

    printf("Message sent: %s\n", message);

    // Close the FIFO
    close(fd);

    return 0;
}

