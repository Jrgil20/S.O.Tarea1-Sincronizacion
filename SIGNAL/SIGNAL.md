# Señales en C

Las señales son una forma de comunicación entre procesos en sistemas operativos tipo Unix.
Una señal es una interrupción generada por software que es enviada a un proceso por el sistema operativo debido a que cuando el usuario presiona Ctrl+C u otro proceso le dice algo a este proceso. Hay un conjunto fijo de señales que se pueden enviar a un proceso. Las señales se identifican mediante números enteros. Permiten que un proceso notifique a otro sobre eventos específicos de manera asíncrona. Aunque las señales son generadas por el sistema operativo, los programas en C pueden definir manejadores personalizados para responder a estas señales utilizando la biblioteca estándar de señales.
El número de señal tiene nombres simbólicos. Por ejemplo, `SIGCHLD` es el número de la señal enviada al proceso principal cuando termina el hijo.

## Tipos de Señales

Algunas de las señales más comunes incluyen:

- `SIGINT`: Interrupción desde el teclado (Ctrl+C).
- `SIGKILL`: Señal para terminar un proceso inmediatamente.
- `SIGTERM`: Señal para solicitar la terminación de un proceso.
- `SIGSEGV`: Señal de violación de segmento (acceso a memoria no permitida).

## Manejo de Señales

Para manejar señales en C, se utiliza la función `signal()` que permite definir un manejador de señales. Un manejador de señales es una función que se ejecuta cuando el proceso recibe una señal específica.

### Ejemplo de Manejo de Señales

```c
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
```

En este ejemplo, el programa registra un manejador para la señal `SIGINT`. Cuando el usuario presiona Ctrl+C, el manejador de señales `handle_signal` se ejecuta y el programa termina.

## Recursos Adicionales

- [Documentación oficial de señales en Linux](https://man7.org/linux/man-pages/man7/signal.7.html)
- [GeeksforGeeks: Señales en C](https://www.geeksforgeeks.org/signals-c-language)

Las señales son una herramienta poderosa para la gestión de procesos y la comunicación entre ellos en sistemas Unix. Comprender cómo manejarlas adecuadamente es esencial para escribir programas robustos y eficientes en C.