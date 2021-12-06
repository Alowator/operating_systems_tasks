#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
    pid_t pid = fork();
    if (pid == 0)
        execl("/bin/cat", "cat", "/home/students/20200/m.bukhner/lab/9/small_file.txt", NULL);
    else if (pid == -1) {
        perror("fork()");
        return 0;
    }
    printf("Created process with pid = %ld\n", pid);
    
    int status;
    pid_t return_pid = waitpid(pid, &status, WEXITED);
    printf("waitpid(2) returned pid = %ld\n", return_pid);
    printf("Child return status = %d\n", WEXITSTATUS(status));
    return 0;
}
