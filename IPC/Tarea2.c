#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/msg.h>

#define SHM_SIZE 1024

struct message_buffer {
    long message_type;
    char message_text[100];
};

int main() {
    int method;
    printf("Seleccione el método de comunicación:\n1) Tuberías\n2) Memoria Compartida\n3) Pase de Mensajes\n");
    scanf("%d", &method);

    if (method == 1) {
        // Usando tuberías
        int fd1[2]; // Pipe 1: Parent to Child
        int fd2[2]; // Pipe 2: Child to Parent
        pid_t pid;
        char parent_msg[] = "Mensaje desde el padre";
        char child_msg[] = "Mensaje desde el hijo";
        char buffer[100];

        if (pipe(fd1) == -1 || pipe(fd2) == -1) {
            perror("Error al crear las tuberías");
            exit(EXIT_FAILURE);
        }

        pid = fork();

        if (pid < 0) {
            perror("Error al crear el proceso hijo");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            // Proceso padre
            close(fd1[0]); // Cerrar lectura de fd1
            close(fd2[1]); // Cerrar escritura de fd2

            // Enviar mensaje al hijo
            write(fd1[1], parent_msg, strlen(parent_msg) + 1);
            close(fd1[1]); // Cerrar escritura de fd1

            // Leer mensaje del hijo
            read(fd2[0], buffer, sizeof(buffer));
            printf("Padre recibió: %s\n", buffer);
            close(fd2[0]); // Cerrar lectura de fd2

        } else {
            // Proceso hijo
            close(fd1[1]); // Cerrar escritura de fd1
            close(fd2[0]); // Cerrar lectura de fd2

            // Leer mensaje del padre
            read(fd1[0], buffer, sizeof(buffer));
            printf("Hijo recibió: %s\n", buffer);
            close(fd1[0]); // Cerrar lectura de fd1

            // Enviar mensaje al padre
            write(fd2[1], child_msg, strlen(child_msg) + 1);
            close(fd2[1]); // Cerrar escritura de fd2

            exit(0);
        }

    } else if (method == 2) {
        // Usando memoria compartida
        key_t key = ftok("shmfile",65);
        int shmid = shmget(key, SHM_SIZE, 0666|IPC_CREAT);
        char *data = (char*) shmat(shmid, (void*)0, 0);

        pid_t pid = fork();

        if (pid < 0) {
            perror("Error en fork");
            exit(1);
        } else if (pid == 0) {
            // Primer proceso hijo
            // Escribir en la memoria compartida
            strcpy(data, "Mensaje desde el proceso hijo");
            shmdt(data);
            exit(0);
        } else {
            // Proceso padre
            wait(NULL); // Esperar al primer hijo

            // Leer de la memoria compartida
            printf("Proceso padre recibió: %s\n", data);
            // Modificar los datos
            strcpy(data, "Mensaje desde el proceso padre");

            pid_t pid2 = fork();

            if (pid2 < 0) {
                perror("Error en fork");
                exit(1);
            } else if (pid2 == 0) {
                // Segundo proceso hijo
                sleep(1); // Esperar a que el padre escriba
                printf("Segundo proceso hijo recibió: %s\n", data);
                shmdt(data);
                exit(0);
            } else {
                // Proceso padre
                wait(NULL); // Esperar al segundo hijo
                shmdt(data);
                shmctl(shmid, IPC_RMID, NULL); // Eliminar segmento de memoria compartida
            }
        }

    } else if (method == 3) {
        // Usando pase de mensajes
        key_t key = ftok("msgqueue",65);
        int msgid = msgget(key, 0666 | IPC_CREAT);
        struct message_buffer msg;

        pid_t pid = fork();
        if (pid == 0) {
            // Proceso hijo
            msgrcv(msgid, &msg, sizeof(msg.message_text), 1, 0);
            printf("Proceso hijo recibió: %s\n", msg.message_text);
            msgctl(msgid, IPC_RMID, NULL);
        } else {
            // Proceso padre
            msg.message_type = 1;
            strcpy(msg.message_text, "Hola desde el proceso padre");
            msgsnd(msgid, &msg, sizeof(msg.message_text), 0);
            wait(NULL);
        }

    } else {
        printf("Selección inválida\n");
    }

    return 0;
}