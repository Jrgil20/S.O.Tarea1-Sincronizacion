#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    int fd1[2]; // Pipe 1: Parent to Child
    int fd2[2]; // Pipe 2: Child to Parent

    pid_t pid;
    char parent_msg[] = "Mensaje desde el padre";
    char child_msg[] = "Mensaje desde el hijo";
    char buffer[100];

    // Crear las tuberías
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

    return 0;
}