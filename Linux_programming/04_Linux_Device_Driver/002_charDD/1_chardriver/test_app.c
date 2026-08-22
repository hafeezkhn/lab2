#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_PATH "/dev/my_chardev"
#define BUFFER_SIZE 1024

int main(void)
{
    int fd;
    char write_buf[] = "Hello from Linux user space!";
    char read_buf[BUFFER_SIZE] = {0};
    ssize_t bytes_written, bytes_read;

    /* 1. Open the device node */
    printf("[USER] Opening %s...\n", DEVICE_PATH);
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("[USER] Failed to open the device");
        return EXIT_FAILURE;
    }

    /* 2. Write data to the device */
    printf("[USER] Writing: \"%s\"\n", write_buf);
    bytes_written = write(fd, write_buf, strlen(write_buf));
    if (bytes_written < 0) {
        perror("[USER] Failed to write to the device");
        close(fd);
        return EXIT_FAILURE;
    }

    /* Close and re-open to test open counter and reset read offset */
    close(fd);

    printf("[USER] Re-opening to test read operation...\n");
    fd = open(DEVICE_PATH, O_RDONLY);
    if (fd < 0) {
        perror("[USER] Failed to re-open device");
        return EXIT_FAILURE;
    }

    /* 3. Read data back from the device */
    bytes_read = read(fd, read_buf, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
        perror("[USER] Failed to read from device");
        close(fd);
        return EXIT_FAILURE;
    }
    read_buf[bytes_read] = '\0';
    printf("[USER] Read %zd bytes: \"%s\"\n", bytes_read, read_buf);

    /* 4. Close the device */
    close(fd);
    printf("[USER] Closed device.\n");

    return EXIT_SUCCESS;
}