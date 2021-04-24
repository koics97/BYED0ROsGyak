#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    int fd[2];
    pipe(fd);
    char text[] = "Koics Marcell BYED0R";
    char readbuffer[80];

    pid_t childpid = fork();

    if(childpid == -1)
    {
        perror("fork");
        exit(1);
    }
    if(childpid == 0)
    {
        close(fd[0]);
        printf("Child is writing\n");
        write(fd[1],text,(strlen(text)+1));
    }
    else
    {
        close(fd[1]);
        printf("Parent is reading\n");
        read(fd[0],readbuffer,sizeof(readbuffer));
        printf("String received from child: %s\n",readbuffer);
    }



    return 0;
}
