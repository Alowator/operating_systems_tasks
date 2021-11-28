#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
    
    freopen("big_file.txt", "w", stdout);
    for (int i = 0; i < 100000; i++) {
        printf("This is a big file...\n");
    }
    return 0;
}
