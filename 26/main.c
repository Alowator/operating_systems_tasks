#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

#define LOWER "/home/students/20200/m.bukhner/lab/26/lower"

int main(int argc, char **argv) {
    FILE *pipe = popen(LOWER, "w");
    if (pipe == NULL) {
        perror(argv[0]);
        return 1;
    }

    char *str = "I don't like Capslock\n";
    fputs(str, pipe);
    pclose(pipe);
    return 0;
}
