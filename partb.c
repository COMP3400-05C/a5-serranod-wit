#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    // TODO: Complete and document
    if (argc != 3) {
        printf("USAGE: partb FILEIN FILEOUT\n");
        return 1;
    }

    char *input_filename  = argv[1];
    char *output_filename = argv[2];

    int fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0770);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2");
        close(fd);
        return 1;
    }
    close(fd);

    printf("Category,Count\n");
    fflush(stdout);

    char *parta_args[] = {
        "./parta",
        input_filename,
        NULL
    };

    int eret = execv("./parta", parta_args);
    if (eret < 0) {
        perror("execv");
        return 1;
    }

    return 0; 
}
