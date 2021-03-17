#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int system(const char *command);
   /* if (system("las") == 0) printf("mukodik");
    else printf("hulyeseget adtal meg");*/

    int a = system("ls -l");  //zárójelben adjuk meg a systemnek a végrehajtandó parancsot

    switch(WEXITSTATUS(a)){ //a WEXITSTATUS a végrehajtott parancs sikerességét jelző kódot (számot) adja vissza; terminálban echo $? adja ezt
        case -1:
        {
            printf("\nVmi gond tortent a parancs futtatas kozben\n");
            break;
        }
        case 127:
        {
            printf("\nnem talalhato ilyen parancs a terminal szerint\n");
            break;
        }
        default:
        {
            printf("\na parancs sikeresen lefutott %d exit koddal\n",a);
            break;
        }
    }
    return 0;
}
