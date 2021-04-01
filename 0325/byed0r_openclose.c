#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>

int main()
{

    int file = open("neptunkod.txt",O_RDWR); //int pufferbe olvassuk be a txt-t

    if (file > 0) //ellenőrizzük a beolvasás sikerességét
    {
        printf("sikeres beolvasas\n\n");
    }
    else
    {
        printf("hiba tortent a fajl beolvasasnal\n");
    }

    char txt[50];
    ssize_t x = read(file,&txt,50); //karakter tömbben tároljuk a beolvasott szöveget és az x változóban a read() visszatérési értékét

    if (x < 0) printf("hiba a fajl kiolvasasnal\n");
    else printf("%s\nbeolvasott byte: %ld\n",txt,x); //majd kiiratjuk

    lseek(file,0,SEEK_SET); //kurzort mozgatjuk az lseek-el; 0 - a fájl eleje
    read(file,&txt,50);

    ssize_t w = write(1,&txt,42);
    if(w < 0) printf("hiba a kiiratasnal\n");
    else printf("kiirt byte mennyiseg: %ld",w);


    return 0;
}
