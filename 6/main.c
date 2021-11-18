#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


int main(int argc, char *argv[])
{
    int offsets[1000], lengths[1000];
    int length = 0, line_number;
    char c, buf[BUFSIZ];

    int tfd = open("/dev/tty", O_RDONLY | O_NDELAY);
    if (tfd == -1) {
        fprintf(stderr, "Cant open /dev/tty\n");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
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

    while (1) {
        printf("Enter line number:\n");
        sleep(5);
        i = read(tfd, buf, BUFSIZ);

        if (i <= 0) {
            lseek(fd, SEEK_SET, 0);
            while((i = read(fd, buf, BUFSIZ)) > 0)
                write(1, buf, i);
            return 0;
        } else {
            buf[i] = '\0';
            line_number = atoi(buf);
            if (line_number <= 0)
                return 0;
            lseek(fd, offsets[line_number], 0);
            if (read(fd, buf, lengths[line_number]))
                write(1, buf, lengths[line_number]);
            else
                fprintf(stderr, "Incorrect line number\n");
        }
    }

    return 0;
}
