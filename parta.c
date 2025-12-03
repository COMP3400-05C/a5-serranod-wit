#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];

    // Must have exactly 1 argument (filename)
    if (argc != 2) {
        printf("USAGE: parta FILEIN\n");
        return 1;
    }

    // Open file with open()
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        // Match the exact error message expected by tests
        printf("ERROR: %s not found\n", argv[1]);
        return 1;
    }

    // Counters
    int upper = 0, lower = 0, digit = 0, space = 0, other = 0;

    // Read loop — read 8 bytes at a time
    ssize_t n;
    while ((n = read(fd, buffer, BUFSIZE)) > 0) {
        for (ssize_t i = 0; i < n; i++) {
            unsigned char c = buffer[i];

            if (isupper(c))      upper++;
            else if (islower(c)) lower++;
            else if (isdigit(c)) digit++;
            else if (isspace(c)) space++;
            else                 other++;
        }
    }

    close(fd);

    // Output
    printf("Upper,%d\n", upper);
    printf("Lower,%d\n", lower);
    printf("Number,%d\n", digit);
    printf("Space,%d\n", space);
    printf("Other,%d\n", other);

    return 0;
}
