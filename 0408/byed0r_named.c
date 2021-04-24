#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    int fd;
    char *myfifo = "BYED0R"; //fifo elérési útvonal, a neptunkód a fájl neve

    mkfifo(myfifo,0666); //mkfifo(pathname,permission) - így hozzuk létre a csővezetéket

    char in[80], out[] = "Koics Marcell";

    pid_t child = fork();

    if(child == -1)
    {
        perror("fork");
        exit(1);
    }
    if(child == 0)
    {
        fd = open(myfifo,O_WRONLY);
        printf("Child is writing...\n");
        write(fd,out,strlen(out)+1);
        close(fd);
    }
    else
    {
        fd = open(myfifo,O_RDONLY);
        printf("Parent is reading...\n");
        read(fd,in,sizeof(in));
        printf("Received text from child: %s",in);
        close(fd);
    }
    return 0;
}
