#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

int main(int argc, char **argv) {
    int fd[2];
    
    int pipe_status = pipe(fd);
    if (pipe_status == -1) {
        perror(argv[0]);
        return 1;
    }

    char *str = "I don't like Capslock\n";
    int pid = fork();
    if (pid > 0) {
        close(fd[0]);
        write(fd[1], str, sizeof(char) * strlen(str));
        close(fd[1]);
    } else if (pid == 0) {
        char in[PIPE_BUF];
        int len = read(fd[0], in, PIPE_BUF);
        for (int i = 0; i < len; i++) {
            if (islower(in[i]))
                in[i] = toupper(in[i]);
        }
        close(fd[0]);
        printf("%s", in);
    } else {
        perror(argv[0]);
        return 1;
    }

    return 0;
}