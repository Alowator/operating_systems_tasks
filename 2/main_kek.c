#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <stdio.h>


int main() 
{
    time_t now;
    putenv("TZ=PST8PDT");
    time(&now);
    printf("%s", ctime(&now));
    return 0;
}