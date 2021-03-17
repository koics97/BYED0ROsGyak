#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t gyerekproc;
    gyerekproc = fork();

    if (gyerekproc < 0)
    {
        perror("unable to create child process");
        exit(-1);
    }
    if (gyerekproc > 0)
    {
        int status;
        waitpid(gyerekproc,&status,0);
        printf("\nchild process exited with code %d\n",status);

    }
    if (gyerekproc == 0)
    {
        execlp("ls","ls", "-l",NULL);
        perror("unable to find command"); //ha sikertelenül futna le az execlp, akkor ezt írja ki
    }
    return 0;
}
