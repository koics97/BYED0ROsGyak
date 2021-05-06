#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

#define SHMKEY 69905

int haromszog_szerkesztheto_e(int,int,int);

int main()
{
    int shmid; //shm ID-je
    key_t key = SHMKEY; //kulcs a shm-hez
    int size = 512; //shm mérete byte-ban
    int shmflag; //flag a jellemzőkhöz,a flag paraméter határozza meg, milyen hozzáférésű az shm, illetve azt is hogy létrehozzuk, írjuk/olvassuk stb

    shmflag = 0;

    //letrehozzuk az osztott memoria szegmenset ugy, hogy elotte megnezzuk letezik-e mar ilyen meretben
    if ((shmid = shmget(key,size,shmflag)) < 0)
    {
        printf("Nincsen meg ilyen meretu shm szegmens, ezert most letrehozzuk\n");
        shmflag = 00666 | IPC_CREAT; //shm létrehozása 00666 hozáféréssel
        shmid = shmget(key,size,shmflag); //az shmget() létrehozza a memória szegmenst, a flag által meghatározott hozzáférhetőséggel, amit az shmflag változóban definiáltunk, majd a visszatérési értéket tároljuk az shmid változóban
        if (shmid < 0)
        {
            perror("sikertelen rendszerhivas: shmget() error\n");
            exit(-1);
        }
    } else printf("Van mar ilyen meretu shm szegmens\n");

    printf("Az osztott memoria azonositoja: %d\n",shmid); //kiírjuk az shm ID-ját

    //attach
    int* shm = (int*)shmat(shmid,NULL,shmflag); //ezt a programot hozzácsatoljuk az osztott memóriához, az shm a létrehozott osztott memória szegmens címére mutat

    while(*shm == '\0')//ezzel a ciklussal várakoztatjuk ezt a processzt, míg egy másik beleír 3 számot az shm-be
    {
        sleep(1);
    }

    printf("\n");
    for(int i = 0; i < 3; i++) //kiiratjuk mit írtak az shm-be
    {
        printf("beolvasott %d. szam: %d\n",i+1,*(shm+i));
    }

    printf("\n");

    if(haromszog_szerkesztheto_e(shm[0],shm[1],shm[2]) == 1) //megnézzük szerkeszthető-e háromszög ebből a 3 számból
    {
        printf("Igen, szerkesztheto haromszog ezekbol a szamokbol\n");
    }
    else printf("Nem, nem szerkesztheto haromszog ezekbol a szamokbol\n");

    shmdt(shm); //detach, lecsatlakoztatjuk a processzt az osztott memóriáról

    shmctl(shmid,IPC_RMID,NULL); //töröljük a mem szegmenst
    return 0;
}

int haromszog_szerkesztheto_e(int a, int b, int c)
{
    FILE *fp = fopen("eredmeny.txt","w");
    if((a + b > c) && (a + c > b) && (b + c > a))
    {
        fprintf(fp,"%d %d es %d szamokbol lehet haromszoget kesziteni, így van kerulete es terulete\n",a,b,c);
        double s = (a+b+c)/2;
        double t = sqrt(s*(s-a)*(s-b)*(s-c));
        fprintf(fp,"kerulet= %d\nterulet = %lf",a+b+c,t);
        return 1;
    }

    fprintf(fp,"%d %d es %d szamokbol nem lehet haromszoget szerkeszteni\n",a,b,c);
    fprintf(fp,"kerulet = %d\nterulet = %d\n",-1,-1);
    fclose(fp);

    return -1;
}
