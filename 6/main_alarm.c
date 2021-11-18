#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h> 

char buf[BUFSIZ];
int fd, tfd;

void print_file_and_exit(int signo) {
    lseek(fd, SEEK_SET, 0);
    int i;
    while ((i = read(fd, buf, BUFSIZ)) > 0)
        write(tfd, buf, i);
    exit(0);
}


int main(int argc, char *argv[])
{
    int offsets[1000], lengths[1000];
    int length = 0, line_number;
    char c;

    tfd = open("/dev/tty", O_RDWR);
    if (tfd == -1) {
        fprintf(stderr, "Cant open /dev/tty\n");
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Incorrect input file - %s\n", argv[1]);
        return 1;
    }

    int i = 0;
    offsets[++i] = 0;
    while (read(fd, &c, sizeof(c))) {
        if (c == '\n') {
            length++;
            lengths[i++] = length;
            offsets[i] = lseek(fd, 0, SEEK_CUR);
            length = 0;
        } else {
            length++;
        }
    }

    signal(SIGALRM, print_file_and_exit);
    while (1) {
        printf("Enter line number:\n");
        alarm(5);
        i = read(tfd, buf, BUFSIZ);
        
        buf[i] = '\0';
        line_number = atoi(buf);
        if (line_number <= 0)
            return 0;
        lseek(fd, offsets[line_number], 0);
        if (read(fd, buf, lengths[line_number]))
            write(tfd, buf, lengths[line_number]);
        else
            fprintf(stderr, "Incorrect line number\n");
    }

    return 0;
}
