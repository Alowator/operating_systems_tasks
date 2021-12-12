#include <stdio.h>

int main(int argc, char **argv) {
    FILE  *file = fopen(argv[1], "r");
    if (file ==  NULL) {
        perror(argv[0]);
        return 1;
    }

    FILE *pipe = popen("wc -l", "w");
    char str[BUFSIZ];
    while (fgets(str, BUFSIZ, file) != NULL)
        if (str[0] == '\n')
            fputs(str, pipe);

    fclose(file);
    pclose(pipe);
    return 0;
}
