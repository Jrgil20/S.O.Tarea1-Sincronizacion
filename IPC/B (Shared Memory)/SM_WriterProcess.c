#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
    // ftok para generar una clave única
    key_t key = ftok("shmfile", 65);

    // shmget devuelve un identificador en shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // shmat para adjuntar a la memoria compartida
    char* str = (char*)shmat(shmid, (void*)0, 0);

    printf("Escribe datos: ");
    fgets(str, 1024, stdin);

    printf("Datos escritos en la memoria: %s\n", str);

    // desadjuntar de la memoria compartida
    shmdt(str);

    return 0;
}
