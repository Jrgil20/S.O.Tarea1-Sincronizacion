#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void manejador_senal(int senal) {
    if (senal == SIGHUP) {
        printf("Recibida la señal SIGHUP\n");
    } else if (senal == SIGTERM) {
        printf("Recibida la señal SIGTERM\n");
    }
}

int main() {
    signal(SIGHUP, manejador_senal);
    signal(SIGTERM, manejador_senal);

    while (1) {
        pause();
    }

    return 0;
}