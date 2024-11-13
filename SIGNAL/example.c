#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_signal(int signal) {
    if (signal == SIGINT) {
        printf("Received SIGINT (Ctrl+C). Exiting...\n");
        _exit(0);
    }
}

int main() {
    // Registrar el manejador de señales
    signal(SIGINT, handle_signal);

    // Bucle infinito para mantener el programa en ejecución
    while (1) {
        printf("Running...\n");
        sleep(1);
    }

    return 0;
}