#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    // ftok para generar una clave única
    key_t key = ftok("shmfile", 65);

    // shmget devuelve un identificador en shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // shmat para adjuntar a la memoria compartida
    char* str = (char*)shmat(shmid, (void*)0, 0);

    printf("Datos leídos de la memoria: %s\n", str);

    // desadjuntar de la memoria compartida
    shmdt(str);

    // destruir la memoria compartida
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
