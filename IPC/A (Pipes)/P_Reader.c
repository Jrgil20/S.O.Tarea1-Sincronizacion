#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    pid_t pid;
    char buffer[128];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Proceso hijo (lector)
        close(fd[1]); // Cerrar el extremo de escritura
        read(fd[0], buffer, sizeof(buffer));
        printf("Mensaje recibido: %s\n", buffer);
        close(fd[0]); // Cerrar el extremo de lectura
        exit(EXIT_SUCCESS);
    } else { // Proceso padre
        wait(NULL); // Esperar a que el hijo termine
    }

    return 0;
}