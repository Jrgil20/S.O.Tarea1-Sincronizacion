#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGSZ 128

// Define message structure
typedef struct msgbuf {
    long mtype;
    char mtext[MSGSZ];
} message_buf;

int main() {
    int msqid1, msqid2;
    key_t key1 = 1234, key2 = 5678;
    message_buf sbuf, rbuf;
    size_t buf_length;
    pid_t pid;

    // Create the message queues
    if ((msqid1 = msgget(key1, IPC_CREAT | 0666)) < 0) {
        perror("msgget");
        exit(1);
    }
    if ((msqid2 = msgget(key2, IPC_CREAT | 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Proceso hijo
        // Receive message from parent
        if (msgrcv(msqid1, &rbuf, MSGSZ, 1, 0) < 0) {
            perror("msgrcv");
            exit(1);
        }
        printf("Hijo recibió: %s\n", rbuf.mtext);

        // Send message to parent
        sbuf.mtype = 1;
        strcpy(sbuf.mtext, "Mensaje del proceso hijo");
        buf_length = strlen(sbuf.mtext) + 1;

        if (msgsnd(msqid2, &sbuf, buf_length, IPC_NOWAIT) < 0) {
            perror("msgsnd");
            exit(1);
        }

    } else {
        // Proceso padre
        // Send message to child
        sbuf.mtype = 1;
        strcpy(sbuf.mtext, "Mensaje del proceso padre");
        buf_length = strlen(sbuf.mtext) + 1;

        if (msgsnd(msqid1, &sbuf, buf_length, IPC_NOWAIT) < 0) {
            perror("msgsnd");
            exit(1);
        }

        // Receive message from child
        if (msgrcv(msqid2, &rbuf, MSGSZ, 1, 0) < 0) {
            perror("msgrcv");
            exit(1);
        }
        printf("Padre recibió: %s\n", rbuf.mtext);
    }

    // Remove the message queues
    if (msgctl(msqid1, IPC_RMID, NULL) < 0) {
        perror("msgctl");
        exit(1);
    }
    if (msgctl(msqid2, IPC_RMID, NULL) < 0) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}