#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

int main(int argc, char **argv) {
    char in[PIPE_BUF + 1];
    int len = read(0, in, PIPE_BUF);
    for (int i = 0; i < len; i++) {
        if (islower(in[i]))
            in[i] = toupper(in[i]);
    }
    in[len] = '\0';
    printf("%s", in);
    return 0;
}
