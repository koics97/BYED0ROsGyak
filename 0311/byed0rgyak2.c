#include <stdio.h>
#include <stdlib.h>


int main()
{
    int system (const char *command);

    char c;
    for(;;)
    {

            printf("Kerem adjon egy UNIX parancsot\n");
            char cmd[50];
            scanf("%[^\n]%*c",cmd); //[^\n] adja azt hogy a scanf az egész sort beolvassa, a %*c arra van hogy az input buffer üres legyen
            system(cmd);

            printf("\nESC a kilepeshez, ENTER a folytatashoz\n");

            c = getchar();
            if (c == 27)
            {
                break;
            }

    }






    return 0;
}
