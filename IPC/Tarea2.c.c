#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd1[2]; // Pipe from parent to child
    int fd2[2]; // Pipe from child to parent
    pid_t pid;
    char parent_msg[] = "Mensaje del proceso padre";
    char child_msg[] = "Mensaje del proceso hijo";
    char buffer[100];

    // Crear las tuberías
    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Proceso hijo
        close(fd1[1]); // Cerrar extremo de escritura de fd1
        close(fd2[0]); // Cerrar extremo de lectura de fd2

        // Leer mensaje del padre
        read(fd1[0], buffer, sizeof(buffer));
        printf("Hijo recibió: %s\n", buffer);

        // Enviar mensaje al padre
        write(fd2[1], child_msg, strlen(child_msg) + 1);

        close(fd1[0]);
        close(fd2[1]);
    } else {
        // Proceso padre
        close(fd1[0]); // Cerrar extremo de lectura de fd1
        close(fd2[1]); // Cerrar extremo de escritura de fd2

        // Enviar mensaje al hijo
        write(fd1[1], parent_msg, strlen(parent_msg) + 1);

        // Leer mensaje del hijo
        read(fd2[0], buffer, sizeof(buffer));
        printf("Padre recibió: %s\n", buffer);

        close(fd1[1]);
        close(fd2[0]);
    }

    return 0;
}