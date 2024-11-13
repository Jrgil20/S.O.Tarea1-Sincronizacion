# Comunicación entre Procesos (IPC)

La Comunicación entre Procesos (IPC, por sus siglas en inglés) es un concepto fundamental en los sistemas operativos que permite a múltiples procesos comunicarse y sincronizar sus acciones. Entre los diversos métodos de IPC, la memoria compartida es uno de los mecanismos más eficientes, especialmente cuando se trata de aplicaciones críticas en cuanto a rendimiento.

## Comunicación entre Procesos a través de Memoria Compartida

La comunicación entre procesos a través de memoria compartida es un concepto en el cual dos o más procesos pueden acceder a una memoria común y la comunicación se realiza a través de esta memoria compartida, donde los cambios realizados por un proceso pueden ser vistos por otro proceso.

### Problemas con Pipes, FIFO y Colas de Mensajes

El problema con pipes, FIFO y colas de mensajes es que para que dos procesos intercambien información, esta debe pasar a través del kernel.

1. El servidor lee del archivo de entrada.
2. El servidor escribe estos datos en un mensaje utilizando ya sea un pipe, FIFO o cola de mensajes.
3. El cliente lee los datos del canal IPC, lo que nuevamente requiere que los datos sean copiados del buffer IPC del kernel al buffer del cliente.
4. Finalmente, los datos son copiados del buffer del cliente.

Se requieren cuatro copias de datos (2 lecturas y 2 escrituras). Por lo tanto, la memoria compartida proporciona una forma de permitir que dos o más procesos compartan un segmento de memoria. Con la memoria compartida, los datos solo se copian dos veces: desde el archivo de entrada a la memoria compartida y desde la memoria compartida al archivo de salida.

## ¿Qué es IPC?

La Comunicación entre Procesos (IPC) se refiere al conjunto de técnicas que permiten a los procesos intercambiar datos y señales entre sí. IPC es crucial para los sistemas operativos modernos que soportan multitarea, ya que permite que los diferentes procesos cooperen y compartan recursos de manera efectiva. Los mecanismos comunes de IPC incluyen el paso de mensajes, semáforos, pipes, señales y memoria compartida.

## Resumen

La Comunicación entre Procesos (IPC) es esencial para la coordinación y el intercambio de datos entre múltiples procesos en un sistema operativo. Existen varios métodos de IPC, como pipes, FIFO, colas de mensajes, semáforos y memoria compartida. Cada método tiene sus ventajas y desventajas, pero la memoria compartida destaca por su eficiencia al reducir el número de copias de datos necesarias. En general, IPC permite que los procesos trabajen juntos de manera efectiva, mejorando el rendimiento y la capacidad de los sistemas multitarea.

## Referencias

- [Inter Process Communication (IPC)](https://www.geeksforgeeks.org/inter-process-communication-ipc/)