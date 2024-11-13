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
        int fd[2];
        pid_t pid;
        char mensaje[] = "Hola desde el proceso padre";
        char buffer[100];

        if (pipe(fd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Proceso hijo
            close(fd[1]);
            read(fd[0], buffer, sizeof(buffer));
            printf("Proceso hijo recibió: %s\n", buffer);
            close(fd[0]);
        } else {
            // Proceso padre
            close(fd[0]);
            write(fd[1], mensaje, strlen(mensaje) + 1);
            close(fd[1]);
            wait(NULL);
        }
    } else if (method == 2) {
        // Usando memoria compartida
        key_t key = ftok("shmfile",65);
        int shmid = shmget(key, SHM_SIZE, 0666|IPC_CREAT);
        char *str = (char*) shmat(shmid, (void*)0, 0);

        pid_t pid = fork();
        if (pid == 0) {
            // Proceso hijo
            sleep(1); // Esperar a que el padre escriba
            printf("Proceso hijo leyó: %s\n", str);
            shmdt(str);
        } else {
            // Proceso padre
            strcpy(str, "Hola desde el proceso padre");
            shmdt(str);
            wait(NULL);
            shmctl(shmid, IPC_RMID, NULL);
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