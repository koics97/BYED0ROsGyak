#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define SHMKEY 69905

int main()
{
    int shmid; //shm ID-je
    key_t key = SHMKEY; //kulcs a shm-hez
    int size = 512; //shm mérete byte-ban
    int shmflag; //flag a jellemzőkhöz,a flag határozza meg, milyen hozzáférésű az shm, illetve azt is hogy létrehozzuk, írjuk/olvassuk stb

    shmflag = 00666; //megkeressük a létrehozott shm-t

    if((shmid = shmget(key,size,shmflag)) < 0)
    {
        perror("rendszerhivas sikertelen: shmget() error\n");
        exit(-1);
    }

    //attach, mert ahhoz hogy írni/olvasni tudjuk a szegmenst, hozzá kell csatolnunk ezt a processzt az shmat()-al
    int* shm = (int*)shmat(shmid,NULL,shmflag); //sikeres csatolás után, az shm az osztott memória címére mutat
    //shmat()  2. paraméterének memóriacímet kell adni és ha NULL-t adunk, akkor azt mondjuk, hogy az OPrendszerre bízzuk a címtartományt, hogy hol hozza létre a szegmenst a memóriában


    //beolvasás a mem szegmensbe, egy fájlból
    FILE *fp;
    fp = fopen("adatok.txt","r");
    for(int i = 0; i < 3; i++)
    {
        fscanf(fp,"%d ",shm+i);
        printf("%d. szam: %d\n",i+1,shm[i]);
    }
    fclose(fp);

    shmdt(shm);//detach, lecsatlakoztatjuk a processzt a mem szegmensről

    printf("fajlbol beolvasva, osztott memoriaba beleirva!\n");

    return 0;
}
