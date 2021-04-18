#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handleSignals(int sig);

int main()
{
    signal(SIGINT,handleSignals);
    signal(SIGQUIT,handleSignals);
    while(1);
    return 0;
}

void handleSignals(int sig)
{
    if(sig == SIGINT)
    {
        printf("\ninterrupt caught %d\n",sig);
        signal(SIGINT,SIG_DFL);
    }
    else if(sig == SIGQUIT)
    {
        printf("\nquit caught %d\n",sig);
    }

}
