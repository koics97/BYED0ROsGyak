#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    pid_t child1;
    child1 = fork();

    if (child1 < 0)
    {
        perror("unable to create child process");
    }

    if (child1 == 0)
    {
        exit(7);
    }

    int status;
    if (wait(&status) != child1) perror("wait error");
    if (WIFEXITED(status)) printf("normalis befejezodes, visszaadott ertek: %d\n",WEXITSTATUS(status));



    pid_t child2;
    if ((child2 = fork()) < 0) perror("unable to create child");
    else if (child2 == 0)
    {
        abort();
    }
    if ((wait(&status)) != child2) perror("wait error");
    if(WIFSIGNALED(status)) printf("abnormalis befejezodes, a szignal sorszama: %d\n",WTERMSIG(status));

    pid_t child3;
    if ((child3 = fork()) < 0) perror("unable to create child");
    else if (child3 == 0)
    {
        printf("%d",5/0);
    }
    if ((wait(&status)) != child3) perror("wait error");
    if(WIFSIGNALED(status)) printf("Abnormalis befejezodes, mert 0-val akartak osztani! A szignal sorszama: %d\n",WTERMSIG(status));

    return 0;
}
