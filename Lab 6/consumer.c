#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>  // For open()
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_PATH "myfifo"
#define BUFFER_SIZE 100

int main() {
    int fd;
    char buffer[BUFFER_SIZE];

    // Open the FIFO for reading
    fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("Error opening FIFO for reading");
        exit(1);
    }

    // Read the message from the FIFO
    read(fd, buffer, BUFFER_SIZE);
    
    // Print the received message
    printf("Received message: %s\n", buffer);

    // Close the FIFO
    close(fd);

    return 0;
}

