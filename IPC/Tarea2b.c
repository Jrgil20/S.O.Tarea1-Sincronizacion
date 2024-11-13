#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>

#define SHM_SIZE 1024  /* tamaño de la memoria compartida */

int main() {
    key_t key;
    int shmid;
    char *data;

    /* Crear una clave única para la memoria compartida */
    key = ftok("shmfile", 65);

    /* Crear el segmento de memoria compartida */
    if ((shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT)) == -1) {
        perror("Error en shmget");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {  /* error en fork */
        perror("Error en fork");
        exit(1);
    } else if (pid == 0) {  /* proceso hijo */
        /* Adjuntar a la memoria compartida */
        data = (char *)shmat(shmid, (void *)0, 0);
        if (data == (char *)(-1)) {
            perror("Error en shmat");
            exit(1);
        }

        /* Escribir en la memoria compartida */
        strcpy(data, "Mensaje desde el proceso hijo");

        /* Desadjuntar la memoria compartida */
        if (shmdt(data) == -1) {
            perror("Error en shmdt");
            exit(1);
        }

        exit(0);
    } else {  /* proceso padre */
        /* Esperar a que el hijo termine */
        wait(NULL);

        /* Adjuntar a la memoria compartida */
        data = (char *)shmat(shmid, (void *)0, 0);
        if (data == (char *)(-1)) {
            perror("Error en shmat");
            exit(1);
        }

        /* Leer de la memoria compartida */
        printf("Proceso padre recibió: %s\n", data);

        /* Modificar los datos */
        strcpy(data, "Mensaje desde el proceso padre");

        /* Desadjuntar la memoria compartida */
        if (shmdt(data) == -1) {
            perror("Error en shmdt");
            exit(1);
        }

        /* Crear segundo proceso hijo */
        pid_t pid2 = fork();

        if (pid2 < 0) {
            perror("Error en fork");
            exit(1);
        } else if (pid2 == 0) {  /* segundo proceso hijo */
            /* Adjuntar a la memoria compartida */
            data = (char *)shmat(shmid, (void *)0, 0);
            if (data == (char *)(-1)) {
                perror("Error en shmat");
                exit(1);
            }

            /* Leer de la memoria compartida */
            printf("Segundo proceso hijo recibió: %s\n", data);

            /* Desadjuntar la memoria compartida */
            if (shmdt(data) == -1) {
                perror("Error en shmdt");
                exit(1);
            }

            exit(0);
        } else {
            /* Esperar a que el segundo hijo termine */
            wait(NULL);

            /* Eliminar el segmento de memoria compartida */
            if (shmctl(shmid, IPC_RMID, NULL) == -1) {
                perror("Error en shmctl");
                exit(1);
            }
        }
    }

    return 0;
}