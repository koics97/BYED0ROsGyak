#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    pid_t childproc;
    childproc = fork();

    if (childproc < 0)
    {
        perror("unable to create childprocess");
        exit(-1);
    }
    if (childproc > 0)
    {
        int status;
        waitpid(childproc,&status,0); //statuszban lesz a child visszatérési értéke
        printf("\nchildprocess exited with code %d\n",status);
    }
    if (childproc == 0)
    {
        if (execl("/home/marcell/Dokumentumok/Projekt/BYED0Rgyak3_child/bin/Debug/BYED0Rgyak3_child","BYED0Rgyak3_child",NULL) < 0)
        {
            perror("unable to load executable program");
            exit(-10);
        }
    }
    return 0;
}
