#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char message[] = "Hola desde el proceso escritor";

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Proceso hijo (escritor)
        close(fd[0]); // Cerrar el extremo de lectura
        write(fd[1], message, strlen(message) + 1);
        close(fd[1]); // Cerrar el extremo de escritura
        exit(EXIT_SUCCESS);
    } else { // Proceso padre
        wait(NULL); // Esperar a que el hijo termine
    }

    return 0;
}