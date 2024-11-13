# Tarea 2: Sincronización de procesos, comunicación entre procesos y señales

## Instrucciones

1. **Señales en C:**
    - Elabore un programa en lenguaje C que maneje las señales `SIGHUP` y `SIGTERM`. Cuando reciba una de estas señales, indique la señal recibida en pantalla.

2. **Intercambio de información entre procesos:**
    - Elabore un programa que al crear dos procesos, estos procesos intercambien información de la siguiente forma:
      - a) Usando tuberías
      - b) Con memoria compartida
      - c) A través del pase de mensajes

## Requisitos

- Utilice el lenguaje de programación C.
- Asegúrese de manejar correctamente las señales `SIGHUP` y `SIGTERM`.
- Implemente las tres formas de comunicación entre procesos mencionadas.

## Recursos

- [Documentación de señales en C](https://man7.org/linux/man-pages/man7/signal.7.html)
- [Sistemas operativos geeksforfeeks](https://www.geeksforgeeks.org/operating-systems)
- [Guía sobre tuberías en C](https://www.geeksforgeeks.org/pipes-c-programming/)
- [Memoria compartida en C (geeksforgeeks)](https://www.geeksforgeeks.org/ipc-shared-memory/)
- [memoria compartida en C](https://old.chuidiang.org/clinux/ipcs/mem_comp.php)
- [Pase de mensajes en C (geeksforgeeks)](https://www.geeksforgeeks.org/ipc-using-message-queues/)
- [Pase de mensajes en C](https://old.chuidiang.org/clinux/ipcs/colas.php/)

## Resúmenes

Para obtener más información sobre los temas tratados en esta tarea, consulte los siguientes resúmenes disponibles en el repositorio:

- [Resumen sobre IPC](/IPC/IPC.md)
- [Resumen sobre señales](/SIGNAL/SIGNAL.md)