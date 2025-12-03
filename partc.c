#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    // TODO: Complete and document

  if (argc != 2) {
        printf("USAGE: partc FILEIN\n");
        return 1;
    }

    char *input_filename = argv[1];

    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {

        close(pipefd[0]);

        if (dup2(pipefd[1], STDOUT_FILENO) < 0) {
            perror("dup2");
            close(pipefd[1]);
            return 1;
        }
        close(pipefd[1]);

        char *parta_args[] = {
            "./parta",
            input_filename,
            NULL
        };

        int eret = execv("./parta", parta_args);
        if (eret < 0) {
            perror("execv parta");
            return 1;
        }
    } else {

        close(pipefd[1]);

        if (dup2(pipefd[0], STDIN_FILENO) < 0) {
            perror("dup2");
            close(pipefd[0]);
            return 1;
        }
        close(pipefd[0]);

        char *sort_args[] = {
            "sort",
            "-t,",
            "-k2",
            "-n",
            NULL
        };

        int eret = execvp("sort", sort_args);
        if (eret < 0) {
            perror("execvp sort");
            return 1;
        }
    }

    return 0;
}
